
#ifndef INCLUDE_GUARD_RANDOM_STRING
#define INCLUDE_GUARD_RANDOM_STRING

#define RANDOMSTR_MIN_LENGTH    1
#define RANDOMSTR_MAX_LENGTH    100

#define CHARSET_NUMBERS         0
#define CHARSET_UPPERCASE       1
#define CHARSET_LOWERCASE       2
#define CHARSET_EXTENDED        3


// Writes a randomized string into the provided character buffer
// Note that it is up to the caller to ensure that the buffer is at least as long
// as RANDOMSTR_MAX_LENGTH
char* random_string(char* buffer);

// Writes a randomized string into the provided character buffer, picking only
// characters from a specific character set.
char* random_string_charset(char* buffer, int char_set);

#endif