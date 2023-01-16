/*----------------------------------------------------------------------------------------
Example extension 2

Defining an assert macro directly without the function
----------------------------------------------------------------------------------------*/#

// Note that "../core.h" need not be included, as it is only needed to reference
// TestSuite_pass and TestSuite_fail in assertion function.
// Since a macro will simply expand the code out when invoked, it needs not to include
// core components.

// The macro defines the code for the assertion directly
#define ASSERT_EQUALS_SEVEN(val1) \
    if (val1 == 7)\
        TestSuite_pass(ts, __LINE__, "%d == 7", val1);\
    else\
        TestSuite_fail(ts, __LINE__, "%d != 7", val1);
