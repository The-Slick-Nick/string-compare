/*----------------------------------------------------------------------------------------
Example extension 1

Defining an assert function and an assert macro invoking that function
----------------------------------------------------------------------------------------*/

// core.h header must be included when defining a function. This can be done either
// by
// #include "../core.h"
// or 
// #include "../EWENIT.h"
// EWENIT.h is slightly preferred, as it includes core.h and helpful utility macros
#include "../EWENIT.h"

// Define the assertion macro to invoke the function
#define ASSERT_EQUALS_SIX(val1) assert_equals_six(ts, val1, __LINE__)


// Define the function being invoked
int assert_equals_six(TestSuite* ts, int val1, double line_num)
{
    if (val1 == 6)
        return TestSuite_pass(ts, line_num, "%d == 6", val1);
    else
        return TestSuite_fail(ts, line_num, "%d != 6", val1);
}

