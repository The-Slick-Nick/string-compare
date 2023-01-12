/*----------------------------------------------------------------------------------------
utility_functions.h

Helpful subfunctions for compare_functions
    choose_fss_basis
    build_
----------------------------------------------------------------------------------------*/

#ifndef INCLUDE_GUARD_UTILITY_FUNCTIONS
#define INCLUDE_GUARD_UTILITY_FUNCTIONS

#include <stdbool.h>
#include <assert.h>

// Identifies which of two strings is more appropriate to be the basis (idx map built from
// for a fss_score calculation)
// Returns 0 for first string, 1 for second string
int choose_fss_basis(char* str1, char* str2)
{
    int idx1, idx2;
    char chr1, chr2;

    // Default to first
    int chosen_basis = 0;
    bool alphabetical_chosen = false;

    int num_loops = 0;

    idx1 = 0;
    idx2 = 0;

    while (true)
    {
        // Error-out at 1 million for safety
        assert(num_loops < 1000000);
        
        num_loops++;

        chr1 = *(str1 + idx1);
        chr2 = *(str2 + idx2);

        // Increment idx now that chr1&chr2 are stored
        idx1++;
        idx2++;

        // Exit conditions when end of a string is reached
        if (chr1 == '\0' && chr2 == '\0') return chosen_basis;  // same length
        if (chr1 == '\0') return 1;                             // str2 longer
        if (chr2 == '\0') return 0;                             // str1 longer

        // Only check alphabetical order if we haven't yet found a difference
        if (alphabetical_chosen)
            continue;

        // Note that we do noting (move to the next) if chr1 == chr2
        if (chr1 > chr2)
        {
            chosen_basis = 0;
            alphabetical_chosen = true;
        }
        else if (chr2 > chr1)
        {
            chosen_basis = 1;
            alphabetical_chosen = true;
        }
    }

    // Return value should be identified in loop - return an oopsie if we get here
    return -1;
}


// summarize_str - Model a provided string, providing:
// 1 - A char_count array tracking the number of occurences of each character
// 2 - An idx_ref storing each index a character appears at, by character
// 3 - The length of the string, as function's return value
// Example:
// HELLO
// idx      char_counts     idx_ref
// 69 (E)       1           [1]               
// 72 (H)       1           [0]    
// 76 (L)       2           [2, 3]
// 79 (O)       1           [4]
// Params
// ------
//  char* str
//      Pointer to input string to model
//  int* char_counts
//      Pointer to a 256-sized integer array to build char_counts into
//      Should be initialized to zeroes
//  int** idx_ref
//      Pointer to a 256-sized array of integer array pointers to build
//      idx_ref into. Should be initialized to NULLs
//  Returns
//  -------
//  int
//      Length of input string `str` as an integer
int summarize_string(const char* str, int* char_counts, int** idx_ref)
{
    int idx;                    // Index for looping through str
    char chr;                   // Current character in str in a loop
    int chr_count;              // Current count for a character in loop
    int min_indices[256] = {0}; // Indices for idx_ref to write to for each char
    int min_idx;                // In a loop, index to write into idx_ref for current char
    int len = 0;                // Tabulated length of string

    // First build char_counts
    for (idx = 0; *(str + idx) != '\0'; idx++)
    {
        chr = *(str + idx);
        len++;

        char_counts[chr]++;
        // *(char_counts + chr)++;
    }

    for (idx = 0; *(str + idx) != '\0'; idx++)
    {
        chr = *(str + idx);
        chr_count = char_counts[chr];
        min_idx = min_indices[chr];

        // Allocate memory for this part of idx_ref if we haven't yet
        if ( idx_ref[chr] == NULL)
            idx_ref[chr] = (int*)malloc(chr_count * sizeof(int));

        // Add this index to idx_ref

        // idx_ref[chr][min_idx] = idx;
        *(idx_ref[chr] + min_idx) = idx;
        min_indices[chr]++;
    }
    return len;
}

#endif