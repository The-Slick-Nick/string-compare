#include "c_version\double_linked_list.h"
#include "c_version\nested_list.h"
#include "c_version\order_score.h"

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

int main()
{
    oscore_test();

    return 0;
}