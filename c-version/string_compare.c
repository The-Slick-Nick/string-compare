#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "string_compare_components.h"


int num_common_chars(const char* str1, const char* str2)
/*
Returns the number of characters common to both str1 and str2.
To be used for sizing filtered char arrays
*/
{
    // Indices for looping through str1 and str2
    int i1;
    int i2;

    // Number of common characters found. Value to return
    int num_common = 0;

    // Use str2 as comparison basis, only need a distribution for it
    int str2_dist[256] = {0};

    // Loop through str2 to build char distribution array
    for(i2 = 0; *(str2 + i2) != '\0'; i2++)
    {
        str2_dist[*(str2 + i2)]++;
    }

    // Loop through str1 to tally common characters by comparint to str2_dist
    for(i1 = 0; *(str1 + i1) != '\0'; i1++)
    {
        if(str2_dist[*(str1 + i1)] > 0)
        {
            num_common++;
            str2_dist[*(str1 + i1)]--;
        }
    }

    return num_common;
}

void filter_common_chars(char* dest1, char* dest2, const char* str1, const char* str2)
/*
Filters str1 and str2 for characters common to both. Copies results into
dest1 and dest2 in same character order as they appear in str1 and str2.

Note that sizes of dest1 and dest2 should both be the size of the number of
common characters between str1 and str2
*/
{
    int i1;  // Index looping through str1
    int i2;  // Index looping through str2

    int dest_i;  // Index to build a destination str
    int dist_i;  // Index to loop through str_dist (to re-use it)

    int str_dist[256] = {0};

    // Build str_dist modeled after str2
    for (i2 = 0; *(str2+i2) != '\0'; i2++)
    {
        str_dist[*(str2+i2)]++;
    }

    // Build dest1 by comparing str1 to str_dist
    dest_i = 0;
    for (i1 = 0; *(str1+i1) != '\0'; i1++)
    {
        if(str_dist[*(str1+i1)] > 0)
        // Check if str1 char is found in str2
        {
            // Copy character into dest1
            dest1[dest_i] = *(str1+i1);
            dest_i++;

            // Consider character used in str_dist
            str_dist[*(str1+i1)]--;
        }
    }

    // Reset str_dist to use again
    for(dist_i=0; dist_i<256; dist_i++)
    {str_dist[dist_i] = 0;}

    // Model str_dist after i1
    for (i1 = 0; *(str1+i1) != '\0'; i1++)
    {
        str_dist[*(str1+i1)]++;
    }

    // Build dest2 by comparing str2 to str_dist
    dest_i = 0;
    for (i2 = 0; *(str2+i2) != '\0'; i2++)
    {
        if(str_dist[*(str2+i2)] > 0)
        // Check if str2 char was found in str1
        {
            dest2[dest_i] = *(str2 + i2);
            dest_i++;

            // Consider character used in str_dist
            str_dist[*(str2+i2)]--;
        }
    }
}


float order_score(const char* str1, const char* str2)
/*
Compares the character order of str1 and str2, returning a floating point (0-1)
assessment of their order similarity
*/
{
    int i1; // Index for accessing str1_common
    int i2; // Index for accessing str2_common
    int num_common;  // Number of characters common to str1 & str2
    int num_segments;  // Number of segments needed to match each character

    // Identify the number of characters total shared
    num_common = num_common_chars(str1, str2);

    // Break early for edge cases - protect from dividing by 0 later
    if(num_common == 0)
    // No matching chars always means 0 order_score
    {
        return (float)0;
    }
    else if(num_common == 1)
    // Only 1 common character means perfect order score
    {
        return (float)1;
    }

    // Now define our common strings
    char str1_common[num_common];
    char str2_common[num_common];

    // Perform filter before comparison begins
    filter_common_chars(str1_common, str2_common, str1, str2);

    num_segments = 0;
    while(i1 < num_common)
    {
        num_segments++;
        i2 = 0;
        while(i2 < num_common && i1 < num_common)
        {

            if( *(str1_common+i1) == *(str2_common+i2) )
            {
                // Mark str2 char as considered
                str2_common[i2] = '\0';

                // Move i1 only if a match is found
                i1++;
            }
            // Always move i2
            i2++;
        }
        // Note that i1 need not be incremented here. As str1_common and
        // str2_common are both filtered for the same set of chars, at least
        // one i1++ call will be reached per i1 char.
    }

    // Score considers the number of ADDITIONAL segments (from 1) needed to
    // match every character (as each comparison will always have at least 1)
    return ( (num_common-1) - (num_segments-1) ) / (float)(num_common - 1);
}

