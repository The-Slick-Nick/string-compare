/* =======================================================================================
comparison_funcs_TEST.c

Tests on string comparison methods
    cdist_score
    lcs_score
    improved_lcs_score
========================================================================================*/

#include "../../EWENIT/EWENIT/EWENIT.c"
#include "test_utils\random_string.h"
#include "compare_function_templates.h"

#include "../c_version/compare_functions/cdist_score.h"
#include "../c_version/compare_functions/lcs_score.h"

#include <time.h>
#include <stdbool.h>


/* =======================================================================================
INDIVIDUAL FUNCTION TESTS
========================================================================================*/
void test_cdist_score()
{
    string_comparison_test(cdist_score);
    ASSERT_EQUAL_DOUBLE(cdist_score("abcd", "abzz"), 0.5);
}

void test_lcs_score()
{
    string_comparison_test(lcs_score);
    subset_test(lcs_score);

    // Manually tabulated example(s)
    ASSERT_ALMOST_EQUAL_DOUBLE(lcs_score("dessert", "stressed"), 4/(double)7);
}

void test_improved_lcs_score()
{
    // Note these tests should mirror lcs_score - as this one should check the same
    // thins in a more efficient way
    string_comparison_test(improved_lcs_score);
    subset_test(improved_lcs_score);

    // Now test that results match lcs score
    char* str1;
    char* str2;
    double score1;
    double score2;
    bool subtest_failed;

    subtest_failed = false;
    for (int i = 0; i < 100; i++)
    {
        str1 = random_string();
        str2 = random_string();
        score1 = lcs_score(str1, str2);
        score2 = improved_lcs_score(str1, str2);
        if (!ALMOST_EQUAL_DOUBLE(score1, score2))
        {
            TEST_FAIL_FMT(
                "lcs and improved_lcs differ: %f != %f\n      %s\n      %s",
                score1, score2, str1, str2
            );
            free(str1);
            free(str2);
            subtest_failed = true;
            break;
        }
        free(str1);
        free(str2);
    }
    if (!subtest_failed)
        TEST_PASS("lcs and improved_lcs generate same score for 100 tests");


    // Time 100k for each
    double lcs_time = time_comparison_func(lcs_score, 100000);
    double improved_lcs_time = time_comparison_func(improved_lcs_score, 100000);
    if (improved_lcs_time < lcs_time)
    {
        TEST_PASS_FMT(
            "improved_lcs performed faster than lcs over 100k tests: %f < %f",
            improved_lcs_time, lcs_time
        );
    }
    else
    {
        TEST_FAIL_FMT(
            "improved_lcs performed slower than lcs over 100k tests: %f > %f",
            improved_lcs_time, lcs_time
        );
    }  
}

void test_mss_score()
{
    string_comparison_test(mss_score);

    // Regular mss has subset == 1 property
    subset_test(mss_score);
}

void test_adjusted_mss_score()
{
    string_comparison_test(adjusted_mss_score);
}

/* =======================================================================================
MAIN
========================================================================================*/
int main()
{
    srand(time(NULL));  // All subtests use randomization - init here
    EWENIT_START;
    ADD_CASE(test_cdist_score, "cdist_score");
    ADD_CASE(test_lcs_score, "lcs_score");
    ADD_CASE(test_improved_lcs_score, "improved_lcs_score");
    EWENIT_END;
}