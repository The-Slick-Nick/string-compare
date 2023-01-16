/*========================================================================================
core.h

Core components for my janky testing framework EWENIT

Definitions/methods for structs:
    TestSuite
    _caseitem
    _assertionitem

Any methods/structs preceded with an underscore
(_caseitem, _assertionitem, and associated methods) should be considered private
and should probably never be directly called outside of this file.

========================================================================================*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#ifndef INCLUDE_GUARD_CORE
#define INCLUDE_GUARD_CORE


#define STATUS_CODE_PASS    0
#define STATUS_CODE_FAIL    -1

#define PRINT_SINGLE_LINE   printf("------------------------------\n")
#define PRINT_DOUBLE_LINE   printf("==============================\n")


/*----------------------------------------------------------------------------------------
HELPER METHOD DEFINITIONS
----------------------------------------------------------------------------------------*/

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

// Format string as above with an already-parsed va_list given
// Returns a newly-allocated character array pointer
char* format_string_valist(char* base_str, va_list arg_list)
{
    int length = 1 + vsnprintf(NULL, 0, base_str, arg_list);
    char* to_return = (char*)malloc(length * sizeof(char));

    vsnprintf(to_return, length, base_str, arg_list);
    return to_return;
}


/*----------------------------------------------------------------------------------------
STRUCT DEFINITIONS
----------------------------------------------------------------------------------------*/


// _assertionitem - individual assertion element - one per assertion per test case
typedef struct TestAssertion {
    int status_code;            // Integer representing status of an assertion
    int line_num;               // Row number assertion was called from
    char* msg;                  // Message to print for this assertion
    struct TestAssertion* next; // Next _assertionitem in list
} _assertionitem;

// _caseitem - individual testcase element storing information about the case
typedef struct TestCaseItem {
    bool is_committed;          // Flag if this _caseitem has been recorded in TestSuite
    int num_pass;               // Number successful assertions for this case
    int num_fail;               // Number of unsuccessful assertions for this case
    int num_tests;              // Total number of assertions for this test case
    char* name;                 // Name provided for this test case
    _assertionitem* ass_head;   // Pointer to head element of assertion list
    _assertionitem* ass_tail;   // Pointer to tail element of assertion list
    struct TestCaseItem* next;  // Pointer to next test case in list
} _caseitem;

// TestSuite - head manager struct for tests
typedef struct {
    int total_pass;             // Grand total number of successes recorded
    int total_fail;             // Grand total number of failures recorded
    int total_tests;            // Grand total number of assertions ran

    int cases_pass;             // Number of test cases passed
    int cases_fail;             // Number of test cases failed
    int num_cases;              // Total number of _caseitem elements
    _caseitem* case_head;       // Pointer to last _caseitem
    _caseitem* case_tail;       // Pointer to last _caseitem in test cases
} TestSuite;


/*----------------------------------------------------------------------------------------
INITIALIZATION & DECONSTRUCTION 
----------------------------------------------------------------------------------------*/

// Assertion Item Initialization
// Private method
_assertionitem* _assertionitem_init(int status_code, char* msg, int line_num)
{
    // NOTE THAT msg SHOULD ALWAYS BE A MALLOC'ED POINTER TO A STRING,
    // NEVER A STRING LITERAL. These should always originate from a call
    // to format_string_valist.
    // 
    // Furthermore, this method should never be "publicly" called and should only
    // ever originate from one of the two chains:
    // TestSuite_pass -> _testcase_addAssertion -> _assertionitem_init (here)
    // TestSuite_fail -> _testcase_addAssertion -> _assertionitem_init (here)


    _assertionitem* ass = (_assertionitem*)malloc(sizeof(_assertionitem));

    ass->status_code = status_code;
    ass->line_num = line_num;
    ass->next = NULL;

    // Add message
    ass->msg = msg;
    return ass;
}

// Private method
void _assertionitem_deconstruct(_assertionitem* ass)
{
    if (ass == NULL)
        return;

    _assertionitem* prev = NULL;
    _assertionitem* current = ass;
    while (current != NULL)
    {
        prev = current;
        current = current->next;

        free(prev->msg);
        free(prev);
    }
}

