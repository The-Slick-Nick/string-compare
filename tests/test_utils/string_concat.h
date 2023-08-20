/*========================================================================================
string_concat.h

Because <string.h> function strcat doesn't work like I need it to
========================================================================================*/
#ifndef INCLUDE_GUARD_STRING_CONCAT
#define INCLUDE_GUARD_STRING_CONCAT


// Concat all provided strings in variable arg list, returning a pointer to a newly
// allocated character array representing the full concatenated string
char* string_concat(int num_strings, ...);

#endif