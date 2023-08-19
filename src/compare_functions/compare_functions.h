#ifndef INCLUDE_GUARD_COMPARE_FUNCTIONS
#define INCLUDE_GUARD_COMPARE_FUNCTIONS

double cdist_score(const char*, const char*);
double fss_score(const char* str1, const char* str2);
double adjusted_fss_score(const char* str1, const char* str2);
double naive_fss_score(const char* str1, const char* str2);
double adjusted_naive_fss_score(const char* str1, const char* str2);
double lcs_score(const char* str1, const char* str2);
double naive_lcs_score(const char* str1, const char* str2);

double print_score_matrix(int *matrix, int len1, int len2);
double levenshtein_score(const char* str1, const char* str2);



#endif