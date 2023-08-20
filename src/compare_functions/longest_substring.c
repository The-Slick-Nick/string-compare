#include <string.h>
#include <stdbool.h>

#include "strcompare.h"
#include "IdxRef.h"
#include "max_min.h"

/*========================================================================================
Internal Declarations
========================================================================================*/

static int _longestSubstring(
    const char* str1, const char* str2, int len1, int len2, int* substrIdx
);
static int _substringLength(const char* str1, const char* str2, int idx1, int idx2);

/*========================================================================================
Internal Definitions
========================================================================================*/

// Internal call to determine the longest substring.
// Assumes that str1 is the shorter of the two strings.
// len1 and len2 represent the lengths of str1 and str2, respectively
// Returns -1 if memory allocation fails

/// @brief Internal worker function for longest substrings
/// @param str1 First string. Assumed to be shorter string
/// @param str2 Second string. Assumed to be longer string. 
/// @param len1 Length of the first string.
/// @param len2 Length of the second string
/// @param substrIdx Address of an integer. Will write to it the index (in str1) where
/// the longest substring between the two beings. Note that the return value (the length)
/// can provide information as to how to construct the longest substring from this index.
/// If this behavior is not desired or
/// neede, pass a NULL value here.
/// @return 
static int _longestSubstring(
    const char* str1, const char* str2, int len1, int len2, int* substrIdx
)
{

    int idx1;               // Index for indexing str1
    int idx2;               // Index for indexing str2
    int max_substr_score;   // Current maximum substring length tabulated
    int substr_score;       // Length of current considered substring
    int bestIdx;            // idx1 where the current max_substr_score was found

    unsigned char curChr;

    IdxRef iref;
    int chr_counts[256] = {0};
    int ptr_ref[256] = {0};

    // Build our reference off of the shorter string
    if (!IdxRef_build(&iref, str1, chr_counts, ptr_ref))
        return -1;

    max_substr_score = 0;
    bestIdx = 0;
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
            if (substr_score > max_substr_score)
            {
                max_substr_score = substr_score;
                bestIdx = idx1;
            }
        }
    }

    IdxRef_deconstruct(&iref);
    if (substrIdx != NULL)
        *substrIdx = bestIdx;

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

double lss_major(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int longestLen;
    int denom;

    if ((len1 == 0) && (len2 == 0))
        return 1;

    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
    {
        longestLen = _longestSubstring(str2, str1, len2, len1, NULL);
        denom = len1;
    }
    else
    {
        longestLen = _longestSubstring(str1, str2, len1, len2, NULL);
        denom = len2;
    }

    if (longestLen < 0)
        return -1;

    return longestLen / (double)denom;
    
}

double lss_minor(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int longestLen;
    int denom;

    if ((len1 == 0) && (len2 == 0))
        return 1;

    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
    {
        longestLen = _longestSubstring(str2, str1, len2, len1, NULL);
        denom = len2;
    }
    else
    {
        longestLen = _longestSubstring(str1, str2, len1, len2, NULL);
        denom = len1;
    }

    if (longestLen < 0)
        return -1;

    return longestLen / (double)denom;
}


// Returns the length of the longest substring found. Writes the index in str1
// where it first appears into substrIdx
int longest_substring(const char* str1, const char* str2, int* substrIdx)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int longestLen;

    if ((len1 == 0) || (len2 == 0))
    {
        *substrIdx = 0;
        return 0;
    }

    // Note that we do not control for length here, so caller knows which string
    // substrIdx is provided for
    longestLen = _longestSubstring(str1, str2, len1, len2, substrIdx);
    if (longestLen < 0)
        return -1;

    return longestLen;
}


// Sister method to longest_substring. Using the information provided/returned,
// slices string into a substring based on length, pushing contents into destination.
int build_substring(const char* str, int substrIdx, int substrLen, char* destination)
{
    for (int i = 0; i < substrLen; i++)
    {
        destination[i] = str[substrIdx];
        substrIdx++;
    }
    destination[substrLen] = '\0';
}
