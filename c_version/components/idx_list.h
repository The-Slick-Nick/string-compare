/*========================================================================================
idx_map.h

Linked list structure of character indices
========================================================================================*/
#include <stdlib.h>

typedef struct IdxListItem {
    int idx;
    struct IdxListItem* next;
    struct IdxListItem* prev;
} IdxItem;


typedef struct {
    int length;
    IdxItem* head;
    IdxItem* tail;
} IdxList;

/*========================================================================================
INITIALIZATION & DECONSTRUCTION
========================================================================================*/

IdxItem* IdxItem_init(int idx)
{
    IdxItem* item = (IdxItem*)malloc(sizeof(IdxItem));
    item->idx = idx;
    item->next = NULL;
    item->prev = NULL;
    return item;
}

IdxList* IdxList_init()
{
    IdxList* list = (IdxList*)malloc(sizeof(IdxList));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// No deconstruction method needed for IdxItem

void IdxList_deconstruct(IdxList* list)
{
    IdxItem* prev = NULL;
    IdxItem* cur = list->head;
    while (cur != NULL)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
    free(list);
}

/*========================================================================================
========================================================================================*/

// Add a new IdxItem to the right end of current list. Return pointer to newly created
// IdxItem
IdxItem* IdxList_append(IdxList* list, int idx)
{
    IdxItem* new_item = IdxItem_init(idx);

    if (list->head == NULL)
        list->head = new_item;

    if (list->tail != NULL)
        list->tail->next = new_item;
    
    new_item->prev = list->tail;
    list->tail = new_item;
    list->length++;
    return new_item;
}


void IdxList_removeItem(IdxList* list, IdxItem* item)
{
    if (item == NULL)
        return;
    
    if (item->prev != NULL)
        item->prev->next = item->next;

    if (item->next != NULL)
        item->next->prev = item->prev;

    if (item == list->head)
        list->head = list->head->next;

    if (item == list->tail)
        list->tail = list->tail->prev;


    list->length--;
    free(item);
}

int IdxList_popLeft(IdxList* list)
{
    int to_return = list->head->idx;
    IdxList_removeItem(list, list->head);
    return to_return;
}