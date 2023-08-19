#include "compare_functions.h"
#include "max_min.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


double levenshtein_score(const char* str1, const char* str2)
{

    int len1;
    int len2;

    int idx1;
    int idx2;

    unsigned char chr1;
    unsigned char chr2;

    int cost;

    int up;
    int left;
    int diagonal;

    len1 = strlen(str1);
    len2 = strlen(str2);

    if ((len1 == 0) && (len2 == 0))
        return 1;
    
    if ((len1 == 0) != (len2 == 0))
        return 0;

    // bottom up DP with O(2n) size
    int* scores = (int*)malloc((2 * (len1 + 1)) * sizeof(int));

    int* thisArr = scores;
    int* lastArr = (scores + (len1 + 1));
    int* hold;

    // Write in "row 0"
    for (int i = 0; i < len1 + 1; i++)
    {
        *(lastArr + i) = i;
    }

    for (idx2 = 1; idx2 <= len2; idx2++)
    {
        // Write value for "column 0"
        *(thisArr) = idx2;
        chr2 = str2[idx2 - 1];
        for (idx1 = 1; idx1 <= len1; idx1++)
        {
            chr1 = str1[idx1 - 1];

            if (chr1 == chr2)
                cost = 0;
            else
                cost = 1;

            up = *(lastArr + idx1);
            left = *(thisArr + idx1 - 1);
            diagonal = *(lastArr + idx1 - 1);

            *(thisArr + idx1) = imin3(
                up + 1,
                left + 1,
                diagonal + cost
            );
            
        }
        hold = thisArr;
        thisArr = lastArr;
        lastArr = hold;

    }

    int minDistance = *(lastArr + len1);
    free(scores);

    // Correct/adjust based on longer string
    if (len1 > len2)
        return (len1 - minDistance) / (double)len1;
    else
        return (len2 - minDistance) / (double)len2;


}