/*========================================================================================
comparefunc_time.h

Structs & methods for use in timing comparison functions
========================================================================================*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "random_string.h"

/*========================================================================================
Macros for Core Structs/Functions
========================================================================================*/

#define PRINT_LINE for(int i = 0; i < 90; i++) {printf("=");} printf("\n")

/*========================================================================================
Struct Definition
========================================================================================*/

typedef struct CompareFunctionItem {
    char* name;
    double time_taken;
    double(*func)(const char*, const char*);
} _cfuncitem;


typedef struct CompareFunctionTimer {

    size_t length;
    size_t size;
    _cfuncitem* functions;
    unsigned int tests_run;

} CFuncTimer;

/*========================================================================================
Private Methods
========================================================================================*/

// Swaps two elements of CFuncTimer.functions based on their total time taken
void _CFuncTimer_swapItems(CFuncTimer* self, int idx1, int idx2)
{
    _cfuncitem temp;
    temp = *(self->functions + idx1);
    *(self->functions + idx1) = *(self->functions + idx2);
    *(self->functions + idx2) = temp;
}

// Performs quicksort on CFuncTimer.functions on their total time taken, asc order
void _CFuncTimer_qsort(CFuncTimer* self, int min_idx, int max_idx)
{

    // QSort exition conditions

    // One element, no checking needed
    if (min_idx >= max_idx)
        return;

    // Two elements, manual check
    if (min_idx + 1 == max_idx)
    {
        double time_left = (*(self->functions + min_idx)).time_taken;
        double time_right = (*(self->functions + max_idx)).time_taken;
        if (time_left > time_right)
            _CFuncTimer_swapItems(self, min_idx, max_idx);
        return;
    }

    double basis_val;
    int basis_idx;

    int left_idx, right_idx;

    basis_idx = min_idx;
    basis_val = (*(self->functions + basis_idx)).time_taken;

    left_idx = min_idx + 1;
    right_idx = max_idx;

    // Check until right crosses left
    while (left_idx < right_idx)
    {

        // Increment left_idx
        // while (left_val < basis_val)
        while ( (*(self->functions + left_idx)).time_taken < basis_val)
        {
            if (left_idx >= max_idx)
                break;
            left_idx++;
        }

        // Derement right_idx
        // while (right_val > basis_val)
        while ( (*(self->functions + right_idx)).time_taken > basis_val)
        {
            if (right_idx <= basis_idx || right_idx < left_idx)
                break;
            right_idx--;
        }

        // If stopped without crossing, swap
        if (left_idx < right_idx)
            _CFuncTimer_swapItems(self, left_idx, right_idx);
    }
    // Swap basis into place
    _CFuncTimer_swapItems(self, basis_idx, right_idx);

    // QSort subsections
    _CFuncTimer_qsort(self, 0, right_idx - 1);
    _CFuncTimer_qsort(self, right_idx + 1, max_idx);

}

/*========================================================================================
Public Methods
========================================================================================*/

// Add a comparison function to be tested
void CFuncTimer_addFunction(
    CFuncTimer* self, double(*func)(const char*, const char*), char* func_name
)
{
    // Resize array if needed
    if (self->length >= self->size)
    {
        while (self->length >= self->size)
        {
            self->size *= 2;
        }
        self->functions = (
            (_cfuncitem*)realloc(self->functions, self->size * sizeof(_cfuncitem))
        );
    }

    // Store next location as pointer to make code more concise
    _cfuncitem* new_func = self->functions + self->length;
    new_func->func = func;
    new_func->name = func_name;
    new_func->time_taken = 0;

    self->length++;
}

// Run tests and store results
void CFuncTimer_runTests(CFuncTimer* self, unsigned int num_tests)
{
    char *str1, *str2;
    _cfuncitem* this_func;

    clock_t start, end;

    // time_taken += ((double)(end - start)) / CLOCKS_PER_SEC;


    // Run through provided number of test cases
    for (int i = 0; i < num_tests; i++)
    {
        if (i % (int)(0.05 * num_tests) == 0)
        {
            printf("%d%% complete\n", (int)(100 * i / num_tests));
        }

        str1 = random_string();
        str2 = random_string();

        // Run each function against the same two strings
        for (int j = 0; j < self->length; j++)
        {
            this_func = self->functions + j;
            start = clock();
            this_func->func(str1, str2);
            end = clock();
            this_func->time_taken += ((double)(end - start)) / CLOCKS_PER_SEC;
        }
        self->tests_run++;
        free(str1);
        free(str2);
    }
}

// Print result of all tests
void CFuncTimer_printResults(CFuncTimer* self)
{
    _cfuncitem* this_func;

    // First print out test parameters

    PRINT_LINE;
    printf("%d tests:\n", self->tests_run);
    printf("Test string min length %d\n", RANDOMSTR_MIN_LENGTH);
    printf("Test string max length %d\n", RANDOMSTR_MAX_LENGTH);
    PRINT_LINE;

    // Next print out test results
    for (int i = 0; i < self->length; i++)
    {
        this_func = self->functions + i;
        printf("[%d] %f: %s\n", i + 1, this_func->time_taken, this_func->name);
    }
}

// Sorts results based on each function's time taken
void CFuncTimer_sortResults(CFuncTimer* self)
{
    _CFuncTimer_qsort(self, 0, self->length - 1);
}

// Ensure internally allocated memory is freed
void CFuncTimer_freeMembers(CFuncTimer* self)
{
    free(self->functions);
}

/*========================================================================================
API Macro Definition
========================================================================================*/

// Establish function scope CFunctimer functimer
// To be called first in testing main() method
#define CFUNC_TIMER_START CFuncTimer functimer = {\
    .length = 0,\
    .size = 4,\
    .functions = (_cfuncitem*)malloc(4 * sizeof(_cfuncitem)),\
    .tests_run = 0\
    }

// Add provided function/name
// To be used after CFUNC_TIMER_START has been called
#define CFUNC_TIMER_ADD(func, name) CFuncTimer_addFunction(&functimer, func, name)

// Run tests, sort results, print resuls, and clean up
// To be used after CFUNC_TIMER_START and any CFUNC_TIMER_ADD calls
#define CFUNC_TIMER_END \
    CFuncTimer_runTests(&functimer, 1000000);\
    CFuncTimer_sortResults(&functimer);\
    CFuncTimer_printResults(&functimer);\
    CFuncTimer_freeMembers(&functimer)
