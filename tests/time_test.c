#include <stdio.h>

#include "test_utils/comparefunc_timer.c"

#include "../strcompare/compare_functions/cdist_score.h"
#include "../strcompare/compare_functions/fss_score.h"
#include "../strcompare/compare_functions/lcs_score.h"
#include "../strcompare/compare_functions/levenshtein_score.h"

int main()
{
    CFUNC_TIMER_START;
    CFUNC_TIMER_ADD(cdist_score, "cdist");

    CFUNC_TIMER_ADD(fss_score, "fss score");
    CFUNC_TIMER_ADD(adjusted_fss_score, "adjusted fss score");
    CFUNC_TIMER_ADD(naive_fss_score, "naive fss score");
    CFUNC_TIMER_ADD(adjusted_naive_fss_score, "adjusted naive fss score");

    CFUNC_TIMER_ADD(lcs_score, "lcs score");
    CFUNC_TIMER_ADD(naive_lcs_score, "naive lcs score");

    CFUNC_TIMER_ADD(levenshtein_score, "levenshtein score");

    CFUNC_TIMER_END;
}