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

#include "../libs/EWENIT/EWENIT.c"

#include "../src/compare_functions/strcompare.h"

#include "test_utils/random_string.h"
#include "test_utils/compare_function_templates.h"

// #include "../src/compare_functions/cdist_score.h"
// #include "../src/compare_functions/lcs_score.h"
// #include "../src/compare_functions/fss_score.h"
// #include "../src/compare_functions/levenshtein_score.h"


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

// void test_naive_lcs_score()
// {
//     string_comparison_test(naive_lcs_score);
//     subset_test(naive_lcs_score);

//     // Manually tabulated example(s)
//     ASSERT_ALMOST_EQUAL_DOUBLE(naive_lcs_score("dessert", "stressed"), 4/(double)7);
// }
void test_longest_substring()
{
    char buffer[32];

    ASSERT_EQUAL_INT(longest_substring("dessert", "stressed", buffer), 4);  // esse
    ASSERT_EQUAL_STR(buffer, "esse");

    ASSERT_EQUAL_INT(longest_substring("hello", "", buffer), 0);
    ASSERT_EQUAL_STR(buffer, "");

    ASSERT_EQUAL_INT(longest_substring("", "", buffer), 0);
    ASSERT_EQUAL_STR(buffer, "");

    ASSERT_EQUAL_INT(longest_substring("ultimate", "mutilate", buffer), 3);
    ASSERT_EQUAL_STR(buffer, "ate");

    ASSERT_EQUAL_INT(longest_substring("bring", "brung", buffer), 2);
    ASSERT_EQUAL_STR(buffer, "br");  // picks first instance of 2
}

void test_lss_major()
{
    string_comparison_test(lss_major);
    ASSERT_ALMOST_EQUAL_DOUBLE(lss_major("dessert", "stressed"), (double)4/8);
}

void test_lss_minor()
{
    string_comparison_test(lss_minor);
    subset_test(lss_minor);
    ASSERT_ALMOST_EQUAL_DOUBLE(lss_minor("dessert", "stressed"), (double)4/7);
}


void test_fss_major()
{
    string_comparison_test(fss_major);

    // Manually tabulated examples
    ASSERT_EQUAL_DOUBLE(fss_major("REST", "STARE"), (double)2/5);
    ASSERT_EQUAL_DOUBLE(fss_major("STRESSED", "DESSERT"), (double)4/8);
    ASSERT_EQUAL_DOUBLE(fss_major("WREATHES", "WEATHERS"), (double)7/8);
    ASSERT_EQUAL_DOUBLE(fss_major("ULTIMATE", "MUTILATE"), (double)6/8);
}

void test_fss_minor()
{
    string_comparison_test(fss_minor);
    subset_test(fss_minor);
    // Manually tabulated examples
    ASSERT_EQUAL_DOUBLE(fss_minor("REST", "STARE"), (double)2/4);
    ASSERT_EQUAL_DOUBLE(fss_minor("STRESSED", "DESSERT"), (double)4/7);
    ASSERT_EQUAL_DOUBLE(fss_minor("WREATHES", "WEATHERS"), (double)7/8);
    ASSERT_EQUAL_DOUBLE(fss_minor("ULTIMATE", "MUTILATE"), (double)6/8);
}

void test_adjusted_fss_major()
{
    string_comparison_test(adjusted_fss_major);
    // Manually tabulated examples
    ASSERT_EQUAL_DOUBLE(adjusted_fss_major("REST", "STARE"), (double)8/20);
    ASSERT_EQUAL_DOUBLE(adjusted_fss_major("STRESSED", "DESSERT"), (double)28/56);
    ASSERT_EQUAL_DOUBLE(adjusted_fss_major("WREATHES", "WEATHERS"), (double)54/64);
    ASSERT_EQUAL_DOUBLE(adjusted_fss_major("ULTIMATE", "MUTILATE"), (double)47/64);
}

void test_adjusted_fss_minor()
{
    string_comparison_test(adjusted_fss_major);
    subset_test(adjusted_fss_minor);
    // Manually tabulated examples
    ASSERT_EQUAL_DOUBLE(adjusted_fss_minor("REST", "STARE"), (double)10/20);
    ASSERT_EQUAL_DOUBLE(adjusted_fss_minor("STRESSED", "DESSERT"), (double)32/56);
    ASSERT_EQUAL_DOUBLE(adjusted_fss_minor("WREATHES", "WEATHERS"), (double)54/64);
    ASSERT_EQUAL_DOUBLE(adjusted_fss_minor("ULTIMATE", "MUTILATE"), (double)47/64);
}


void test_levenshtein_major()
{
    string_comparison_test(levenshtein_major);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_major("GUMBO", "GAMBOL"), (double)4/6);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_major("KITTEN", "SITTING"), (double)4/7);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_major("STRESSED", "DESSERT"), (double)3/8);
}

void test_levenshtein_minor()
{
    string_comparison_test(levenshtein_minor);
    subset_test(levenshtein_minor);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_minor("GUMBO", "GAMBOL"), (double)4/5);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_minor("KITTEN", "SITTING"), (double)4/6);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_minor("STRESSED", "DESSERT"), (double)3/7);

}

void test_levenshtein_distance()
{
    ASSERT_EQUAL_INT(levenshtein_distance("GUMBO", "GAMBOL"), 4);
    ASSERT_EQUAL_INT(levenshtein_distance("GAMBOL", "GUMBO"), 4);

    ASSERT_EQUAL_INT(levenshtein_distance("KITTEN", "SITTING"), 4);
    ASSERT_EQUAL_INT(levenshtein_distance("SITTING", "KITTEN"), 4);

    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_distance("STRESSED", "DESSERT"), 3);
    ASSERT_ALMOST_EQUAL_DOUBLE(levenshtein_distance("DESSERT", "STRESSED"), 3);
}


/* =======================================================================================
MAIN
========================================================================================*/
int main()
{
    srand(time(NULL));  // All subtests use randomization - init here
    EWENIT_START;
    ADD_CASE(test_cdist_score, "cdist_score");
    // ADD_CASE(test_naive_lcs_score, "naive_lcs_score");
    // ADD_CASE(test_lcs_score, "lcs_score");
    // ADD_CASE(test_fss_score, "fss_score");
    // ADD_CASE(test_adjusted_fss_score, "adjusted_fss_score");

    ADD_CASE(test_longest_substring, "longest substring");
    ADD_CASE(test_lss_major, "lss major");
    ADD_CASE(test_lss_minor, "lss minor");


    ADD_CASE(test_fss_major, "fss major");
    ADD_CASE(test_fss_minor, "fss minor");
    ADD_CASE(test_adjusted_fss_major, "adjusted fss major");
    ADD_CASE(test_adjusted_fss_minor, "adjusted fss minor");

    ADD_CASE(test_levenshtein_major, "levenshtein major");
    ADD_CASE(test_levenshtein_minor, "levenshtein minor");
    EWENIT_END;

    return 0;
}