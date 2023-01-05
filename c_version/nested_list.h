#include <stdlib.h>
#include <stdio.h>

#ifndef INCLUDE_GUARD_NESTED_LIST
#define INCLUDE_GUARD_NESTED_LIST

typedef struct NestedListItem {
    
    int data;                       // Data for this list item
    struct NestedListItem* next;    // Next item in current list
    struct NestedList* list;        // Link to next list in

} NListItem;

typedef struct NestedList {
    int length;
    NListItem* first;
    NListItem* last; 
} NList;


// Init and deconstruct prototypes
NListItem* NListItem_initData(int data);
NListItem* NListItem_initList();
NList* NList_init();
void NList_deconstruct(NList* list);
void NListItem_deconstruct(NListItem* item);


NListItem* NListItem_initData(int data)
{
    NListItem* item = (NListItem*)malloc(sizeof(NListItem));
    item->data = data;
    item->next = NULL;
    item->list = NULL;
    return item;
}

NListItem* NListItem_initList()
{
    NListItem* item = (NListItem*)malloc(sizeof(NListItem));
    item->next = NULL;
    item->list = NList_init();
    return item;
}

NList* NList_init()
{
    NList* list = (NList*)malloc(sizeof(NList));
    list->length = 0;
    list->first = NULL;
    list->last = NULL;
    return list;
}


// 
void NListItem_deconstruct(NListItem* item)
{
    if (item == NULL)
        return;

    NList_deconstruct(item->list);
    free(item);

}

// Free any memory allocated for a NList
void NList_deconstruct(NList* list)
{
    if (list == NULL)
        return;


    NListItem* prev = NULL;
    NListItem* current = list->first;

    while (current != NULL)
    {
        prev = current;
        current = current->next;
        NListItem_deconstruct(prev);
    }

    free(list);
}


// Manually append an already-created NestedListItem element into list
// Note that `item` should not already belong to another list, or shenanigans may occur
NListItem* NList_appendItem(NList* list, NListItem* item)
{
    if (list->first == NULL)
        list->first = item;

    if (list->last != NULL)
        list->last->next = item;

    list->last = item;
    list->length++;
    return item;
}

// Appends a data element to list. Returns that listItem
NListItem* NList_append(NList* list, int data)
{
    NListItem* item = NListItem_initData(data);
    NList_appendItem(list, item);
    return item;
}

// Adds a new NListItem element with an associated list. Returns reference to the new
// NListItem's list
NList* NList_appendList(NList* list)
{
    NListItem* item = NListItem_initList();
    NList_appendItem(list, item);
    return item->list;
}


// Print 
void NList_print(NList* list)
{
    NListItem* current;

    printf("[");

    current = list->first;
    while (current != NULL)
    {
        if (current->list != NULL)
            NList_print(current->list);
        // Only print data if no list is associated
        else
        {
            printf("%d", current->data);
            if (current->next != NULL)
                printf(", ");
        }
        current = current->next;
    }

    printf("]");

}

#endif