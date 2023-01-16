/*========================================================================================
int_assertions.h

Assertion functions revolving around integers
Also includes boolean checks
========================================================================================*/
#include <stdbool.h>
#include "core.h"

// Compares two ints for exact equality
int assert_equal_int(TestSuite* ts, int val1, int val2, long line_num)
{
    if (val1 == val2)
        return TestSuite_pass(ts, line_num, "%d == %d", val1, val2);
    else
        return TestSuite_fail(ts, line_num, "%d != %d", val1, val2);
}

// Compare two ints to assess their inequality
int assert_not_equal_int(TestSuite* ts, int val1, int val2, long line_num)
{
    if (val1 != val2)
        return TestSuite_pass(ts, line_num, "%d != %d", val1, val2);
    else
        return TestSuite_fail(ts, line_num, "%d != %d", val1, val2);
}

// Compare two ints and assert that val1 > val2
int assert_greater_than_int(TestSuite* ts, int val1, int val2, long line_num)
{
    if (val1 > val2)
        return TestSuite_pass(ts, line_num, "%d > %d", val1, val2);
    else if (val1 == val2)
        return TestSuite_fail(ts, line_num, "%d == %d", val1, val2);
    else
        return TestSuite_fail(ts, line_num, "%d < %d", val1, val2);
}

// Ensure value is true
int assert_true(TestSuite* ts, int val1, long line_num)
{
    if (val1)
        return TestSuite_pass(ts, line_num, "%d is true", val1);
    else
        return TestSuite_fail(ts, line_num, "%d is false", val1);
}

// Ensure value is false
int assert_false(TestSuite* ts, int val1, long line_num)
{
    if (!val1)
        return TestSuite_pass(ts, line_num, "%d is false", val1);
    else
        return TestSuite_fail(ts, line_num, "%d is false", val1);
}