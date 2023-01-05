/*
int_assertions.h

Assertion functions revolving around integers
*/
#include <stdbool.h>
#include "test_components.h"

// Compares two integers to assess their equality
int assert_equal_int(TestSuite* ts, char* test_name, int val1, int val2)
{

    if(val1 == val2)
        return TestSuite_pass(ts);
    else
    {
        char* fail_msg = format_string(
            "assert_equal_int failure:\n%d != %d\n", val1, val2
        );
        
        int test_status = TestSuite_fail(ts, test_name, fail_msg);
        free(fail_msg);  // format_string generated a copy - free it now
        return test_status;
    }
}

// Compare two integers to assess their inequality
int assert_not_equal_int(TestSuite* ts, char* test_name, int val1, int val2)
{
    if(val1 != val2)
        return TestSuite_pass(ts);
    else if(val1 == val2)
    {
        char* fail_msg = format_string(
            "assert_not_equal_int failure:\n%d == %d\n", val1, val2
        );
        int test_status = TestSuite_fail(ts, test_name, fail_msg);
        free(fail_msg);  // format_string generated a copy - free it now
        return test_status;
    }
}

// Compare two integers and assert that val1 > val2
int assert_greater_than_int(TestSuite* ts, char* test_name, int val1, int val2)
{
    if(val1 > val2)
        return TestSuite_pass(ts);
    else
    {
        // Deal with two different failure scenarios
        char* fail_msg;
        if(val1 == val2)
        {
            fail_msg = format_string(
                "Failure at assert_greater_than_int:\n%d == %d", val1, val2
            );
        }
        else
        {
            fail_msg = format_string(
                "Failure at assert_greater_than_int:\n%d < %d", val1, val2
            );
        }

        int test_status = TestSuite_fail(ts, test_name, fail_msg);
        free(fail_msg);  // format_string generated a copy - free it now
        return test_status;
    }
}


// Tests that a boolean value is true
int assert_true(TestSuite* ts, char* test_name, bool val)
{
    if(val)
        return TestSuite_pass(ts);
    else if(!val)
    {
        char* fail_msg = format_string(
            "assert_true failure:\n%d != true", val
        );
        int test_status = TestSuite_fail(ts, test_name, fail_msg);
        free(fail_msg);
        return test_status;
    }

}

// Tests that a boolean value is false
int assert_false(TestSuite* ts, char* test_name, bool val)
{
    if(!val)
        return TestSuite_pass(ts);
    else
    {
        printf("F");
        ts->n_fail++;

        char* fail_msg = format_string(
            "assert_false failure:\n%d != false", val
        );
        int test_status = TestSuite_fail(ts, test_name, fail_msg);
        free(fail_msg);
        return test_status;
    }
}