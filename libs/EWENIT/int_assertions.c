#include <stdbool.h>
#include "int_assertions.h"

// Compares two ints for exact equality
int assert_equal_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num)
{
    if (val1 == val2)
        return TestSuite_pass(ts, file_name, line_num, "%d == %d", val1, val2);
    else
        return TestSuite_fail(ts, file_name, line_num, "%d != %d", val1, val2);
}

// Compare two ints to assess their inequality
int assert_not_equal_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num)
{
    if (val1 != val2)
        return TestSuite_pass(ts, file_name, line_num, "%d != %d", val1, val2);
    else
        return TestSuite_fail(ts, file_name, line_num, "%d != %d", val1, val2);
}

// Compare two ints and assert that val1 > val2
int assert_greater_than_int(TestSuite* ts, int val1, int val2, char* file_name, long line_num)
{
    if (val1 > val2)
        return TestSuite_pass(ts, file_name, line_num, "%d > %d", val1, val2);
    else if (val1 == val2)
        return TestSuite_fail(ts, file_name, line_num, "%d == %d", val1, val2);
    else
        return TestSuite_fail(ts, file_name, line_num, "%d < %d", val1, val2);
}

// Ensure value is true
int assert_true(TestSuite* ts, int val1, char* file_name, long line_num)
{
    if (val1)
        return TestSuite_pass(ts, file_name, line_num, "%d is true", val1);
    else
        return TestSuite_fail(ts, file_name, line_num, "%d is false", val1);
}

// Ensure value is false
int assert_false(TestSuite* ts, int val1, char* file_name, long line_num)
{
    if (!val1)
        return TestSuite_pass(ts, file_name, line_num, "%d is false", val1);
    else
        return TestSuite_fail(ts, file_name, line_num, "%d is false", val1);
}