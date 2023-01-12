#include "c_version\compare_functions\fss_score.h"




int main()
{
    // char str1[] = "D646554P4kx|jJXF2u4x7YA|rUuy002p3DG5024S1Bk~3L1p7045s17NJLz7XQfK6j268Sjq}751ykoe";
    // char str2[] = "D646554P4kx|jJXF2u4x7YA|rUuy002p3DG5024S1Bk~3L1p7045s17NJLz7XQfK6j268Sjq}751ykoe";

    char str1[] = "1OAA7EoOq";
    char str2[] = "8Yj{yRX1OAA7EoOq";
    
    double score;

    score = naive_fss_score(str1, str2);
    printf("naive fss %f\n", score);
}