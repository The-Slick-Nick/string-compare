/*----------------------------------------------------------------------------------------
lcs_score.h

Longest Common Substring score

lcs_score
Returns the ratio of the length of the longest common substring between to strings
to the length of the shorter string
----------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include "../components/idx_list.h"

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
        return max_substr_score / (float)len2;
    else
        return max_substr_score / (float)len1;

}

// Improved version of lcs score 
double improved_lcs_score(const char* str1, const char* str2)
{

    int idx1, idx2;
    int idx1_temp, idx2_temp;
    int len1, len2;
    char chr1, chr2;

    int substr_score;
    int max_substr_score = 0;

    IdxList* list;
    IdxItem* item;
    IdxList* idx_ref[256] = {NULL};


    len1 = strlen(str1);  // Only len1 needs calculated this way - str2 is looped through
                          // to build the idx_ref anyway

    // Model index reference after str2
    len2 = 0;
    for (idx2 = 0; *(str2 + idx2) != '\0'; idx2++)
    {
        len2++;
        chr2 = *(str2 + idx2);
        if (idx_ref[chr2] == NULL)
            idx_ref[chr2] = IdxList_init();

        list = idx_ref[chr2];

        IdxList_append(list, idx2);
    }

    if ((len1 == 0) != (len2 == 0))
        return 0.0;


    for (idx1 = 0; *(str1 + idx1) != '\0'; idx1++)
    {
        // Exit if a better substr can't be found
        if ( (len1 - idx1) <= max_substr_score)
            break;

        list = idx_ref[*(str1 + idx1)];
        if (list == NULL)
            continue;

        for (item = list->head; item != NULL; item = item->next)
        {
            // Exit if a better substr can't be found - note that each list will have
            // indices in ascending order, so we can `break` here
            if ( (len2 - item->idx) <= max_substr_score)
                break;

            substr_score = 0;
            idx1_temp = idx1;
            idx2_temp = item->idx;

            chr1 = *(str1 + idx1_temp);
            chr2 = *(str2 + idx2_temp);

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

            if (substr_score > max_substr_score)
                max_substr_score = substr_score;

        }

    }

    for (int i = 0; i < 256; i++)
    {
        list = idx_ref[i];
        if (list != NULL)
            IdxList_deconstruct(list);
    }
    // Return ratio of longest substr length to the short string (which would be the
    // maximum length substring possible)
    if (len1 > len2)
        return max_substr_score / (float)len2;
    else
        return max_substr_score / (float)len1;
}