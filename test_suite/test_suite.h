/*
test_suite.h

Methods for unit testing
RETURN CODES
0   SUCCESS
-1  TEST FAILURE

USAGE
Create a test file in form XXX_test.c
#include ".../test_suite.c"

Write test methods in the form 
    int test_some_func(TestSuite* ts)
    {
        ... some code ...
        assert_function(ts, "test_some_func", ...)
    }

Assert functions are defined in this file and are used to test equality/inequality
and various other properties of expected function results.

Then, in a main method, do:

1 int main()
2 {
3   TestSuite* ts = TestSuite_init();
4   test_some_func(ts);
5   ... other test functions ...
6
7   TestSuite.print(ts);
8   TestSuite_deconstruct(ts);
9 }

3.  Initializes a TestSuite struct
4-5 Runs tests and passes TestSuite to it, recording results
7   Prints results of tests
*/

#include "test_components.h"
#include "int_assertions.h"
#include "str_assertions.h"
#include "float_assertions.h"
#include "double_assertions.h"
