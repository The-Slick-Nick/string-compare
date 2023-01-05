/*
strlist.h

Provides a definition of a linked list where each
element has both a title and content.

Used by TestSuite for tracking error messages along
with the functions that generated that error.
*/

#include <stdlib.h>
#include <string.h>
#include "test_codes.h"

#ifndef INCLUDE_GUARD_STRLIST
#define INCLUDE_GUARD_STRLIST

// Copies some input_str into a newly allocated character array, then returns its pointer
char* copy_string(char* input_str)
{
    int length = strlen(input_str);
    char* to_return = (char*)malloc((1 + length) * sizeof(char));
    strcpy(to_return, input_str);
    return to_return;
}

// Single element in a linked list
typedef struct ListItem {
    char* title;        // Header message for list element
    char* content;      // Message contents of list element
    int status;         // Integer status code for list element (0, -1, -2)
    struct ListItem* next;
} _listitem;

// Linked list of character arrays (strings)
typedef struct StrList {
    _listitem* head;
    _listitem* tail;
    int size;
} StrList;

_listitem* _listitem_init(char* title, char* content, int status)
// Allocate and return a ListItem struct
{
    _listitem* li = (_listitem*)malloc(sizeof(_listitem));
    // To handle both literals and malloc'ed strings, make copy here regardless
    li->title = copy_string(title);
    li->content = copy_string(content);
    li->status = status;
    li->next = NULL;
    return li;
}

StrList* StrList_init()
// Allocate and return a StrList struct
{
    StrList* list = (StrList*)malloc(sizeof(StrList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Frees a ListItem's char arrays then frees ListItem
void _listitem_deconstruct(_listitem* li)
{
    free(li->title);
    free(li->content);
    free(li);
}

// Frees StrList and all referenced character strings and _listitem structs
void StrList_deconstruct(StrList* list)
{
    _listitem* hold = NULL;
    _listitem* current = list->head;

    while(current != NULL)
    {
        // Store temp ref to current
        hold = current;

        // Move to next item in list
        current = current->next;

        // Free _listitem considered this round
        _listitem_deconstruct(hold);
    }
    // Finally, free StrList handler struct 
    free(list);
}

// Add a new entry to left side of list
void StrList_insert(StrList* list, char* title, char* content, int status)
{
    _listitem* new_item = _listitem_init(title, content, status);
    if(list->head == NULL && list->tail == NULL)
    // Implies size == 0
    {
        list->head = new_item;
        list->tail = new_item;
    }
    else
    {
        new_item->next = list->head;
        list->head = new_item;
    }
    list->size++;
}

// Add a new entry to right side of list
void StrList_append(StrList* list, char* title, char* content, int status)
{
    _listitem* new_item = _listitem_init(title, content, status);
    if(list->head == NULL && list->tail == NULL)
    // Implies size == 0
    {
        list->head = new_item;
        list->tail = new_item;
    }
    else
    {
        list->tail->next = new_item;
        list->tail = new_item;
    }
    list->size++;
}

#endif