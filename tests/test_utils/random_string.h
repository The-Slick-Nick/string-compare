
#ifndef INCLUDE_GUARD_RANDOM_STRING
#define INCLUDE_GUARD_RANDOM_STRING

#define RANDOMSTR_MIN_LENGTH    1
#define RANDOMSTR_MAX_LENGTH    100

#define CHARSET_NUMBERS         0
#define CHARSET_UPPERCASE       1
#define CHARSET_LOWERCASE       2
#define CHARSET_EXTENDED        3


// Returns a string of random characters of random length
char* random_string();

// Returns a random string of characters from only one specific character set
char* random_string_charset(int char_set);

#endif