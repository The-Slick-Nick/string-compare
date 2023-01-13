/*----------------------------------------------------------------------------------------
lcs_score.h

Longest Common Substring score

lcs_score
Returns the ratio of the length of the longest common substring between to strings
to the length of the shorter string
----------------------------------------------------------------------------------------*/
#ifndef INCLUDE_GUARD_LCS_SCORE
#define INCLUDE_GUARD_LCS_SCORE


#include <stdlib.h>
#include <string.h>

#include "../components/utility_functions.h"

// Longest Common Substring score
double lcs_score(const char* str1, const char* str2)
{
    int idx1, idx2;
    int idx1_temp, idx2_temp;

    // Need to know lengths for optimization & final score
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Edge cases
    if ((len1 == 0) != (len2 == 0))
        return 0;

    char chr1, chr2;

    int substr_score;
    int max_substr_score = 0;

    for (idx1 = 0; idx1 < len1; idx1++)
    {
        // Exit when a longer possible substring score cannot be found
        if ( (len1 - idx1) <= max_substr_score)
            break;

        idx2 = 0;
        // consider every idx2 starter for every idx1
        while (idx2 < len2)
        {
            // Exit when a longer possible substring score cannot be found
            if ( (len2 - idx2) <= max_substr_score)
                break;

            substr_score = 0;
            idx1_temp = idx1;
            idx2_temp = idx2;

            chr1 = *(idx1_temp + str1);
            chr2 = *(idx2_temp + str2);

            // matching "head" character traverse through str1 & str2 simultaneously
            // to check how long that substring is
            while (chr1 == chr2)
            {
                // Strings ended - stop consideration (note that we don't need to check
                // chr1 == '\0' and chr2 == '\0' both, as we can't get here unless
                // they are equal anyway)
                if (chr1 == '\0')
                    break;

                substr_score++;
                idx1_temp++;
                idx2_temp++;

                chr1 = *(idx1_temp + str1);
                chr2 = *(idx2_temp + str2);
            }

            // Determine if we've found a new better score
            if (substr_score > max_substr_score)
                max_substr_score = substr_score;

            idx2++;
        }

    }

    // Return ratio of longest substr length to the short string (which would be the
    // maximum length substring possible)
    if (len1 > len2)
        return max_substr_score / (double)len2;
    else
        return max_substr_score / (double)len1;

}

double improved_lcs_score(const char* str1, const char* str2)
{
    int idx1, idx2;
    int idx1_temp, idx2_temp;
    int len1, len2;
    char chr1, chr2;

    int substr_score;
    int max_substr_score;

    int char_counts[256] = {0};     // Counts of characters in str2 by their ascii val
    int* idx_ref[256] = {NULL};     // Arrays of each index found in str2 by char

    // Build our arrays for use in algorithm
    len2 = summarize_string(str2, char_counts, idx_ref);
    len1 = strlen(str1);

    // Exactly one blank - exit early, 0 score
    if ( (len1 == 0) != (len2 == 0))
        return 0;

    // Loop through str1 and match indices to str2
    max_substr_score = 0;
    for (idx1 = 0; *(str1 + idx1) != '\0'; idx1++)
    {
        // Break when we can't find a better score
        if (len1 - idx1 <= max_substr_score)
            break;

        // Consider each associated idx2 for this character
        for (int i = 0; i < char_counts[ *(str1 + idx1) ]; i++)
        {   // idx_ref[str1_chr][i]
            idx2 = *(idx_ref[ *(str1 + idx1) ] + i);

            // Stop considering this char if can't find better score
            // (idx2 is in ascending order here)
            if (len2 - idx2 <= max_substr_score)
                break;

            idx1_temp = idx1;
            idx2_temp = idx2;

            chr1 = *(str1 + idx1_temp);
            chr2 = *(str2 + idx2_temp);
            substr_score = 0;

            // Increment both as long as they match - checking substr length
            while (chr1 == chr2)
            {
                if (chr1 == '\0')
                    break;

                substr_score++;
                idx1_temp++;
                idx2_temp++;
                chr1 = *(str1 + idx1_temp);
                chr2 = *(str2 + idx2_temp);
            }

            // Check vs current running max
            if (substr_score > max_substr_score)
                max_substr_score = substr_score;
        }
    }

    // Now free our allocated memory
    for (int i = 0; i < 256; i++)
        free(idx_ref[i]);

    // Return
    if (len1 > len2)
        return max_substr_score / (double)len2;
    else
        return max_substr_score / (double)len1;
}

#endif
