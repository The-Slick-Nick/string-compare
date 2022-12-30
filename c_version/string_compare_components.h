#include <stdlib.h>
#include <stdio.h>

struct listItem {
    int data;
    struct listItem* next;
    struct listItem* previous;
} listItem_default = {0, NULL, NULL};

struct listHead {
    struct listItem* first;
    struct listItem* last;
    int length;
} listHead_default = {NULL, NULL, 0};


struct listHead* list_init()
{
    struct listHead* new_list = (struct listHead*)malloc(sizeof(struct listHead));
    new_list->length = 0;
    new_list->first = NULL;
    new_list->last = NULL;
    return new_list;
}


void list_print(struct listHead* head)
/*
Print linked list, starting at provided listItem head
*/
{
    struct listItem* current = head->first;
    printf("[");
    while(current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("]\n");
}

void list_insert(struct listHead* head, int data)
/*
Add a new element of data to current linked list from the left.
*/
{
    struct listItem* new_item = (struct listItem*)malloc(sizeof(struct listItem));

    // set data
    new_item->data = data;

    // set listItem pointers
    new_item->next = head->first;

    // adjust head
    if(head->last == NULL)
    // If no elements previously there, also set last
    {
        head->last = new_item;
    }
    head->first = new_item;
    head->length++;
}

void list_append(struct listHead* head, int data)
/*
Add a new element of data to current linked list from the right.
*/
{
    struct listItem* new_item = (struct listItem*)malloc(sizeof(struct listItem));

    // set data
    new_item->data = data;

    // set listItem pointers
    new_item->next = NULL;
    if(head->last != NULL)
    {
        head->last->next = new_item;
    }

    // adjust head
    if(head->first == NULL)
    // If no elements previously there, also set first
    {
        head->first = new_item;
    }
    head->last = new_item;
    head->length++;
}

void list_remove(struct listHead* head, int data)
/*
Remove the first list element where data equal to provided, traversing
from left to right. (head->first->next->last)
If none exist, nothing will be removed.

Returns pointer to removed listItem, if any. Returns NULL if no listItem was
removed.
*/
{
    // Resolve edge cases near the head
    if(head->length == 0)
    {
        return;
    }
    else if(head->length == 1)
    {
        if(head->first->data == data)
        {
            struct listItem* hold = head->first;
            head->first = NULL;
            head->last = NULL;
            head->length--;
            free(hold);

        }
        return;
    }
    // length >= 2 - check first item independently
    if(head->first->data == data)
    {
        struct listItem* hold = head->first;
        head->first = head->first->next;
        head->length--;
        free(hold);
    } 

    // since length >= 2 here, we start at 2nd element to ensure previous != NULL
    struct listItem* prev = head->first;
    struct listItem* current = head->first->next;

    while(current != NULL)
    {
        if(current->data == data)
        {
            prev->next = current->next;
            head->length--;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int list_pop_next_highest(struct listHead* head, int target)
/*
Traverses list left to right until it finds a listItem with data > target. Removes that element from list and returns
that element's data. If none found higher than target, returns -1.

Works only for positive integers.
*/
{
    int to_return;  // Integer to store data to return if necessary

    // Check edge cases of length == 0 and length == 1
    if(head->length == 0)
    {
        return -1;
    }
    else if(head->length == 1)
    {
        if(head->first->data > target)
        {
            struct listItem* temp = head->first;
            to_return = temp->data;
            head->first = NULL;
            head->last = NULL;
            head->length--;
            free(temp);
            return to_return;
        }
        else
        {
            return -1;
        }
    }

    struct listItem* previous = head->first;
    struct listItem* current = previous->next;

    while(current != NULL)
    {
        if(current->data > target)
        {
            to_return = current->data;
            previous->next = current->next;
            head->length--;
            free(current);
            return to_return;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}


char* list_to_char_array(struct listHead* head)
{
    int build_i = 0;
    char* to_return = (char*)malloc((1 + head->length) * sizeof(char));
    struct listItem* current = head->first;

    while(current != NULL)
    {
        *(to_return + build_i) = current->data;
        build_i++;
        current = current->next;
    }
    *(to_return + build_i) = '\0';

    return to_return;
}


/*
struct node {
    int data;
    int key;
    struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

// displays the list
void print_list() {
    struct node *ptr = head;
    printf("\n[ ");

    while(ptr != NULL)
    {
        printf("(%d, %d) ",ptr->key, ptr-> data);
        ptr = ptr->next;
    }
}

// inserts link at first location
void insert_first(int key, int data)
{
    // create a new empty node named link
    struct node *link = (struct node*) malloc(sizeof(struct node));

    // assign key & data to new node
    link->key = key;
    link->data = data;

    // point new node to current (old) first node
    link->next = head;

    // point `head` of previous first node to new node
    head = link;
}

// delete first item
struct node* delete_first()
{
    // save reference to first link
    struct node *temp_link = head;

    // make the current `next` the new head
    head = head->next;

    // return deleted link
    return temp_link;
}

// identify if list is empty
bool is_empty()
{
    return head == NULL;
}

int length()
{
    int length = 0;
    struct node *current;

    // Traverse list starting from head and keep track "jumps" until we reach end
    for(current = head; current != NULL; current = current->next)
    {
        length++;
    }

    return length;
}

// find link with the given key
struct node* find_key(int key)
{
    // begin at first link
    struct node* current = head;

    // early exit if list is empty
    if(head == NULL)
    {
        return NULL;
    }

    // traverse list
    while(current->key != key)
    {
        // check if we're on last node
        if(current->next == NULL)
        {
            return NULL;
        }
        // otherwise check next link
        else
        {
            current = current->next;
        }
    }
    // if exited naturally, key was found. Return link
    return current;
}

// delete link with provided key
struct node* delete_key(int key)
{
    // begin at first link
    struct node* current = head;
    struct node* previous = NULL;

    // if list empty
    if(head == NULL)
    {
        return NULL;
    }

    // traverse list to find key
    while(current-> key != key)
    {
        // Early exit if end of list found without key present
        if(current->next == NULL)
        {
            return NULL;
        }
        else
        {
            // Save link to previous
            previous = current;
            // Move to next node
            current = current->next;
        }
    }

    // Natural while exit - key found
    if(current == head)
    // if key was on the first item in list, no need to use previous
    {
        head = head->next;
    }
    // otherwise, jump over current by linking previous to next
    else
    {
        previous->next = current->next;
    }

    // return the link that was deleted
    return current;
}

int main()
{

}
*/