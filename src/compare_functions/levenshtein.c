#include "strcompare.h"
#include "max_min.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*========================================================================================
Internal declarations
========================================================================================*/

static int _levenshteinDistance(const char* str1, const char* str2, int len1, int len2);


/*========================================================================================
Internal definitions
========================================================================================*/

// Levenshtein distance between two strings. Though the order does not impact the final
// score, we assum str1 is shorter than str2. len1 and len2 represent the lengths
// of these two strings, respectively.
static int _levenshteinDistance(const char* str1, const char* str2, int len1, int len2)
{
    int idx1;
    int idx2;

    unsigned char chr1;
    unsigned char chr2;

    int cost;
    int up;
    int left;
    int diagonal;

    int numRows = len2 + 1;
    int numCols = len1 + 1;

    int* scores = (int*)malloc((2 * numCols) * sizeof(int));

    int* thisArr = scores;
    int* lastArr = (scores + numCols);
    int* hold;

    // Write in "row 0"
    for (int i = 0; i < numCols; i++)
        *(lastArr + i) = i;

    for (idx2 = 1; idx2 < numRows; idx2++)
    {
        // Write value for "column 0"
        *(thisArr) = idx2;
        chr2 = str2[idx2 - 1];
        for (idx1 = 1; idx1 < numCols; idx1++)
        {
            chr1 = str1[idx1 - 1];

            if (chr1 == chr2)
                cost = 0;
            else
                cost = 1;

            up = *(lastArr + idx1);
            left = *(thisArr + idx1 - 1);
            diagonal = *(lastArr + idx1 - 1); // up & to the left

            *(thisArr + idx1) = imin3(up + 1, left + 1, diagonal + cost);
        }
        hold = thisArr;
        thisArr = lastArr;
        lastArr = hold;
    }
    int minDistance = *(lastArr + len1);  // Last iteration would have swapped
    free(scores);
    return minDistance;
}


/*========================================================================================
API Definitions
========================================================================================*/

int levenshtein_distance(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 > len2)
        return _levenshteinDistance(str2, str1, len2, len1);
    else
        return _levenshteinDistance(str1, str2, len1, len2);
}

double levenshtein_major(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int distance;

    if ((len1 == 0) && (len2 == 0))
        return 1;
    
    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
    {
        distance = _levenshteinDistance(str2, str1, len2, len1);
        return (len1 - distance) / (double)len1;
    }
    else
    {
        distance = _levenshteinDistance(str1, str2, len1, len2);
        return (len2 - distance) / (double)len2;
    }
}

double levenshtein_minor(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int distance;

    if ((len1 == 0) && (len2 == 0))
        return 1;
    
    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
    {
        distance = _levenshteinDistance(str2, str1, len2, len1);
        return (len1 - distance) / (double)len2;
    }
    else
    {
        distance = _levenshteinDistance(str1, str2, len1, len2);
        return (len2 - distance) / (double)len1;
    }
}
