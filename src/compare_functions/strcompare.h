/*========================================================================================
strcompare.h

A collection of methods that compare two strings to assess their similarity
========================================================================================*/


#ifndef INCLUDE_GUARD_STRCOMPARE
#define INCLUDE_GUARD_STRCOMPARE


/// @brief Compare two strings by assessing differences in their distribution of
/// characters
/// @param str1 Pointer to first string to compare. 
/// @param str2 Pointer to second string to compare.
/// @return Floating point number representing the ratio of character mismatches
/// to the total length among the two strings.
double cdist_score(const char* str1, const char* str2);


int levenshtein_distance(const char* str1, const char* str2);

double levenshtein_major(const char* str1, const char* str2);
double levenshtein_minor(const char* str1, const char* str2);



double fss_score(const char* str1, const char* str2);
double adjusted_fss_score(const char* str1, const char* str2);
double naive_fss_score(const char* str1, const char* str2);
double adjusted_naive_fss_score(const char* str1, const char* str2);
double lcs_score(const char* str1, const char* str2);
double naive_lcs_score(const char* str1, const char* str2);

double print_score_matrix(int *matrix, int len1, int len2);



#endif