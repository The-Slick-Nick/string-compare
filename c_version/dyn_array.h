#include <stdlib.h>

struct dArray {
    int* contents;  // Pointer to array
    int size;  // Current max number of elements
    int index;  // Index of rightmost unassigned location
};

struct dArray* dArray_init(int init_size)
// Initialize and return a new dynamic array
{
    struct dArray* to_return = (struct dArray*)malloc(sizeof(struct dArray));

    to_return->size = init_size;
    to_return->index = 0;
    to_return->contents = (int*)malloc(init_size*sizeof(int));
    return to_return;
}

void dArray_expand(struct dArray* arr)
// Resize dynamic array larger. Allocates a new array double the current size and transfers contents over.
{
    int* new_contents = (int*)malloc(2 * arr->size * sizeof(int));
    int* hold;
    int i;

    // Transfer each element of data to new array
    for(i = 0; i < arr->index; i++)
    {
        *(new_contents + i) = *(arr->contents + i);
    }

    // Update content reference to new array
    hold = arr->contents;
    arr->contents = new_contents;
    free(hold);

    // Double current size
    arr->size *= 2;
}

void dArray_append(struct dArray* arr, int data)
// Add new data to right end of given dynamic array. Resize if necessary
{
    if(arr->index >= arr->size)
    {
        dArray_expand(arr);
    }
    *(arr->contents + arr->index) = data;
    arr->index++;
}


