/*========================================================================================
compare_func_templates.h

Utility functins and testing templates to assess string comparison functions
========================================================================================*/
#include "../../libs/EWENIT/EWENIT.c"
#include "random_string.h"
#include "string_concat.h"

#include <time.h>
#include <stdbool.h>


/*========================================================================================
HELPER FUNCS
========================================================================================*/
double time_comparison_func(
    double(*compare_func)(const char*, const char*), int num_tests
)
{
    clock_t start;
    clock_t end;
    double time_taken = 0;

    char* str1;
    char* str2;

    start = clock();

    for (int i = 0; i < num_tests; i++)
    {
        str1 = random_string();
        str2 = random_string();
        // Make sure to only time the comparison portion
        start = clock();
        compare_func(str1, str2);
        end = clock();
        time_taken += ((double)(end - start)) / CLOCKS_PER_SEC;
        free(str1);
        free(str2);
    }
    return time_taken;
}


/*========================================================================================
SUBTEST TEMPLATES
========================================================================================*/

// test that func(str1, str2) == 1.0 for str1 == str2
void exact_equality_test(double(*compare_func)(const char*, const char*))
{
    char* test_str;
    double score;
    for (int i = 0; i < 1000; i++)
    {
        test_str = random_string();
        score = compare_func(test_str, test_str);
        if (score != 1.0)
        {
            TEST_FAIL_FMT("Equality test failed: %f \n      %s", score, test_str);
            free(test_str);
            return;
        }
    }
    TEST_PASS("Equality test passed for all 1,000 tests");
}

// test that func(str1, str2) == func(str2, str1)
void reversibility_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    char* str2;
    double score1;
    double score2;
    for (int i = 0; i < 1000; i++)
    {
        str1 = random_string();
        str2 = random_string();
        score1 = compare_func(str1, str2);
        score2 = compare_func(str2, str1);
        if (score1 != score2)
        {
            TEST_FAIL_FMT("Reversibility test failed\n      %s\n      %s", str1, str2);
            free(str1);
            free(str2);
            return;
        }
    }
    free(str1);
    free(str2);
    TEST_PASS("Reversibility test passed for all 1,000 tests");
}

// Test that func(str1, str2) == 0.0 if str1 and str2 share 0 characters
void inequality_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    char* str2;
    for (int i = 0; i < 1000; i++)
    {
        str1 = random_string_charset(CHARSET_NUMBERS);
        str2 = random_string_charset(CHARSET_UPPERCASE);
        if (compare_func(str1, str2) != 0.0)
        {
            TEST_FAIL_FMT("Inequality test failed\n      %s\n      %s", str1, str2);
            free(str1);
            free(str2);
            return;
        }
    }
    free(str1);
    free(str2);
    TEST_PASS("Inequality test passed for all 1,000 tests");
}

// test that func(str1, "") == 0 for any str1 != ""
void one_empty_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    double score;
    for (int i = 0; i < 100; i++)
    {
        str1 = random_string();
        score = compare_func(str1, "");
        if (score != 0)
        {
            TEST_FAIL_FMT("Empty string test failed: Score %f on string %s", score, str1);
            free(str1);
            return;
        }
    }
    free(str1);
    TEST_PASS("Empty string test passed for all 1,000 tests");
}

// test that 0.0 <= func(str1, str2) <= 1.0 for any valid str1, str2
void score_range_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    char* str2;
    double score;
    for (int i = 0; i < 1000; i++)
    {
        str1 = random_string();
        str2 = random_string();
        score = compare_func(str1, str2);
        if (score < 0.0 || score > 1.0)
        {
            TEST_FAIL_FMT(
                "Score range failed: %f on \n      %s\n      %s", score, str1, str2
            );
            free(str1);
            free(str2);
            return;
        }
    }
    free(str1);
    free(str2);
    TEST_PASS("Score range met for all 1,000 tests");

}

// test that 10000 runs of func executes within 1 second
void benchmark_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    char* str2;

    clock_t t_start, t_end;
    double time_taken = 0;
    
    t_start = clock();

    // 100k passes
    for (int num_tests = 0; num_tests < 10000; num_tests++)
    {

        str1 = random_string();
        str2 = random_string();
        if (time_taken > 1.0)
        {
            TEST_FAIL_FMT(
                "Benchmark test failed: %d out of 10000 tests in 1 second",
                num_tests
            );
            free(str1);
            free(str2);
            return;
        }
        // Only time the comparison portion
        t_start = clock();
        compare_func(str1, str2);
        t_end = clock();
        time_taken += ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
    }
    // 100k passes should be done in less than a second
    TEST_PASS_FMT(
        "Benchmark test succeeded: 10000 tests completed in %f seconds", time_taken
    );
    free(str1);
    free(str2);
}

// test that funct(str1, str2) == 1.0 if str1 is a subset of str2 or vice versa
void subset_test(double(*compare_func)(const char*, const char*))
{

    char* prefix;
    char* base_str;
    char* suffix;
    char* to_compare;

    int substr_type; // randomly generated, 0-2
                     // 0 - prefix, 1 - suffix, 2 - both


    double score;

    for (int i = 0; i < 1000; i++)
    {
        substr_type = rand() % 3;
        base_str = random_string();
        prefix = random_string();
        suffix = random_string();
        switch (substr_type)
        {

            case 0:  // Prefix
                to_compare = string_concat(2, prefix, base_str);
                break;
            case 1:  // Suffix
                to_compare = string_concat(2, base_str, suffix);
                break;
            case 2:
                to_compare = string_concat(3, prefix, base_str, suffix);
                break;
            default:
                strcpy(to_compare, base_str);
        }

        score = compare_func(base_str, to_compare);

        if (score != 1.0)
        {
            TEST_FAIL_FMT(
                "Subset score not 1.0 on strings\n      %s\n      %s",
                base_str, to_compare
            );
            free(base_str);
            free(prefix);
            free(suffix);
            free(to_compare);
            return;
        }
    }
    TEST_PASS("Subset test passed on all 1,000 tests");
    free(base_str);
    free(prefix);
    free(suffix);
    free(to_compare);
}

/* =======================================================================================
MASTER TEMPLATE
========================================================================================*/

// Series of standard check that should be true for ANY string comparison function
void string_comparison_test(double(*compare_func)(const char*, const char*))
{
    exact_equality_test(compare_func);
    inequality_test(compare_func);
    one_empty_test(compare_func);
    reversibility_test(compare_func);
    benchmark_test(compare_func);
    score_range_test(compare_func);

}
