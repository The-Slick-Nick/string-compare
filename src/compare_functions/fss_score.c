/*----------------------------------------------------------------------------------------
fcs_score.c

Fragmented Substring Score

"Fractured Substring"
    A series of character matches between two strings where characters are in the same
    relative order, i.e. for AGREE vs EAGER, fractured substrings would be:
        AGREE vs EAGER
        __R_E vs E___R => AGE
        ____E vs E____ => R
        _____ vs _____ => E
    Note that fractured substrings work "without replacement", and the total combinations
    of all characters between fractured substrings should match the total distribution
    of matching characters between str1 and str2

Behavior types:
---------------------------------------
SCORING - how points are assessed
    normal - considers each character match 1 point
    adjusted - corrects each character match down by difference in idx1 & idx2 offsets 

PLACEMENT - how to decide which running substr (calc group) a match is placed onto
    first - adds to the first discovered substring in calc group
    best - considers each calc group and places on the one with minimum offset difference

fcs_score
    SCORING = normal
    PLACEMENT = first

adjusted_fss_score
    SCORING = adjusted
    PLACEMENT = best
----------------------------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>

#include "strcompare.h"
#include "max_min.h"


double fss_score(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // One extra row & column for zeroes
    // int numRows = len1 + 1;
    int numCols = len2 + 1;

    if (len1 == 0 && len2 == 0)
        return (double)1;
    else if ((len1 == 0) != (len2 == 0)) // xor
        return (double)0;

    int* scores = (int*)calloc(2 * numCols, sizeof(int));

    if (scores == NULL)
        return -1; // :(

    int* thisArr = scores;
    int* lastArr = (scores + numCols);
    int* hold; // for swapping

    int right;
    int down;
    int diagonal;

    // bottom-up DP with O(2n) + c memory
    for (int rowNum = len1 - 1; rowNum >= 0; rowNum--)
    {
        *(thisArr + len2) = 0;  // reset "buffer" column
        for (int colNum = len2 - 1; colNum >= 0; colNum--)
        {
            diagonal = *(lastArr + colNum + 1);

            if (str1[rowNum] == str2[colNum])
            {
                *(thisArr + colNum) = 1 + diagonal;
            }
            else
            {
                right = *(thisArr + colNum + 1);
                down = *(lastArr + colNum);

                *(thisArr + colNum) = imax(right, down);
            }
        }
        hold = thisArr;
        thisArr = lastArr;
        lastArr = hold;
    }
    int bestScore = *lastArr;  // have to use lastArr, as it would have swapped at end
    free(scores);
    return bestScore / (double)(imax(len1, len2));

}

double adjusted_fss_score(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int maxLen = imax(len1, len2);

    // int numRows = len1 + 1;
    int numCols = len2 + 1;

    int maxScore = 0;
    int* scores;

    int* thisArr;
    int* lastArr;
    int* hold;

    int this;
    int right;
    int down;
    int diagonal;


    // Both empty - 100% equal
    if (len1 == 0 && len2 == 0)
        return (double)1;
    // Exactly 1 empty - 0% equal
    else if ((len1 == 0) != (len2 == 0)) // xor
        return (double)0;

    scores = (int*)calloc(2 * numCols, sizeof(int));

    if (scores == NULL)
        return -1; // calloc failed :(

    thisArr = scores;
    lastArr = (scores + numCols);
    
    // bottom up DP but with O(2n) + c memory
    for (int rowNum = len1 - 1; rowNum >= 0; rowNum--)
    {
        *(thisArr + len2) = 0; // reset "buffer" column
        for (int colNum = len2 - 1; colNum >= 0; colNum--)
        {
            diagonal = *(lastArr + colNum + 1);

            if (str1[rowNum] == str2[colNum])
            {
                this = diagonal + maxLen;
                *(thisArr + colNum) = this;
                maxScore = imax(this, maxScore);
            }
            else
            {
                right = *(thisArr + colNum + 1);
                down = *(lastArr + colNum);
                this = imax3(
                    right -1,
                    down - 1,
                    diagonal
                );
                *(thisArr + colNum) = this;
            }
        }
        hold = thisArr;
        thisArr = lastArr;
        lastArr = hold;
    }
    double to_return = maxScore / ((double)len1 * (double)len2);
    free(scores);
    return to_return;
}