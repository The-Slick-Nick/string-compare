/* =======================================================================================
comparison_funcs_TEST.c

Tests on string comparison methods
========================================================================================*/

#include "../libs/EWENIT/EWENIT.h"
#include "../src/compare_functions/strcompare.h"

#include "test_utils/random_string.h"
#include "test_utils/string_concat.h"

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
    char buffer1[RANDOMSTR_MAX_LENGTH];
    char buffer2[RANDOMSTR_MAX_LENGTH];

    start = clock();

    for (int i = 0; i < num_tests; i++)
    {
        str1 = random_string(buffer1);
        str2 = random_string(buffer2);
        // Make sure to only time the comparison portion
        start = clock();
        compare_func(str1, str2);
        end = clock();
        time_taken += ((double)(end - start)) / CLOCKS_PER_SEC;
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
    char buffer[RANDOMSTR_MAX_LENGTH];
    for (int i = 0; i < 1000; i++)
    {
        test_str = random_string(buffer);
        score = compare_func(test_str, test_str);
        if (score != 1.0)
        {
            TEST_FAIL_FMT("Equality test failed: %f \n      %s", score, test_str);
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
    char buffer1[RANDOMSTR_MAX_LENGTH];
    char buffer2[RANDOMSTR_MAX_LENGTH];
    double score1;
    double score2;
    for (int i = 0; i < 1000; i++)
    {
        str1 = random_string(buffer1);
        str2 = random_string(buffer2);
        score1 = compare_func(str1, str2);
        score2 = compare_func(str2, str1);
        if (score1 != score2)
        {
            TEST_FAIL_FMT("Reversibility test failed\n      %f vs %f\n      %s\n      %s", score1, score2, str1, str2);
            return;
        }
    }
    TEST_PASS("Reversibility test passed for all 1,000 tests");
}

// Test that func(str1, str2) == 0.0 if str1 and str2 share 0 characters
void inequality_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    char* str2;
    char buffer1[RANDOMSTR_MAX_LENGTH];
    char buffer2[RANDOMSTR_MAX_LENGTH];
    for (int i = 0; i < 1000; i++)
    {
        str1 = random_string_charset(buffer1, CHARSET_NUMBERS);
        str2 = random_string_charset(buffer2, CHARSET_UPPERCASE);
        if (compare_func(str1, str2) != 0.0)
        {
            TEST_FAIL_FMT("Inequality test failed\n      %s\n      %s", str1, str2);
            return;
        }
    }
    TEST_PASS("Inequality test passed for all 1,000 tests");
}

// test that func(str1, "") == 0 for any str1 != ""
void one_empty_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    char buffer1[RANDOMSTR_MAX_LENGTH];
    double score;
    for (int i = 0; i < 100; i++)
    {
        str1 = random_string(buffer1);
        score = compare_func(str1, "");
        if (score != 0)
        {
            TEST_FAIL_FMT("Empty string test failed: Score %f on string %s", score, str1);
            return;
        }
    }
    TEST_PASS("Empty string test passed for all 1,000 tests");
}

// test that 0.0 <= func(str1, str2) <= 1.0 for any valid str1, str2
void score_range_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    char* str2;
    char buffer1[RANDOMSTR_MAX_LENGTH];
    char buffer2[RANDOMSTR_MAX_LENGTH];
    double score;
    for (int i = 0; i < 1000; i++)
    {
        str1 = random_string(buffer1);
        str2 = random_string(buffer2);
        score = compare_func(str1, str2);
        if (score < 0.0 || score > 1.0)
        {
            TEST_FAIL_FMT(
                "Score range failed: %f on \n      %s\n      %s", score, str1, str2
            );
            return;
        }
    }
    TEST_PASS("Score range met for all 1,000 tests");

}

// test that 10000 runs of func executes within 1 second
void benchmark_test(double(*compare_func)(const char*, const char*))
{
    char* str1;
    char* str2;
    char buffer1[RANDOMSTR_MAX_LENGTH];
    char buffer2[RANDOMSTR_MAX_LENGTH];

    clock_t t_start, t_end;
    double time_taken = 0;
    
    t_start = clock();

    // 10k passes
    for (int num_tests = 0; num_tests < 10000; num_tests++)
    {

        str1 = random_string(buffer1);
        str2 = random_string(buffer2);
        if (time_taken > 1.0)
        {
            TEST_FAIL_FMT(
                "Benchmark test failed: %d out of 10000 tests in 1 second",
                num_tests
            );
            return;
        }
        // Only time the comparison portion
        t_start = clock();
        compare_func(str1, str2);
        t_end = clock();
        time_taken += ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
    }
    // 10k passes should be done in less than a second
    TEST_PASS_FMT(
        "Benchmark test succeeded: 10000 tests completed in %f seconds", time_taken
    );
}

