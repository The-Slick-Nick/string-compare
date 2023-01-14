/*========================================================================================
dynamicarray.h
Dynamic Array
========================================================================================*/
#include <stdlib.h>
#include <stdio.h>

#include "utility_functions.h"

/*========================================================================================
STRUCT DEFINITION
========================================================================================*/
typedef struct DynamicArray {
    size_t length;          // Current number of values in contents;
    int* contents;          // Pointer to integer array holding values
    size_t _size;              // Internal size of allocated contents
} DynArr;


/*========================================================================================
INITIALIZATION/DECONSTRUCTION
========================================================================================*/



// Macros for default construction
#define DYNARR { .length = 0, .contents = (int*)malloc(4 * sizeof(int)), ._size = 4}
#define DYNARR_PTR DynArr_init(4);

// Given an already allocated Dynamic Array, initialize its contents & values
void DynArr_build(DynArr* self, size_t init_size)
{
    // Set size to a power of 2 >= init_size
    self->_size = next_pow2(init_size);
    self->contents = (int*)malloc(self->_size * sizeof(int));
    self->length = 0;
}

DynArr* DynArr_init(size_t init_size)
{
    DynArr *self = (DynArr*)malloc(sizeof(DynArr));
    DynArr_build(self, init_size);
    return self;
}

void DynArr_deconstruct(DynArr* self)
{
    free(self->contents);
    free(self);
}


/*========================================================================================
Private methods
========================================================================================*/
void _DynArr_expand(DynArr* self)
{
    // Double current size
    self->_size = self->_size<<1;
    self->contents = realloc(self->contents, self->_size * sizeof(int));
    if (self->contents == NULL)
        exit(EXIT_FAILURE);
}

/*========================================================================================
Public methods
========================================================================================*/

void DynArr_append(DynArr* self, int new_val)
{
    while (self->length >= self->_size)
    {
        _DynArr_expand(self);
    }

    *(self->contents + self->length) = new_val;
    self->length++;
}

void DynArr_print(DynArr* self)
{
    printf("[");
    for (int i = 0; i < self->length; i++)
    {
        printf("%d", *(self->contents + i));
        if (i != self->length - 1)
            printf(", ");
    }
    printf("]\n");
}