#include "core.h"

#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
    #define OPTIONAL_VARIADIC_SUPPORTED         1
#else
    #define OPTIONAL_VARIADIC_SUPPORTED         0
#endif

#define EWENIT_START                            ts = TestSuite_init();
#define TEST_START                              EWENIT_START
#define EWENIT_END                              TestSuite_commitCase(ts);\
                                                TestSuite_print(ts);\
                                                TestSuite_deconstruct(ts)
#define TEST_END                                EWENIT_END

// Support a compact version of final error reporting
#define EWENIT_END_COMPACT                      TestSuite_commitCase(ts);\
                                                TestSuite_printCompact(ts);\
                                                TestSuite_deconstruct(ts);
#define TEST_END_COMPACT                        EWENIT_END_COMPACT

#define ADD_CASE(func, name)                    TestSuite_newCase(ts, name); func() 


// Allow manual PASS/FAIL macros to use formatted arguments if compiler supports it
#if OPTIONAL_VARIADIC_SUPPORTED
    #define TEST_PASS(msg, ...)                 TestSuite_pass(ts, __LINE__, msg, ##__VA_ARGS__)
    #define TEST_FAIL(msg, ...)                 TestSuite_fail(ts, __LINE__, msg, ##__VA_ARGS__)
#else
    #define TEST_PASS(msg)                      TestSuite_pass(ts, __LINE__, msg)
    #define TEST_FAIL(msg)                      TestSuite_fail(ts, __LINE__, msg)
#endif

// Provide a formatting-supported version of the macro regardless
#define TEST_PASS_FMT(msg, ...)                 TestSuite_pass(ts, __LINE__, msg, __VA_ARGS__)
#define TEST_FAIL_FMT(msg, ...)                 TestSuite_fail(ts, __LINE__, msg, __VA_ARGS__)


#define ERROR_CHECK(x)                          if (x < 0) do \
                                                   {printf("ASSERTION UNSUCCESSFUL\n");}\
                                                   while (0)