float order_score2(char* str1, char* str2)
{
    struct listHead* cdist[256];
    struct listHead* dist_i2;
    struct listItem* item_i2;  // List item for traversing dist_i2


    int i1, i2;
    bool has_match;

    // Initialize array of lists
    for(int i = 0; i < 256; i++)
    {
        cdist[i] = list_init();
    }

    for(int i2 = 0; str2[i2] != '\0'; i2++)
    {
        dist_i2 = cdist[str2[i2]];
        list_append(dist_i2, i2);
    }

    int num_common = 0; // number of common chars in str1 & str2
    int i2_min = -1;
    int num_resets = 0;  // number of times i2_min has been reset
    for(i1 = 0; str1[i1] != '\0'; i1++)
    {
        dist_i2 = cdist[str1[i1]];
        if(dist_i2->length == 0)
        {
            continue;
        }
        else
        // i2 has a char from i1, one more in-common
        {
            num_common++;
        }

        has_match=false;
        while(!has_match)
        {
            item_i2 = dist_i2->next;
            while(item_i2 != NULL)
            {
                if(item_i2->data > i2_min)
                {
                    i2_min = item_i2->data;
                    list_remove(dist_i2, item_i2->data);
                    has_match=true;
                    break;
                }
                item_i2 = item_i2->next;
            }
            if(!has_match)
            // If i2 has chars but none are below current index, reset & try again
            {
                num_resets++;
                i2_min=-1;
            }
        }
    }


    if(num_common == 0)
    {
        return 0;
    } else if (num_common == 1)
    {
        return 1;
    } else
    {
        // Max resets = num_common - 1
        // (since the first character will always be found without a reset)
        return ((num_common - 1) - num_resets) / (float)(num_common - 1);
    }
   
}


float letter_score(const char* str1, const char* str2)
/*
Compares two provided strings and provides a floating point assessment (0-1)
of how similar the character distributions of the two strings are.
*/
{
    int cdist[255] = {0};  // Tracked character distribution

    int i1, i2, i_dist;  // Indices for looping through str1, str2, and cdist
    int max_diff = 0;  // Maximum possible difference between the two
    int actual_diff = 0;  // Calculated difference between the two distributions

    int to_add = 0;  // Value to add within a loop

    // build cdist based on distribution of str1 characters
    for (i1 = 0; *(str1+i1) != '\0'; i1++)
    {
        max_diff++;

        // Use asc val of character in str1 for index in cdist
        cdist[*(str1+i1)]++;  // Increment for str1
    }

    // modify cdist based on distribution of str2 characters
    for (i2 = 0; *(str2+i2) != '\0'; i2++)
    {
        max_diff++;

        // Use asc val of character in str2 for index in cdist
        cdist[*(str2+i2)]--;// Decrement for str2
    }

    for (i_dist=0; i_dist<256; i_dist++)
    {
        actual_diff += abs(*(cdist+i_dist));
    }

    return (max_diff-actual_diff)/(float)max_diff;
}


float string_compare(const char* str1, const char* str2)
/*
Compares two provided strings and provides a floating point assessment (0-1)
of how similar the two strings are.
*/
{
    return sqrtf(
        letter_score(str1, str2) * order_score(str1, str2)
    );
}


char* random_string(int num_chars)
{
    char* new_str = malloc(num_chars + 1);
    int rchar;

    for(int i = 0; i <= num_chars; i++)
    {
        rchar = 62 + (int)(rand() % 25);
        *(new_str + i) = (char)rchar;
    }
    *(new_str+num_chars+1) = "\0";

    return new_str;

}

int main()
{\

    char* str1;
    char* str2;

    int r1;
    int r2;

    float os1;
    float os2;

    int num_common;
    int i;

    for(int numtests = 0; numtests < 5; numtests++)
    {

        str1 = random_string(10);
        str2 = random_string(10);

        os1 = order_score(str1, str2);
        os2 = order_score2(str1, str2);
        num_common = num_common_chars(str1, str2);
        printf("_______________________\n");
        printf("str1: %s\nstr2: %s\n", str1, str2);
        printf("num common %d", num_common);
        printf("\n");
        printf("oscore1: %f", os1);
        printf("\n");
        printf("oscore2: %f", os2);
        printf("\n");
        }
}