// test that funct(str1, str2) == 1.0 if str1 is a subset of str2 or vice versa
void subset_test(double(*compare_func)(const char*, const char*))
{

    char* prefix;
    char* base_str;
    char* suffix;
    char* to_compare;

    char bufferBase[RANDOMSTR_MAX_LENGTH];
    char bufferPrefix[RANDOMSTR_MAX_LENGTH];
    char bufferSuffix[RANDOMSTR_MAX_LENGTH];

    char bufferConcat[3 * RANDOMSTR_MAX_LENGTH];

    int substr_type; // randomly generated, 0-2
                     // 0 - prefix, 1 - suffix, 2 - both


    double score;

    for (int i = 0; i < 1000; i++)
    {
        substr_type = rand() % 3;
        base_str = random_string(bufferBase);
        prefix = random_string(bufferPrefix);
        suffix = random_string(bufferSuffix);
        switch (substr_type)
        {

            case 0:  // Prefix
                to_compare = string_concat(bufferConcat, 2, prefix, base_str);
                break;
            case 1:  // Suffix
                to_compare = string_concat(bufferConcat, 2, base_str, suffix);
                break;
            case 2:
                to_compare = string_concat(bufferConcat, 3, prefix, base_str, suffix);
                break;
            default:
                to_compare = strcpy(bufferConcat, base_str);
        }

        score = compare_func(base_str, to_compare);

        if (score != 1.0)
        {
            TEST_FAIL_FMT(
                "Subset score not 1.0 on strings\n      %s\n      %s",
                base_str, to_compare
            );
            return;
        }
    }
    TEST_PASS("Subset test passed on all 1,000 tests");
}

void extended_charset_test(double(*compare_func)(const char*, const char*))
{
    // Double test here - checks both score range and extended charset
    // (128-255 chars)

    // Note that one failure condition for this test is crashing
    // Maybe I should come up with a different way?
    char* str1;
    char* str2;
    char buffer1[RANDOMSTR_MAX_LENGTH];
    char buffer2[RANDOMSTR_MAX_LENGTH];
    double score;
    for (int i = 0; i < 1000; i++)
    {
        str1 = random_string_charset(buffer1, CHARSET_EXTENDED);
        str2 = random_string_charset(buffer2, CHARSET_EXTENDED);
        score = compare_func(str1, str2);
        if (score < 0 || score > 1)
        {
            TEST_FAIL_FMT(
                "Extended Charset failed with score %f\n      %s\n      %s",
                score, str1, str2
            );
            return;
        }
    }
    TEST_PASS("Extended charsets supported over 1000 tests");
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
    extended_charset_test(compare_func);

}


/* =======================================================================================
INDIVIDUAL FUNCTION TESTS
========================================================================================*/
void test_cdist_score()
{
    string_comparison_test(cdist_score);
    ASSERT_EQUAL_DOUBLE(cdist_score("abcd", "abzz"), 0.5);
}


void test_longest_substring()
{
    int len;
    const char* substr;
    char buffer[256];

    // test with shorter string first
    len = longest_substring("dessert", "stressed", &substr);
    substring(buffer, substr, len);
    ASSERT_EQUAL_INT(len, 4);
    ASSERT_EQUAL_STR(buffer, "esse");

    // test with shorter string second
    len = longest_substring("stressed", "dessert", &substr);
    substring(buffer, substr, len);
    ASSERT_EQUAL_INT(len, 4);
    ASSERT_EQUAL_STR(buffer, "esse");

    len = longest_substring("hello", "", &substr);
    substring(buffer, substr, len);
    ASSERT_EQUAL_INT(len, 0);
    ASSERT_EQUAL_STR(buffer, "");


    len = longest_substring("", "", &substr);
    substring(buffer, substr, len);
    ASSERT_EQUAL_INT(len, 0);
    ASSERT_EQUAL_STR(buffer, "");

    len = longest_substring("ultimate", "mutilate", &substr);
    substring(buffer, substr, len);
    ASSERT_EQUAL_INT(len, 3);
    ASSERT_EQUAL_STR(buffer, "ate");

    len = longest_substring("bring", "brung", &substr);
    substring(buffer, substr, len);
    ASSERT_EQUAL_INT(len, 2);
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
    ADD_CASE(test_cdist_score);

    ADD_CASE(test_longest_substring);
    ADD_CASE(test_lss_major);
    ADD_CASE(test_lss_minor);


    ADD_CASE(test_fss_major);
    ADD_CASE(test_fss_minor);
    ADD_CASE(test_adjusted_fss_major);
    ADD_CASE(test_adjusted_fss_minor);

    ADD_CASE(test_levenshtein_major);
    ADD_CASE(test_levenshtein_minor);
    EWENIT_END_VERBOSE;

    return 0;
}