// Case Item
// Private method
_caseitem* _caseitem_init(char* case_name)
{
    _caseitem* citem = (_caseitem*)malloc(sizeof(_caseitem));
    citem->is_committed = false;
    citem->num_pass = 0;
    citem->num_fail = 0;
    citem->num_tests = 0;
    
    if (case_name == NULL)
        citem->name = NULL;
    else
    {
        citem->name = (char*)malloc((1 + strlen(case_name)) * sizeof(char));
        strcpy(citem->name, case_name);
    }

    citem->ass_head = NULL;
    citem->ass_tail = NULL;
    citem->next = NULL;
    return citem;
}

// Starting at head _caseitem, traverse all _caseitems and free any allocated memory
// Private method
void _caseitem_deconstruct(_caseitem* citem)
{
    if (citem == NULL)
        return;

    _caseitem* prev = NULL;
    _caseitem* current = citem;
    while (current != NULL)
    {
        prev = current;
        current = current->next;

        _assertionitem_deconstruct(prev->ass_head);
        free(prev->name);
        free(prev);
    }

}

// TestSuite
// Public method
TestSuite* TestSuite_init()
{
    TestSuite* ts = (TestSuite*)malloc(sizeof(TestSuite));
    ts->total_pass = 0;
    ts->total_fail = 0;
    ts->total_tests = 0;

    ts->cases_pass = 0;
    ts->cases_fail = 0;
    ts->num_cases = 0;

    ts->case_head = NULL;
    ts->case_tail = NULL;

    return ts;
}

// Public method
void TestSuite_deconstruct(TestSuite* ts)
{
    if (ts == NULL)
        return;

    _caseitem_deconstruct(ts->case_head);
    free(ts);
}


/*----------------------------------------------------------------------------------------
PRINT METHODS
----------------------------------------------------------------------------------------*/

// Private method
// Prints the error status and message for an individual assertion
void _assertionitem_print(_assertionitem* ass)
{
    if (ass == NULL)
        return;

    printf("[%ld] ", ass->line_num);
    switch (ass->status_code)
    {
        case STATUS_CODE_PASS:
            printf("Success");
            break;
        case STATUS_CODE_FAIL:
            printf("Fail");
            break;
        default:
            break;
    }

    if (ass->msg == NULL)
    {
        printf("\n");
        return;
    }

    printf(": %s\n", ass->msg);
}

// Private method
// Compact printing: Prints a one-line list of successes/failures of an assertionitem
// i.e. PFFPFPPFF
void _assertionitem_printCompact(_assertionitem* ass)
{
    if (ass == NULL)
        return;

    switch (ass->status_code)
    {
        case STATUS_CODE_PASS:
            printf("P");
            break;
        case STATUS_CODE_FAIL:
            printf("F");
            break;
        default:
            break;
    }
}

// Private method
// Prints a summary of success/failure for all assertions in a given test case
void _caseitem_print(_caseitem* ci)
{
    if (ci == NULL)
        return;

    if (ci->num_tests == 0)
        return;

    if (!ci->is_committed)
        return;

    // Print name if one was given
    if (ci->name == NULL)
        printf("UNTITLED\n");
    else
        printf("%s\n", ci->name);

    // Print each assertion message for this test case
    for (_assertionitem* cur = ci->ass_head; cur != NULL; cur = cur->next)
    {
        printf("    ");
        _assertionitem_print(cur);
    }
    PRINT_SINGLE_LINE;
    printf("[%dP] ", ci->num_pass);
    printf("[%dF] ", ci->num_fail);
    printf("Total: %d\n", ci->num_tests);
}

// Private method
// Compact printing of a case item. Prints a one-line summary of this test case
void _caseitem_printCompact(_caseitem* ci)
{
    if (ci == NULL)
        return;

    if (ci->num_tests == 0)
        return;

    if (!ci->is_committed)
        return;

    if (ci->name == NULL)
        printf("UNTITLED: ");
    else
        printf("%s: ", ci->name);

    // Print overall status for _caseitem
    if (ci->num_fail > 0)
        printf("Failed ");
    else
        printf("Passed ");

    printf("[");
    for (_assertionitem* cur = ci->ass_head; cur != NULL; cur = cur->next)
    {
        _assertionitem_printCompact(cur);
    }
    printf("]");
}

