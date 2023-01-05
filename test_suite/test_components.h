/*
test_components.h

Core structures and macros for writing test cases
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "strlist.h"
#include "test_codes.h"

#ifndef INCLUDE_GUARD_TEST_SUITE
#define INCLUDE_GUARD_TEST_SUITE


// Uses a double-call to vnsprintf and parsing of a va_list to generate and return
// a pointer to a formatted variable length message. If no variable args are provided,
// simply allocates a new char array ptr, copies base_str into it, then returns it
// Used primarily for generating error messages and making copies
char* format_string(char* base_str, ...)
{
    va_list arg_list;
    va_start(arg_list, base_str);

    // Passing NULL as destination to vsnprintf will return length of target
    // resulting string
    int length = 1 + vsnprintf(NULL, 0, base_str, arg_list);
    char* to_return = (char*)malloc(length * sizeof(char));

    // Now that length is known, make second call to vsnprintf to generate desired
    // string
    vsnprintf(to_return, length, base_str, arg_list);
    
    // I'm not sure why but we need to va_end if we have used va_start
    va_end(arg_list);
    return to_return;
}


/* TestSuite structure definition */
typedef struct TestSuite{
    int n_pass;         // Number of test successes
    int n_fail;         // Number of test failures
    int n_error;          // Number of test errors
    StrList* error_msg; // Linked list of error messages
} TestSuite;


// Initialization function for TestSuite
// Returns pointer to a newly defined TestSuite
TestSuite* TestSuite_init()
{
    TestSuite* ts = (TestSuite*)malloc(sizeof(TestSuite));
    ts->n_pass = 0;
    ts->n_fail = 0;
    ts->n_error = 0;
    ts->error_msg = StrList_init();
    return ts;
}

// Frees any memory allocated as part of a TestSuite
void TestSuite_deconstruct(TestSuite* ts)
{
    StrList_deconstruct(ts->error_msg);
    free(ts);
}

// Call to indicate a test has succeeded.
int TestSuite_pass(TestSuite* ts)
{
    printf("*");
    ts->n_pass++;
    return TEST_SUCCESS;
}

// Call to indicate a test has failed. Provide a test name failure message.
int TestSuite_fail(TestSuite* ts, char* test_name, char* fail_msg)
{
    printf("F");
    ts->n_fail++;

    StrList_append(ts->error_msg, test_name, fail_msg, TEST_FAILURE);
    return TEST_FAILURE;

}

// Call to indicate unexpected behavior or an error has occured. Provide a test name and
// error message
int TestSuite_error(TestSuite* ts, char* test_name, char* error_msg)
{
    printf("E");
    ts->n_error++;

    StrList_append(ts->error_msg, test_name, error_msg, TEST_ERROR);
    return TEST_ERROR;
}

// Print Status of tests - prints test failure and reports on # success/fail
void TestSuite_print(TestSuite* ts)
{
    printf("\n");
    printf("______________________\n");
    for(_listitem* current=ts->error_msg->head;current!=NULL;current=current->next)
    {
        switch(current->status)
        {
            case TEST_SUCCESS:
                printf("SUCCESS\n");
                break;
            case TEST_FAILURE:
                printf("FAIL\n");
                break;
            case TEST_ERROR:
                printf("ERROR\n");
                break;
        }
        printf("%s\n", current->title);
        printf("%s\n", current->content);
        printf("______________________\n");
    }

    printf("Successes: %d\n", ts->n_pass);
    printf("Failures: %d\n", ts->n_fail);
    printf("Errors %d\n", ts->n_error);

}

#endif