/*----------------------------------------------------------------------------------------
calc_groups.h

For use with methods fss_score methods

Calc group - stores a linked list of items representing character matches between
str1 and str2.

Each item in a CalcGroup represents a matching 

New potential character matches between one string and another are assessed against
each item in the CalcGroup, appending to an existing if both indices are higher
than on
----------------------------------------------------------------------------------------*/


#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// "private" struct holding indices and references to next linked _calcitem
typedef struct CalcItem {
    int idx1;
    int idx2;
    struct CalcItem* next;
} _calcitem;

// Manager struct for CalcGroup
typedef struct CalcGroup {
    int idx2_min;           // Lowest idx2 on a _calcitem head
    int length;             // Number of linked _calclist structs (# of groups)
    int matches;            // Total number of _calcitem structs (# of entries)
    int offset_difference;  // Total difference in idx2 - idx1 offsets
    _calcitem* first;       // Link to first _calclist in chain
} CalcGroup;

/* INITIALIZATION AND DECONSTRUCTION */

_calcitem* _calcitem_init(int idx1, int idx2)
{
    _calcitem* item = (_calcitem*)malloc(sizeof(_calcitem));
    item->idx1 = idx1;
    item->idx2 = idx2;
    item->next = NULL;
}

CalcGroup* CalcGroup_init()
{
    CalcGroup* group = (CalcGroup*)malloc(sizeof(CalcGroup));
    group->length = 0;              
    group->matches = 0;
    group->offset_difference = 0;         
    group->idx2_min = INT_MAX; 
    group->first = NULL;
    return group;
}

/*
NOTE TO SELF:
CalcGroup keeps track of grand total offset difference. The final score
should be tabulated as:

total score = 
    (num matches * l2) - total_offset_sum
    ______________________________________
    l2 * l1

Where l2 = len(longer string) -2 and l1 = len(shorter string) - 1

*/

void _calcitem_deconstruct(_calcitem* item)
{
    _calcitem* prev = NULL;
    _calcitem* current = item;
    while (current != NULL)
    {
        // Move to next and free this one
        prev = current;
        current = current->next;
        free(prev);
    }
}

void CalcGroup_deconstruct(CalcGroup* group)
{
    // Begin chain of _calcitem deconstruction
    _calcitem_deconstruct(group->first);
    free(group);
}

/* PRINT/AUDIT METHODS */

// Chain through _calcitems, printing each idx1, idx2 combo
void _calcitem_print(_calcitem* item)
{
    for (_calcitem* current = item; current != NULL; current = current->next)
    {
        printf("(%d, %d)", current->idx1, current->idx2);
        if (current->next != NULL)
            printf(", ");
    }
}

// Trigger _calclist print chain
void CalcGroup_print(CalcGroup* group)
{
    if (group == NULL)
        return;
    printf("[");
    _calcitem_print(group->first);
    printf("]\n");
    // Now display properties
    printf("Length: %d\n", group->length);
    printf("Matches %d\n", group->matches);
    printf("Offset difference %d\n", group->offset_difference);
    printf("Min Idx2 %d\n", group->idx2_min);
}

/* PRIVATE METHODS */

// Insert a new _calcitem into a _calcitem chain (at item_head) and return new item
// as new head
_calcitem* _calcitem_insert(_calcitem* item, int idx1, int idx2)
{
    _calcitem* new_item = _calcitem_init(idx1, idx2);
    new_item->next = item;
    return new_item;
}

// Updates the values for a provided _calcitem
void _calcitem_update(_calcitem* item, int idx1, int idx2)
{
    item->idx1 = idx1;
    item->idx2 = idx2;
}


/* PUBLIC METHODS */

// Add a new _calcitem to group at idx1, idx2
void CalcGroup_addNew(CalcGroup* group, int idx1, int idx2)
{
    // new _calcitem
    _calcitem* new_item = _calcitem_init(idx1, idx2);

    // Add item to list
    new_item->next = group->first;
    group->first = new_item;

    // Handle list properties
    group->length++;
    if (idx2 < group->idx2_min)
        group->idx2_min = idx2;

}

