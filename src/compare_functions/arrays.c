#include "arrays.h"
#include <stdlib.h>
#include <stdio.h>
#include "max_min.h"

// takes 10 to the exponent provided
static int _pow10(int num)
{
    if (num == 0)
        return 1;

    if (num < 0)
        return -1;

    int exp = 10;
    int result = 1;

    while (num > 0)
    {

        if ((num & 1) == 1)
            result = result * exp;

        exp *= exp;
        num >>= 1;

    }
    return result;
}

// finds the number of digits in a base-10 representation
// of num
static int numDigits(int num)
{
    if (num == 0)
        return 1;

    int right = 9;
    int left = 0;
    int mid;

    if ((num / _pow10(right)) > 0)
        return right;

    while (left < right - 1)
    {
        mid = (right + left) / 2;

        if ((num / _pow10(mid)) > 0)
            left = mid;
        else    
            right = mid;
    }
    return left + 1;

}

void printInt2d(int* arrPtr, int rows, int cols)
{

    int maxLen = 1;
    int cellVal;
    int valLen;

    // determine maximum length of integer print value
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cellVal = ACCESS_2D(arrPtr, cols, i, j);
            valLen = numDigits(cellVal);
            maxLen = imax(maxLen, numDigits(cellVal));
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cellVal = ACCESS_2D(arrPtr, cols, i, j);
            valLen = numDigits(cellVal);
            // print value
            printf("%d", cellVal);

            // print extra "padding" vs max length, with one extra added
            for (int _ = 0; _ <= maxLen - valLen; _++)
                printf(" ");
        }
        printf("\n");
    }
}