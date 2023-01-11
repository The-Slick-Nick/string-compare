/*----------------------------------------------------------------------------------------
fcs_score.h

Fragmented Substring Score

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
#ifndef INCLUDE_GUARD_FSS_SCORE
#define INCLUDE_GUARD_FSS_SCORE

#include "../components/calc_groups.h"

// Scores two strings based on the number of substring matches between the two

double fss_score(char* str1, char* str2)
{
    return 0;
}


double adjusted_fss_score(char* str1, char* str2)
{
    return 0;
}


#endif