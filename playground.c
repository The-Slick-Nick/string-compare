#include "tests\test_utils\random_string.h"
#include "c_version\components\calc_groups.h"
#include "tests/test_utils/string_concat.h"


int calc_groups_test()
{
    CalcGroup* group = CalcGroup_init();

    char str1[] = "dessert";
    char str2[] = "stressed";
    // S T R E S S E D
    // 0 1 2 3 4 5 6 7

    for (int i = 1; i < 100; i++)
    {
        for (int j = 1; j < 100; j++)
        {
            if (!CalcGroup_addBest(group, i, j))
                CalcGroup_addNew(group, i, j);
        }
    }
    CalcGroup_print(group);
    CalcGroup_deconstruct(group);
}

int random_string_test()
{
    for (int i = 0; i < 5; i++)
    {
        char* str1 = random_string();
        printf("%s\n", str1);
        free(str1);
    }
}

int main()
{
    char* str1 = "hello";
    char* str2 = "goodbye";
    char* combined;
    combined = string_concat(2, str1, str2);
    printf("str1 %s\nstr2 %s\ncombined %s\n", str1, str2, combined);
    free(combined);
}