// Attempts to add a new _calcitem with (idx1, idx2) at the best possible location by 
// minimizing offset difference by current indices idx1 and idx2 vs a _calcitem's
// idx1 and idx2.
// Returns a boolean flag indicating if placement was successful.
bool CalcGroup_addBest(CalcGroup* group, int idx1, int idx2)
{
    // If new item cannot be placed, return false
    if (idx2 < group->idx2_min || group->length == 0)
        return false;

   int loop_idx1;                   // idx1 on current item in loop
   int loop_idx2;                   // idx2 on current item in loop

   int loop_osdiff;                 // Offset difference in current loop

   int min_osdiff_found = INT_MAX;  // Lowest difference in offsets for idx1,idx2
   int secondmin_idx2 = INT_MAX;    // Second minimum idx2 in group
   _calcitem* best_item = NULL;     // Best candidate for placement (lowest odiff)

   for (_calcitem* current = group->first; current != NULL; current = current->next)
   {
        loop_idx1 = current->idx1;
        loop_idx2 = current->idx2;

        // Maintain tracking second smallest current idx2 (this only works because
        // no idx2 can be repeated in group, as they represent character indices)
        if (loop_idx2 > group->idx2_min && loop_idx2 < secondmin_idx2)
            secondmin_idx2 = loop_idx2;

        // Skip this loop if we cannot place (loop_idx2 too big)
        if (loop_idx2 > idx2)
            continue;

        loop_osdiff = abs((idx2 - loop_idx2) - (idx1 - loop_idx1));

        printf(
            "    item (%d, %d) has osdiff %d\n",
            loop_idx1, loop_idx2, loop_osdiff
        );

        // Check if we found a better match
        if (loop_osdiff < min_osdiff_found)
        {
            min_osdiff_found = loop_osdiff;
            best_item = current;
        }
   }

    // Didn't find any valid items - no placements
   if (best_item == NULL)
        return false;

    // Need to update min_idx2 if its _calcitem replaced it
    if (best_item->idx2 == group->idx2_min)
    {
        // Use replacement if it is smaller than second minimum idx2
        if (idx2 < secondmin_idx2)
            group->idx2_min = idx2;
        // Otherwise update to second minimum
        else 
            group->idx2_min = secondmin_idx2;
    }

    // Update with our found item
    group->matches++;
    group->offset_difference += min_osdiff_found;  // best_item should have lowest offset

    // Finally, update the element in question
    _calcitem_update(best_item, idx1, idx2);
    return true;
}

// Attempt to add a new _calcitem with (idx1, idx2) at the first possible placement
// location.
// Returns a boolean flag indicating if placement was successful.
bool CalcGroup_addFirst(CalcGroup* group, int idx1, int idx2)
{
    // If new item cannot be placed, return false
    if (idx2 < group->idx2_min || group->length == 0)
        return false;

   int loop_idx1;                   // idx1 on current item in loop
   int loop_idx2;                   // idx2 on current item in loop

   int secondmin_idx2 = INT_MAX;    // Second minimum idx2 in group
   _calcitem* best_item = NULL;     // Best candidate for placement (first valid found)
   int osdiff_toadd = 0;            // Offset associated with best_item;

   for (_calcitem* current = group->first; current != NULL; current = current->next)
   {
        loop_idx1 = current->idx1;
        loop_idx2 = current->idx2;

        // Maintain tracking second smallest current idx2 (this only works because
        // no idx2 can be repeated in group, as they represent character indices)
        if (loop_idx2 > group->idx2_min && loop_idx2 < secondmin_idx2)
            secondmin_idx2 = loop_idx2;

        // Skip this loop if we cannot place (loop_idx2 too big)
        if (loop_idx2 > idx2)
            continue;

        // Set best_item the first time we find a valid element & save its offset
        if (best_item == NULL)
        {
            osdiff_toadd = abs((idx2 - loop_idx2) - (idx1 - loop_idx1));
            best_item = current;
        }

   }

    // Didn't find any valid items - no placements
   if (best_item == NULL)
        return false;

    // Need to update min_idx2 if its _calcitem replaced it
    if (best_item->idx2 == group->idx2_min)
    {
        // Use replacement if it is smaller than second minimum idx2
        if (idx2 < secondmin_idx2)
            group->idx2_min = idx2;
        // Otherwise update to second minimum
        else 
            group->idx2_min = secondmin_idx2;
    }

    // Update with our found item
    group->matches++;
    group->offset_difference += osdiff_toadd;  // best_item should have lowest offset

    // Finally, update the element in question
    _calcitem_update(best_item, idx1, idx2);
    return true;
}