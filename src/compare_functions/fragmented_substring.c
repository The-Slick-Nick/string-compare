/*========================================================================================
fragmented_substring.c

Fragmented Substring Score

Assess string similarity based on the "best" fragmented substring common to both
strings.

"Fractured Substring"
    A series of character matches between two strings where characters are in the same
    relative order, i.e. for AGREE vs EAGER, possible fractured substrings would be:
        AGREE vs EAGER
        __R_E vs E___R => AGE
        ____E vs E____ => R
        _____ vs _____ => E

========================================================================================*/

#include <string.h>
#include <stdlib.h>

#include "strcompare.h"
#include "max_min.h"

/*========================================================================================
Internal declarations
========================================================================================*/

int _longestFragmented(const char* str1, const char* str2, int len1, int len2);
int _adjustedFrag(const char* str1, const char* str2, int len1, int len2, int factor);

/*========================================================================================
Internal definitions
========================================================================================*/

// Calculate the length of the longest fragmented substring.
// str1 is assumed to be the shorter of the two strings, and
// len1 and len2 represent the lengths of str1 and str2, respectively
// Returns -1 on failed memory allocation
int _longestFragmented(const char* str1, const char* str2, int len1, int len2)
{
    /* 
    * For optimization purposes, the "width" (or numCols) is the shorter string
    *   S T R
    * S
    * T
    * R
    * I
    * N
    * G
    * This will increase the number of swaps necessary, but provide lower memory
    * usage & better locality benefits, as the score array will be smaller.
    */
    int numCols = len1 + 1;

    int* scores = (int*)calloc(2 * numCols, sizeof(int));

    if (scores == NULL)
        return -1;

    int* thisArr = scores;
    int* lastArr = (scores + numCols);
    int* hold; // for swapping

    int right;
    int down;
    int diagonal;


    // bottom-up DP with O(2n) memory
    for (int rowNum = len2 - 1; rowNum >= 0; rowNum--)
    {
        *(thisArr + len1) = 0; // reset "buffer" column
        for (int colNum = len1 - 1; colNum >= 0; colNum--)
        {
            diagonal = *(lastArr + colNum + 1);

            if (str1[colNum] == str2[rowNum])
                *(thisArr + colNum) = 1 + diagonal;
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
    int bestScore = *lastArr;  // Would have swapped, use "last"
    free(scores);
    return bestScore;
}


// Calculate the "best" fragmented substring score between two strings.
// Points scaled by a given factor, where the provided factor argument will depend
// on if you are calculating the major or minor version of the score.
// str1 is assumed to be the shorter of the two strings, and
// len1 and len2 represent the lengths of str1 and str2, respectively
// Returns -1 on failed memory allocation
int _adjustedFrag(const char* str1, const char* str2, int len1, int len2, int factor)
{
    /* 
    * For optimization purposes, the "width" (or numCols) is the shorter string
    *   S T R
    * S
    * T
    * R
    * I
    * N
    * G
    * This will increase the number of swaps necessary, but provide lower memory
    * usage & better locality benefits, as the score array will be smaller.
    */

    int numCols = len1 + 1;
    int maxScore = 0;

    int* scores = (int*)calloc(2 * numCols, sizeof(int));

    if (scores == NULL)
        return -1;

    int* thisArr = scores;
    int* lastArr = (scores + numCols);
    int* hold;

    int this;
    int right;
    int down;
    int diagonal;

    // bottom up DP using O(2n) memory
    for (int rowNum = len2 - 1; rowNum >= 0; rowNum--)
    {
        *(thisArr + len1) = 0;  // reset "buffer" column
        for (int colNum = len1 - 1; colNum >= 0; colNum--)
        {
            diagonal = *(lastArr + colNum + 1);

            if (str1[colNum] == str2[rowNum])
            {
                this = diagonal + factor;
                *(thisArr + colNum) = this;
                maxScore = imax(maxScore, this);
            }
            else
            {
                right = *(thisArr + colNum + 1);
                down = *(lastArr + colNum);
                this = imax3(
                    right - 1,
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
    free(scores);
    return maxScore;
}

/*========================================================================================
API Definitions
========================================================================================*/

double fss_major(const char* str1, const char* str2)
{

    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int fragLength;
    int denominator;

    if ((len1 == 0) && (len2 == 0))
        return 1;

    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
    {
        fragLength = _longestFragmented(str2, str1, len2, len1);
        denominator = len1;
    }
    else
    {
        fragLength = _longestFragmented(str1, str2, len1, len2);
        denominator = len2;
    }

    if (fragLength < 0)  // memory allocation error
        return -1;

    return fragLength / (double)denominator;
}

double fss_minor(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int fragLength;
    int denominator;

    if ((len1 == 0) && (len2 == 0))
        return 1;

    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
    {
        fragLength = _longestFragmented(str2, str1, len2, len1);
        denominator = len2;
    }
    else
    {
        fragLength = _longestFragmented(str1, str2, len1, len2);
        denominator = len1;
    }

    if (fragLength < 0)  // memory allocation error
        return -1;

    return fragLength / (double)denominator;
}

double adjusted_fss_major(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int fragScore;

    if ((len1 == 0) && (len2 == 0))
        return 1;

    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
        fragScore = _adjustedFrag(str2, str1, len2, len1, len2);  // factor is short length
    else
        fragScore = _adjustedFrag(str1, str2, len1, len2, len1);

    if (fragScore < 0) // memory allocation error
        return -1;

    return fragScore / (double)(len1 * len2);
}

double adjusted_fss_minor(const char* str1, const char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int fragScore;

    if ((len1 == 0) && (len2 == 0))
        return 1;

    if ((len1 == 0) != (len2 == 0))
        return 0;

    if (len1 > len2)
        fragScore = _adjustedFrag(str2, str1, len2, len1, len1); // factor is longer len
    else
        fragScore = _adjustedFrag(str1, str2, len1, len2, len2);

    if (fragScore < 0)  // memory allocation error
        return -1;
    
    return fragScore / (double)(len1 * len2);
}





// double fss_score(const char* str1, const char* str2)
// {
//     int len1 = strlen(str1);
//     int len2 = strlen(str2);

//     // One extra row & column for zeroes
//     // int numRows = len1 + 1;
//     int numCols = len2 + 1;

//     if (len1 == 0 && len2 == 0)
//         return (double)1;
//     else if ((len1 == 0) != (len2 == 0)) // xor
//         return (double)0;

//     int* scores = (int*)calloc(2 * numCols, sizeof(int));

//     if (scores == NULL)
//         return -1; // :(

//     int* thisArr = scores;
//     int* lastArr = (scores + numCols);
//     int* hold; // for swapping

//     int right;
//     int down;
//     int diagonal;

//     // bottom-up DP with O(2n) + c memory
//     for (int rowNum = len1 - 1; rowNum >= 0; rowNum--)
//     {
//         *(thisArr + len2) = 0;  // reset "buffer" column
//         for (int colNum = len2 - 1; colNum >= 0; colNum--)
//         {
//             diagonal = *(lastArr + colNum + 1);

//             if (str1[rowNum] == str2[colNum])
//             {
//                 *(thisArr + colNum) = 1 + diagonal;
//             }
//             else
//             {
//                 right = *(thisArr + colNum + 1);
//                 down = *(lastArr + colNum);

//                 *(thisArr + colNum) = imax(right, down);
//             }
//         }
//         hold = thisArr;
//         thisArr = lastArr;
//         lastArr = hold;
//     }
//     int bestScore = *lastArr;  // have to use lastArr, as it would have swapped at end
//     free(scores);
//     return bestScore / (double)(imax(len1, len2));

// }

// double adjusted_fss_score(const char* str1, const char* str2)
// {
//     int len1 = strlen(str1);
//     int len2 = strlen(str2);
//     int maxLen = imax(len1, len2);

//     // int numRows = len1 + 1;
//     int numCols = len2 + 1;

//     int maxScore = 0;
//     int* scores;

//     int* thisArr;
//     int* lastArr;
//     int* hold;

//     int this;
//     int right;
//     int down;
//     int diagonal;


//     // Both empty - 100% equal
//     if (len1 == 0 && len2 == 0)
//         return (double)1;
//     // Exactly 1 empty - 0% equal
//     else if ((len1 == 0) != (len2 == 0)) // xor
//         return (double)0;

//     scores = (int*)calloc(2 * numCols, sizeof(int));

//     if (scores == NULL)
//         return -1; // calloc failed :(

//     thisArr = scores;
//     lastArr = (scores + numCols);
    
//     // bottom up DP but with O(2n) + c memory
//     for (int rowNum = len1 - 1; rowNum >= 0; rowNum--)
//     {
//         *(thisArr + len2) = 0; // reset "buffer" column
//         for (int colNum = len2 - 1; colNum >= 0; colNum--)
//         {
//             diagonal = *(lastArr + colNum + 1);

//             if (str1[rowNum] == str2[colNum])
//             {
//                 this = diagonal + maxLen;
//                 *(thisArr + colNum) = this;
//                 maxScore = imax(this, maxScore);
//             }
//             else
//             {
//                 right = *(thisArr + colNum + 1);
//                 down = *(lastArr + colNum);
//                 this = imax3(
//                     right -1,
//                     down - 1,
//                     diagonal
//                 );
//                 *(thisArr + colNum) = this;
//             }
//         }
//         hold = thisArr;
//         thisArr = lastArr;
//         lastArr = hold;
//     }
//     double to_return = maxScore / ((double)len1 * (double)len2);
//     free(scores);
//     return to_return;
// }