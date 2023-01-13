#include "c_version\compare_functions\fss_score.h"
#include "c_version\compare_functions\lcs_score.h"
#include "c_version\compare_functions\levenshtein_score.h"
#include "..\EWENIT\EWENIT\EWENIT.c"




int main()
{
    // char str1[] = "D646554P4kx|jJXF2u4x7YA|rUuy002p3DG5024S1Bk~3L1p7045s17NJLz7XQfK6j268Sjq}751ykoe";
    // char str2[] = "D646554P4kx|jJXF2u4x7YA|rUuy002p3DG5024S1Bk~3L1p7045s17NJLz7XQfK6j268Sjq}751ykoe";

    
    printf("\n%f\n", levenshtein_score("stressed", "dessert"));
}