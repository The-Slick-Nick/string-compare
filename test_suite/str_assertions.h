/*
str_assertions.h

Assertion functions revolving around strings
*/
#include <string.h>
#include "test_components.h"

int assert_equal_str(TestSuite* ts, char* test_name, char* val1, char* val2)
{
    int idx;
    int len1 = strlen(val1);
    int len2 = strlen(val2);
    int test_status;
    char chr1, chr2;
    char* fail_msg;

    if(len1 != len2)
    {
        fail_msg = format_string(
            "String lengths differ: %d vs %d\n%s\n%s", len1, len2, val1, val2
        );
        test_status = TestSuite_fail(ts, test_name, fail_msg);
        free(fail_msg);
        return test_status;
    }

    for(idx = 0; idx < len1; idx++)
    {
        chr1 = *(val1 + idx);
        chr2 = *(val2 + idx);
        if(chr1 != chr2)
        {
            char* indicator = (char*)malloc((idx + 1) * sizeof(char));
            for(int i = 0; i < idx; i++)
            {
                *(indicator + i) = ' ';
            }
            *(indicator + idx) = '^';

            fail_msg = format_string(
                "Strings differ at index %d\n%s\n%s\n%s", idx, val1, val2, indicator
            );
            test_status = TestSuite_fail(ts, test_name, fail_msg);
            free(indicator);
            free(fail_msg);
            return test_status;
        }
    }

    return TestSuite_pass(ts);
}

int assert_not_equal_str(TestSuite* ts, char* test_name, char* val1, char* val2)
{
    if(strcmp(val1, val2) != 0)
        return TestSuite_pass(ts);

    char* fail_msg = format_string(
        "Strings equal\n%s\n%s\n", val1, val2
    );
    int test_status = TestSuite_fail(ts, test_name, fail_msg);
    free(fail_msg);
    return test_status;
}