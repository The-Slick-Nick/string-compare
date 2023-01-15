/*=======================================================================================
idx_ref.h

Framework for tracking the indices (by character) for characters in a given model string
========================================================================================*/
#ifndef INCLUDE_GUARD_IDXREF
#define INCLUDE_GUARD_IDXREF
#include <stdlib.h>


/*=======================================================================================
Structure Definition
========================================================================================*/

typedef struct {
    int* chr_counts;        // Array of counts per character
    int* ptr_ref;           // Array of pointer offsets per character to look into idx_arr
    int* idx_arr;           // Array of all indices found for a provided string
} IdxRef;


/*=======================================================================================
Public methods
========================================================================================*/

void IdxRef_build(IdxRef* self, const char* str)
{
    int i;
    char chri;
    int current_offset;
    int total_size = 0;
    int min_idx[256] = {0};

    self->chr_counts = (int*)calloc(256, sizeof(int));
    self->ptr_ref = (int*)calloc(256, sizeof(int));

    // Gather information about str before building
    for (i = 0; *(str + i) != '\0'; i++)
    {
        total_size++;
        (*(self->chr_counts + *(str + i)))++;
        // self->chr_counts[ *(str + i) ]++;
    }

    // One malloc
    // pointer ref 0 used as invalid, reserve index 0 for N/A. This is to take
    // advantage of calloc() setting to 0s and not manually using memset all to -1
    self->idx_arr = (int*)malloc((1 + total_size) * sizeof(int));
    current_offset = 1;


    for (i = 0; *(str + i) != '\0'; i++)
    {
        chri = *(str + i);
        // If still 0 (from allocation), we haven't pointed this char to a block yet
        if (*(self->ptr_ref + chri) == 0)
        {
            // Assign next available block to current character (at current_offset)
            *(self->ptr_ref + chri) = current_offset;
            // Set current_offset to start of next available block
            current_offset += *(self->chr_counts +chri);
        }

        // idx_arr[ptr_ref[chri] + min_idx[chri]]
        *(self->idx_arr + *(self->ptr_ref + chri) + min_idx[chri]) = i;
        min_idx[chri]++;
    }
}

// Retrieve ith index for a given character from idx_ref 
int IdxRef_getIndex(IdxRef* self, char chr, int chr_num)
{
    return *(self->idx_arr + *(self->ptr_ref + chr) + chr_num);
}

// Set the ith index for a given character in idx_ref to a new value
void IdxRef_updateIndex(IdxRef* self, char chr, int chr_num, int new_val)
{
    *(self->idx_arr + *(self->ptr_ref + chr) + chr_num) = new_val;
}

int IdxRef_getChrCount(IdxRef* self, char chr)
{
    return *(self->chr_counts + chr);
}

void IdxRef_deconstruct(IdxRef* self)
{
    free(self->chr_counts);
    free(self->ptr_ref);
    free(self->idx_arr);
}

#endif