// Public method
void TestSuite_print(TestSuite* ts)
{
    for (_caseitem* cur = ts->case_head; cur != NULL; cur = cur->next)
    {
        PRINT_DOUBLE_LINE;
        _caseitem_print(cur);
        printf("\n");
    }
    PRINT_DOUBLE_LINE;
    printf("Assertions\n");
    printf("[%dP] [%dF] Total: %d", ts->total_pass, ts->total_fail, ts->total_tests);
    printf("\n\nTest Cases\n");
    printf("[%dP] [%dF] Total: %d", ts->cases_pass, ts->cases_fail, ts->num_cases);
    printf("\n");

}

// Public method
void TestSuite_printCompact(TestSuite* ts)
{
    PRINT_DOUBLE_LINE;
    for (_caseitem* cur = ts->case_head; cur != NULL; cur = cur->next)
    {
        _caseitem_printCompact(cur);
        printf("\n");
    }
    PRINT_DOUBLE_LINE;
    printf("Assertions ");
    printf("[%dP] [%dF] Total: %d\n", ts->total_pass, ts->total_fail, ts->total_tests);
    printf("Test Cases ");
    printf("[%dP] [%dF] Total: %d\n", ts->cases_pass, ts->cases_fail, ts->num_cases);
}

/*----------------------------------------------------------------------------------------
ASSERTION/TEST CASE MANAGEMENT
----------------------------------------------------------------------------------------*/

// Shorthand to add an _assertionitem to a provided _caseitem
// Private method
void _caseitem_addAssertion(_caseitem* citem, int status_code, char* msg, int line_num)
{
    _assertionitem* new_ass = _assertionitem_init(status_code, msg, line_num);
    if (citem->ass_head == NULL)
        citem->ass_head = new_ass;
    
    if (citem->ass_tail != NULL)
        citem->ass_tail->next = new_ass;

    citem->ass_tail = new_ass;
}

// A _caseitem is considered incomplete until it has been committed. This method commits
// it, adding success/fail/total counts to TestSuite and flagging it as considered
// Public method
int TestSuite_commitCase(TestSuite* ts)
{
    if (ts->case_tail == NULL)
        return -1;

    if (ts->case_tail->is_committed)
        return -1;

    ts->total_pass += ts->case_tail->num_pass;
    ts->total_fail += ts->case_tail->num_fail;
    ts->total_tests += ts->case_tail->num_tests;

    ts->num_cases++;
    if (ts->case_tail->num_fail > 0)
        ts->cases_fail++;
    else
        ts->cases_pass++;

    ts->case_tail->is_committed = true;
    return 0;
}

// Adds a new test case. First commits the old running one at tail _caseitem, then
// appends a brand new one to the right side
// Public method
int TestSuite_newCase(TestSuite* ts, char* case_name)
{
    // New case - commit the old one
    TestSuite_commitCase(ts);

    _caseitem* new_case = _caseitem_init(case_name);

    if (ts->case_head == NULL)
        ts->case_head = new_case;

    if (ts->case_tail != NULL)
        ts->case_tail->next = new_case;

    // new_case is now the "current" test case under consideration
    ts->case_tail = new_case;
    return 0;
}

// Call to indicate an assertion passed on the current running _caseitem
// Public method
int TestSuite_pass(TestSuite* ts, long line_num, char* msg, ...)
{
    if (ts->case_tail == NULL)
        return -1;

    // Handle any formatting passed by using format_string_valist
    char* pass_msg;
    va_list arg_list;
    va_start(arg_list, msg);

    pass_msg = format_string_valist(msg, arg_list);

    // Cases are added to the right side
    _caseitem_addAssertion(ts->case_tail, STATUS_CODE_PASS, pass_msg, line_num);
    ts->case_tail->num_pass++;
    ts->case_tail->num_tests++;

    va_end(arg_list);
    return 0;
}

// Call to indicate an assertion failed on the current running _caseitem
// Public method
int TestSuite_fail(TestSuite* ts, long line_num, char* msg, ...)
{
    if (ts->case_tail == NULL)
        return -1;

    // Handle any formatting passed by using format_string_valist
    char* fail_msg;
    va_list arg_list;
    va_start(arg_list, msg);

    fail_msg = format_string_valist(msg, arg_list);

    // Cases are added to the right side
    _caseitem_addAssertion(ts->case_tail, STATUS_CODE_FAIL, fail_msg, line_num);
    ts->case_tail->num_fail++;
    ts->case_tail->num_tests++;

    va_end(arg_list);
    return 0;
}

#endif