#include "c_version\double_linked_list.h"
#include "c_version\nested_list.h"
#include "c_version\order_score.h"
#include "c_version\calc_groups.h"

int dll_test()
{
    Dll* my_list = Dll_init();
    DllItem* item1;

    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
            Dll_insert(my_list, i);
        else
            Dll_append(my_list, i);
    }
    Dll_print(my_list);
    Dll_deconstruct(my_list);
}

int nl_test()
{
    NList* all_groups = NList_init();

    NList* group1 = NList_appendList(all_groups);
    NList* entry1 = NList_appendList(group1);

    NListItem* data1 = NList_append(entry1, 5);
    NListItem* data2 = NList_append(entry1, 6);

    NList* entry2 = NList_appendList(group1);
    NListItem* data3 = NList_append(entry2, 6);
    NListItem* data4 = NList_append(entry2, 8);

    NList_print(all_groups);

    // Cleanup
    NList_deconstruct(all_groups);
}

int oscore_test()
{
    order_score("stressed", "dessert");
}

int calc_groups_test()
{
    CalcGroup* group = CalcGroup_init();

    char str1[] = "dessert";
    char str2[] = "stressed";
    // S T R E S S E D
    // 0 1 2 3 4 5 6 7

    // idx1 indices
    int pairings_left[] = {0, 1, 2, 3, 4, 5, 6}
    // idx2 indices
    int pairings_right[] = {7, }

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

int main()
{
    calc_groups_test();

    return 0;
}