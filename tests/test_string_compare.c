#include "../test_suite/test_suite.h"
#include "../c_version/letter_score.h"



void test_letter_score(TestSuite *ts)
{
    double score;
    // Exact equal distribution - should be 1

    score = letter_score("abbbcdef", "bbbcdfea");
    assert_equal_double(ts, "letter score EQUAL DIST", score, 1);

    // Exact different distribution - should b 0
    score = letter_score("abcde", "zyxwv");
    assert_equal_double(ts, "letter score NONEQUAL DIST", score, 0);

    // Should be 50% similar
    score = letter_score("abcd", "abzz");
    assert_equal_double(ts, "letter score HALF EQUAL", score, 0.5);
}


int main()
{
    TestSuite *ts = TestSuite_init();

    test_letter_score(ts);

    TestSuite_print(ts);
    TestSuite_deconstruct(ts);
}