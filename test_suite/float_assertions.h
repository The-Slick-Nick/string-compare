/*
float_assertions.h

Assertion functions revolving around floating point numbers
*/
#include <stdbool.h>
#include "test_components.h"

// Compares two floats for exact equality
int assert_equal_float(TestSuite* ts, char* test_name, float val1, float val2)
{
    if(val1 == val2)
        return TestSuite_pass(ts);
    
    char* fail_msg = format_string(
        "assert_equal_float failure\n%f != %f\n", val1, val2
    );
    int test_status = TestSuite_fail(ts, test_name, fail_msg);
    free(fail_msg);  // format_string generated a copy - free it now
    return test_status;
}

// Compare two floats to assess their inequality
int assert_not_equal_float(TestSuite* ts, char* test_name, float val1, float val2)
{
    if(val1 != val2)
        return TestSuite_pass(ts);
    
    char* fail_msg = format_string(
        "assert_not_equal_float failure:\n%f == %f\n", val1, val2
    );
    int test_status = TestSuite_fail(ts, test_name, fail_msg);
    free(fail_msg);  // format_string generated a copy - free it now
    return test_status;

}

// Compare two floats and assert that val1 > val2
int assert_greater_than_float(TestSuite* ts, char* test_name, float val1, float val2)
{
    if(val1 > val2)
        return TestSuite_pass(ts);
    
    // Deal with two different failure scenarios
    char* fail_msg;
    if(val1 == val2)
    {
        fail_msg = format_string(
            "Failure at assert_greater_than_float:\n%f == %f", val1, val2
        );
    }
    else
    {
        fail_msg = format_string(
            "Failure at assert_greater_than_int:\n%f < %f", val1, val2
        );
    }

    int test_status = TestSuite_fail(ts, test_name, fail_msg);
    free(fail_msg);  // format_string generated a copy - free it now
    return test_status;

}
