/*
Doubly linked list
*/
#include <stdlib.h>
#include <stdio.h>

#ifndef INCLUDE_GUARD_DOUBLE_LINKED_LIST
#define INCLUDE_GUARD_DOUBLE_LINKED_LIST

typedef struct DoubleLinkedListItem {
    int data;
    struct DoubleLinkedListItem* next;
    struct DoubleLinkedListItem* prev;
} DllItem;

typedef struct DoubleLinkedList {
    int length;
    DllItem* first;
    DllItem* last;
} Dll;

// Initialize a DoubleLinkedListItem with data `data`
DllItem* DllItem_init(int data)
{
    DllItem* item = (DllItem*)malloc(sizeof(DllItem));
    item->data = data;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

// Initialize a DoubleLinkedList head struct with no data or elements
Dll* Dll_init()
{
    Dll* list = (Dll*)malloc(sizeof(Dll));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
}

// Free any memory allocated for a DoubleLinkedListItem `item`
void DllItem_deconstruct(DllItem* item)
{
    if (item == NULL)
        return;
    free(item);
}

// Free any memory allocated for a DoubleLinkedList `list`
void Dll_deconstruct(Dll* list)
{

    if (list == NULL)
        return;

    DllItem* prev = NULL;
    DllItem* current = list->first;

    while (current != NULL)
    {
        prev = current;
        current = current->next;
        DllItem_deconstruct(prev);
    }

    free(list);
}

// Insert a new DoubleLinkedListItem with `data` at left (front) of list
void Dll_insert(Dll* list, int data)
{
    // Setup new list item
    DllItem* item = DllItem_init(data);
    item->next = list->first;

    // Adding first element - first == last
    if (list->length == 0)
    {
        list->first = item;
        list->last = item;
    }
    // Update references
    else
    {
        list->first->prev = item;
        list->first = item;
    }

    list->length++;
}

// Insert a new DoubleLinkedListItem with `data` at right (end) of list
void Dll_append(Dll* list, int data)
{
    // Setup new list item
    DllItem* item = DllItem_init(data);
    item->prev = list->last;

    // Adding first element- first == last
    if (list->length == 0)
    {
        list->first = item;
        list->last = item;
    }
    // Update references
    else
    {
        list->last->next = item;
        list->last = item;
    }

    list->length++;

}

// Remove a DoubleLinkedListItem from DoubleLinkedList
// WARNING `li` must belong to `list`, otherwise shenanigans will occur
void Dll_remove(Dll* list, DllItem* item)
{

    DllItem* prev = item->prev;
    DllItem* next = item->next;

    if (item == list->first)
        list->first = next;

    if (item == list->last)
        list->last = prev;

    if (prev != NULL)
        prev->next = next;
    
    if (next != NULL)
        next->prev = prev;

    list->length--;
    free(item);
}

int Dll_print(Dll* list)
{
    DllItem* current;

    printf("[");
    for (current = list->first; current != NULL; current = current->next)
    {
        printf("%d", current->data);
        if (current->next != NULL)
            printf(", ");
    }
    printf("]\n");
}

#endif