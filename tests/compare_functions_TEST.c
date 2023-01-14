/* =======================================================================================
comparison_funcs_TEST.c

Tests on string comparison methods
    cdist_score
    lcs_score
    improved_lcs_score
    fss_score
    adjusted_fss_score
    naive_fss_score
    adjusted_naive_fss_score
    levenshtein_score
========================================================================================*/

#include "../EWENIT/EWENIT.c"
#include "test_utils/random_string.h"
#include "test_utils/compare_function_templates.h"

#include "../strcompare/compare_functions/cdist_score.h"
#include "../strcompare/compare_functions/lcs_score.h"
#include "../strcompare/compare_functions/fss_score.h"
#include "../strcompare/compare_functions/levenshtein_score.h"

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

void test_naive_lcs_score()
{
    string_comparison_test(naive_lcs_score);
    subset_test(naive_lcs_score);

    // Manually tabulated example(s)
    ASSERT_ALMOST_EQUAL_DOUBLE(naive_lcs_score("dessert", "stressed"), 4/(double)7);
}

void test_lcs_score()
{
    // Note these tests should mirror lcs_score - as this one should check the same
    // thins in a more efficient way
    string_comparison_test(lcs_score);
    subset_test(lcs_score);

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
        score1 = naive_lcs_score(str1, str2);
        score2 = lcs_score(str1, str2);
        if (!ALMOST_EQUAL_DOUBLE(score1, score2))
        {
            TEST_FAIL_FMT(
                "naive_lcs and lcs differ: %f != %f\n      %s\n      %s",
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
    clock_t start;
    clock_t end;
    double lcs_time = 0;
    double improved_lcs_time = 0;

    #define TIME_TAKEN ((double)(end - start)) / CLOCKS_PER_SEC

    for (int i = 0; i < 100000; i++)
    {
        str1 = random_string();
        str2 = random_string();
        start = clock();
        naive_lcs_score(str1, str2);
        end = clock();
        lcs_time += TIME_TAKEN;

        start = clock();
        lcs_score(str1, str2);
        end = clock();
        improved_lcs_time += TIME_TAKEN;

        free(str1);
        free(str2);
    }
    if (improved_lcs_time < lcs_time)
    {
        TEST_PASS_FMT(
            "lcs performed faster than naive_lcs over 100k tests: %f < %f",
            improved_lcs_time, lcs_time
        );
    }
    else
    {
        TEST_FAIL_FMT(
            "lcs performed slower than naive_lcs over 100k tests: %f > %f",
            improved_lcs_time, lcs_time
        );
    }  
}

void test_fss_score()
{
    string_comparison_test(fss_score);

    // Regular mss has subset == 1 property
    subset_test(fss_score);
    // Manually tabulated examples
    ASSERT_EQUAL_DOUBLE(fss_score("STRESSED", "DESSERT"), (double)3/6);
    ASSERT_EQUAL_DOUBLE(fss_score("WREATHES", "WEATHERS"), (double)6/7);
    ASSERT_EQUAL_DOUBLE(fss_score("ULTIMATE", "MUTILATE"), (double)5/7);
}

void test_adjusted_fss_score()
{
    string_comparison_test(adjusted_fss_score);
    // Manually tabulated examples
    ASSERT_EQUAL_DOUBLE(adjusted_fss_score("STRESSED", "DESSERT"), (double)18/36);
    ASSERT_EQUAL_DOUBLE(adjusted_fss_score("WREATHES", "WEATHERS"), (double)34/42);
    ASSERT_EQUAL_DOUBLE(adjusted_fss_score("ULTIMATE", "MUTILATE"), (double)29/42);
}

void test_naive_fss_score()
{
    string_comparison_test(naive_fss_score);
    subset_test(naive_fss_score);

    // Manually tabulated examples
    ASSERT_EQUAL_DOUBLE(naive_fss_score("ULTIMATE", "MUTILATE"), (double)5/7);
    ASSERT_EQUAL_DOUBLE(naive_fss_score("WREATHES", "WEATHERS"), (double)6/7);
}


void test_adjusted_naive_fss_score()
{
    string_comparison_test(adjusted_naive_fss_score);
    // Manually tabulated examples
    ASSERT_ALMOST_EQUAL_DOUBLE(
        adjusted_naive_fss_score("STRESSED", "DESSERT"), (double)18/36
    );
    ASSERT_ALMOST_EQUAL_DOUBLE(
        adjusted_naive_fss_score("ULTIMATE", "MUTILATE"), (double)24/42
    );


}

void test_levenshtein_score()
{
    string_comparison_test(levenshtein_score);
    // Manually tabulated examples
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_score("GUMBO", "GAMBOL"), (double)4/6);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_score("KITTEN", "SITTING"), (double)4/7);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_score("STRESSED", "DESSERT"), (double)3/8);
}

/* =======================================================================================
MAIN
========================================================================================*/
int main()
{
    srand(time(NULL));  // All subtests use randomization - init here
    EWENIT_START;
    ADD_CASE(test_cdist_score, "cdist_score");
    ADD_CASE(test_naive_lcs_score, "naive_lcs_score");
    ADD_CASE(test_lcs_score, "lcs_score");
    ADD_CASE(test_fss_score, "fss_score");
    ADD_CASE(test_adjusted_fss_score, "adjusted_fss_score");
    ADD_CASE(test_naive_fss_score, "naive fss score");
    ADD_CASE(test_adjusted_naive_fss_score, "adjusted naive fss score");
    ADD_CASE(test_levenshtein_score, "levenshtein score");
    EWENIT_END;
}