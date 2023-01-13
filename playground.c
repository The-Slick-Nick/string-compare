#include "c_version\compare_functions\fss_score.h"
#include "c_version\compare_functions\lcs_score.h"
#include "..\EWENIT\EWENIT\EWENIT.c"




int main()
{
    // char str1[] = "D646554P4kx|jJXF2u4x7YA|rUuy002p3DG5024S1Bk~3L1p7045s17NJLz7XQfK6j268Sjq}751ykoe";
    // char str2[] = "D646554P4kx|jJXF2u4x7YA|rUuy002p3DG5024S1Bk~3L1p7045s17NJLz7XQfK6j268Sjq}751ykoe";

    double expected = (double)4/7;
    double actual = lcs_score("stressed", "dessert");

    printf("exp %.100f\n", expected);
    printf("act %.100f\n", actual);
    printf("diff %.100f\n", fabs(actual - expected));
    printf("epsilon %.100f\n", DBL_EPSILON);
}