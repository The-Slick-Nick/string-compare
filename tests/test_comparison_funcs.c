#include "D:\Projects\c-testsuite\test_suite\test_suite.c"
#include "../c_version/letter_score.h"

void test_letter_score()
{

    // Exact equal distribution - should be 1
    ASSERT_EQUAL_DOUBLE(letter_score("HELLO", "HELLO"), 1.0);

    // // Exact different distribution - should be 0
    ASSERT_EQUAL_DOUBLE(letter_score("ABCDE", "ZYXWV"), 0.0);

    // // Should be 50% similar
    ASSERT_EQUAL_DOUBLE(letter_score("ABCD", "ABZZ"), 0.5);

    // Reversibility
    ASSERT_EQUAL_DOUBLE(
        letter_score("THIS STRING", "THAT STRING"),
        letter_score("THAT STRING", "THIS STRING")
    );
}


int main()
{
    TEST_START;
    ADD_CASE(test_letter_score, "letter score");
    TEST_END;
}