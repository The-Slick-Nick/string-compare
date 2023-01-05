#include <stdlib.h>
// Compares two provided strings and provides a floating point assessment (0-1) of
// how similar the character distributions of the two strings are
double letter_score(const char* str1, const char* str2)
{
    int cdist[256] = {0};  // Tracked character distribution

    int i1, i2, i_dist;     // Indices for looping through str1, str2, and cdist
    int max_diff = 0;       // Maximum possible difference between the two
    int actual_diff = 0;    // Calculated difference between the two distributions

    int to_add = 0;  // Value to add within a loop

    // build cdist based on distribution of str1 characters
    for (i1 = 0; *(str1+i1) != '\0'; i1++)
    {
        max_diff++;

        // Use asc val of character in str1 for index in cdist
        cdist[*(str1+i1)]++;  // Increment for str1
    }

    // modify cdist based on distribution of str2 characters
    for (i2 = 0; *(str2+i2) != '\0'; i2++)
    {
        max_diff++;

        // Use asc val of character in str2 for index in cdist
        cdist[*(str2+i2)]--;// Decrement for str2
    }

    for (i_dist=0; i_dist<256; i_dist++)
    {
        actual_diff += abs(*(cdist + i_dist));
    }

    return (max_diff-actual_diff)/(double)max_diff;
}
