/*----------------------------------------------------------------------------------------
utility_functions.h

Helpful subfunctions for compare_functions
----------------------------------------------------------------------------------------*/
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