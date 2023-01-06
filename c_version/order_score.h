/*
Computations for assessing the order similarity between strings
*/
#include <string.h>
#include <stdbool.h>
#include "double_linked_list.h"
#include "nested_list.h"


// First computation for order score
double __comp1__(char* str1, char* str2, int l1, int l2)
{
    printf("");
}

// Second computation for order score
double __comp2__(char* str1, char* str2, int l1, int l2)
{
    int idx1, idx2;
    char chr1, chr2;

    int current_idx2;
    int idx2_max_recorded;
    bool group_found;

    Dll* idx_ref[256] = {NULL};
    Dll* this_idx_ref;

    DllItem* dll_current;
    DllItem* to_remove;

    NListItem* current_calc_group;

    NListItem* calc_group_item;

    NList* new_calc_entry;
    NList* new_calc_group;

    NList* calc_groups = NList_init();

    // build character reference of str2 indices
    for (idx2 = 0; idx2 < l2; idx2++)
    {
        chr2 = str2[idx2];
        if(idx_ref[chr2] == NULL)
            idx_ref[chr2] = Dll_init();

        Dll_append(idx_ref[chr2], idx2);
    }

    for (int i = 0; i < 256; i++)
    {
        if (idx_ref[i] != NULL)
            Dll_print(idx_ref[i]);
    }

    for (idx1 = 0; idx1 < l1; idx1++)
    {
        chr1 = str1[idx1];
        this_idx_ref = idx_ref[chr1];
        if (this_idx_ref == NULL)
            continue;

        if (this_idx_ref->length == 0)
            continue;

        group_found = false;

        // Note that we need only check the first item - indices will be in
        // ascending order and thus, if n has no valid calc_group, n+1 will not either
        dll_current = this_idx_ref->first;
        idx2 = dll_current->data;

        current_calc_group = calc_groups->first;
        while (current_calc_group != NULL)
        {
            if (group_found)
                break;

            if (current_calc_group->list == NULL)
                break;

            if (current_calc_group->list->length == 0)
                break;

            idx2_max_recorded = current_calc_group->list->last->list->last->data;

            // Found an existing group to add this entry to
            if (idx2 > idx2_max_recorded)
            {
                group_found = true;
                // Move the matched index and idx1 into calc groups
                new_calc_entry = NList_appendList(current_calc_group->list);
                NList_append(new_calc_entry, idx1);
                NList_append(new_calc_entry, idx2);
            }

            current_calc_group = current_calc_group->next;
        }

        // did not find a valid existing group, create a new one
        if (!group_found)
        {
            new_calc_group = NList_appendList(calc_groups);
            new_calc_entry = NList_appendList(new_calc_group);
            // Append idx1 first so we have order [idx1, idx2]
            // could also do NList_insert(..., idx1) and NList_append(..., idx2) for safety
            NList_append(new_calc_entry, idx1);
            NList_append(new_calc_entry, dll_current->data);
        }

        // Remove this index entry
        to_remove = dll_current;
        dll_current = NULL;
        Dll_remove(this_idx_ref, to_remove);
    }

    NList_print(calc_groups);
    // calc groups - several layers deep nested list

    // Cleanup
    for (int i = 0; i < 256; i++)
        Dll_deconstruct(idx_ref[i]);

    NList_deconstruct(calc_groups);


}


double order_score(char* str1, char* str2)
{
    int l1 = strlen(str1);
    int l2 = strlen(str2);

    // Force the longer of the two strings into str2
    if (l1 > l2)
        return __comp2__(str2, str1, l2, l1);
    else
        return __comp2__(str1, str2, l1, l2);
    
}