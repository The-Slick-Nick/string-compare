/*========================================================================================
arrays.h

Utility macros for handling multidimensional arrays, stored as 1D arrays
========================================================================================*/
#ifndef INCLUDE_GUARD_ARRAYS
#define INCLUDE_GUARD_ARRAYS

// Allocate a 2d array of the provided type. Must be freed by caller
#define ARRAY_2D(type, rows, columns) ((type*)calloc((rows) * (columns), sizeof(type)))

// Convert row & column indices into a single index for accessing
#define CONVERT_INDEX_2D(rowSize, rowNum, colNum) (((rowSize) * (rowNum)) + (colNum))

// 
#define ACCESS_2D(arrPtr, numCols, rowNum, colNum) \
    *((arrPtr) + CONVERT_INDEX_2D((numCols), (rowNum), (colNum)))


void printInt2d(int* arrPtr, int rows, int cols);

#endif
