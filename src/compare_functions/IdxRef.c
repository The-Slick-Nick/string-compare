#include "IdxRef.h"
#include <stdlib.h>
#include <stdbool.h>


/* API definitions */

void IdxRef_build(IdxRef* self, const char* str, int* chr_counts, int* ptr_ref)
{
    int i;
    unsigned char chri;
    int current_offset;
    int total_size = 0;
    int min_idx[256] = {0};

    // Point IdxRef tracking arrays to what was passed
    self->chr_counts = chr_counts;
    self->ptr_ref = ptr_ref;

    // Gather string information before building
    for (i = 0; *(str + i) != '\0'; i++)
    {
        chri = (unsigned char)(*(str + i));
        total_size++;
        self->chr_counts[chri]++;
    }

    // Each character from str gets a "slot", with one extra allocated.
    // We allocate one extra slot, as index 0 is used for "unreserved", so we never
    // actually use it as an index.
    self->idx_arr = (int*)malloc((1 + total_size) * sizeof(int));
    *(self->idx_arr) = -1;

    current_offset = 1;

    for (i = 0; *(str + i) != '\0'; i++)
    {
        chri = (unsigned char)(*(str + i)); // Cast as unsigned char

        if (self->ptr_ref[chri] == 0)  // No block yet reserved in idx_arr
        {
            // Assign next available block to current character (at current offset)
            self->ptr_ref[chri] = current_offset;

            // Reserve a block in idx_ref, with size equal to # of this character
            current_offset += self->chr_counts[chri];
        }

        // Set this instance of this character in idx_arr
        *(self->idx_arr + self->ptr_ref[chri] + min_idx[chri]) = i;
        min_idx[chri]++;
    }

    self->active = true;

}

int IdxRef_getIndex(IdxRef* self, unsigned char chr, int chr_num)
{

    if (!self->active)
        return -1;

    // If we don't have enough of defined character
    if (self->chr_counts[chr] < chr_num)
        return -1;

    return *(self->idx_arr + self->ptr_ref[chr] + chr_num);
}


int IdxRef_getChrCount(IdxRef* self, unsigned char chr)
{
    if (!self->active)
        return -1;

    return self->chr_counts[chr];
}

void IdxRef_deconstruct(IdxRef* self)
{
    if (self->idx_arr != NULL)
        free(self->idx_arr);

    self->active = false;
}