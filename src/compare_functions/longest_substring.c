#include <string.h>
#include <stdbool.h>

#include "strcompare.h"
#include "IdxRef.h"
#include "max_min.h"

/*========================================================================================
Internal Declarations
========================================================================================*/

static int _longestSubstring(
    const char* str1, const char* str2, int len1, int len2, const char** substrPtr
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
/// @param substrPtr Address of a character pointer. If not NULL, writes the address
/// of the start of the longest substring from str1.
/// @return Integer representing longest substring between two strings
static int _longestSubstring(
    const char* str1, const char* str2, int len1, int len2, const char** substrPtr
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
    if (substrPtr != NULL)
        *substrPtr = (str1 + bestIdx);

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


/// @brief Identifies the length of the longest substring between two strings. If 
/// substrPtr is provided, writes the address where that substring beings into
/// substrPtr.
/// @param str1 First string to compare. 
/// @param str2 Second string to compare.
/// @param substrPtr Character pointer to some address within str1 where the longest
/// substring begins. If passed NULL, does nothing. Note that the address will point
/// to somewhere in str1, and the "substring" is not zero terminated. Instead, the
/// length is indicated by the return value of the function. It is up to the caller
/// at this point to call strncpy or equivalent to build the substring themselves.
/// @return Integer representing the length of the longest sequence of common
/// characters in order between two strings. 
/// Example: STRESSED vs DESSERT would yield 4.
/// substrPtr, in this example, would point to the address of the first "E" in STRESSED.
int longest_substring(const char* str1, const char* str2, const char** substrPtr)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int longestLen;

    if ((len1 == 0) || (len2 == 0))
    {
        if (substrPtr != NULL)
            *substrPtr = (str1 + len1);
        return 0;
    }

    if (len1 > len2)
        longestLen = _longestSubstring(str2, str1, len2, len1, substrPtr);
    else
        longestLen = _longestSubstring(str1, str2, len1, len2, substrPtr);

    if (longestLen < 0)
        return -1;

    return longestLen;
}


// Since neither strcpy nor memcpy null-terminate the string, this function is provided
// as a helpful utility
char* substring(char* dest, const char* src, size_t len)
{
    memcpy(dest, src, len);
    dest[len] = '\0';
    return dest;
}