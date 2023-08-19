#include <string.h>

#include "compare_functions.h"
#include "IdxRef.h"
#include "max_min.h"

/*========================================================================================
Internal Declarations
========================================================================================*/

static int _longestSubstring(const char* str1, const char* str2, int len1, int len2);
static int _naiveLongestSubstring(const char* str1, const char* str2, int len1, int lent2);
static int _substringLength(const char* str1, const char* str2, int idx1, int idx2);

/*========================================================================================
Internal Definitions
========================================================================================*/

// Internal call to determine the longest substring.
// Assumes that str1 is the shorter of the two strings.
// len1 and len2 represent the lengths of str1 and str2, respectively
static int _longestSubstring(const char* str1, const char* str2, int len1, int len2)
{

    int idx1;
    int idx2;
    int max_substr_score;
    int substr_score;

    unsigned char curChr;

    IdxRef iref;
    int chr_counts[256] = {0};
    int ptr_ref[256] = {0};

    // Build our reference off of the shorter string
    IdxRef_build(&iref, str1, chr_counts, ptr_ref);

    max_substr_score = 0;
    for (idx2 = 0; idx2 < len2; idx2++)
    {
        // Break when we can't find a better score
        if (len2 - idx2 <= max_substr_score)
            break;

        curChr = *(str2 + idx2);

        // Consider each associated idx1 for this character
        for (int i = 0; i < IdxRef_getChrCount(&iref, curChr); i++)
        {
            idx1 = IdxRef_getIndex(&iref, curChr, i);

            if (len1 - idx1 <= max_substr_score)
                break;

            substr_score = _substringLength(str1, str2, idx1, idx2);
            max_substr_score = imax(max_substr_score, substr_score);
        }
    }

    IdxRef_deconstruct(&iref);
    return max_substr_score;

}

// Performs naive algorithm to calculate longest substring. Assumes str1 is the shorter
// of the two strings. 
static int _naiveLongestSubstring(const char* str1, const char* str2, int len1, int len2)
{
    int idx1;
    int idx2;

    // unsigned char chr1;
    // unsigned char chr2;

    int substr_score = 0;
    int max_substr_score = 0;

    for (idx1 = 0; idx1 < len1; idx1++)
    {
        if ( (len1 - idx1) <= max_substr_score)
            break;

        idx2 = 0;

        // Consider every idx2 starter for each idx1
        while (idx2 < len2)
        {
            // Exit when we can't find a longer substr
            if ( (len2 - idx2) <= max_substr_score)
                break;

            substr_score = _substringLength(str1, str2, idx1, idx2);
            max_substr_score = imax(max_substr_score, substr_score);

            idx2++;
        }
    }

    return max_substr_score;
}


// Calculate the matching substring length starting at the provided indices
static int _substringLength(const char* str1, const char* str2, int idx1, int idx2)
{
    unsigned char chr1;
    unsigned char chr2;
    int substr_score = 0;

    chr1 = (unsigned char)(*(str1 + idx1));
    chr2 = (unsigned char)(*(str2 + idx2));

    while (chr1 == chr2)
    {
        if (chr1 == '\0')
            break;

        substr_score++;
        idx1++;
        idx2++;
        chr1 = *(str1 + idx1);
        chr2 = *(str2 + idx2);
    }

    return substr_score;

}


/*========================================================================================
API Definitions
========================================================================================*/

double lcs_score(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int longestLen;

    if ((len1 == 0) && (len2 == 0))
        return 1;

    if ((len1 == 0) != (len2 == 0))
        return 0;


    if (len1 > len2)
    {
        longestLen = _longestSubstring(str2, str1, len2, len1);
        return longestLen / (double)len2;
    }
    else
    {
        longestLen = _longestSubstring(str1, str2, len1, len2);
        return longestLen / (double)len1;
    }

}

double naive_lcs_score(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int longestLen;

    if ((len1 == 0) && (len2 == 0))
        return 1;

    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
    {
        longestLen = _naiveLongestSubstring(str2, str1, len2, len1);
        return longestLen / (double)len2;
    }
    else
    {
        longestLen = _naiveLongestSubstring(str1, str2, len1, len2);
        return longestLen / (double)len1;
    }
}