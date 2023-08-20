#include <string.h>
#include <stdlib.h>
#include "random_string.h"

#define RANDOMIZED_LENGTH(lower, upper) (rand() % (upper - lower + 1)) + lower


// Writes a randomized string into the provided character buffer
// Note that it is up to the caller to ensure that the buffer is at least as long
// as RANDOMSTR_MAX_LENGTH.
char* random_string(char* buffer)
{
    int char_set = rand() % 3;
    int len = RANDOMIZED_LENGTH(RANDOMSTR_MIN_LENGTH, RANDOMSTR_MAX_LENGTH);
    int this_char;

    // "len" calculated is the length INCLUDING the null terminator
    // i.e. length = 5 could possibly generate string "BOAT", as
    // BOAT is ['B', 'O', 'A', 'T', '\0'] for a total of 5 characters, including
    // null terminator

    int i = 0;
    while (i < len)
    {
        char_set = rand() % 3;
        switch (char_set)
        {
            case CHARSET_NUMBERS:
                this_char = 48 + rand() % (57 - 48);
                break;
            case CHARSET_UPPERCASE: // uppercase letters
                this_char = 65 + rand() % (90 - 65);
                break;
            case CHARSET_LOWERCASE: // lowercase letters
                this_char = 97 + rand() % (127 - 97);
                break;
        }
        buffer[i] = (char)this_char;
        i++;
    }
    buffer[len] = '\0';
    return buffer;
}


// Writes a randomized string into the provided character buffer, picking only
// characters from a specific character set.
char* random_string_charset(char* buffer, int char_set)
{
    int len = RANDOMIZED_LENGTH(RANDOMSTR_MIN_LENGTH, RANDOMSTR_MAX_LENGTH);
    
    char this_char;

    int i = 0;
    while (i < len)
    {
        switch (char_set)
        {
            case CHARSET_NUMBERS:
                this_char = 48 + rand() % (57 - 48);
                break;
            case CHARSET_UPPERCASE: // uppercase letters
                this_char = 65 + rand() % (90 - 65);
                break;
            case CHARSET_LOWERCASE: // lowercase letters
                this_char = 97 + rand() % (127 - 97);
                break;
            case CHARSET_EXTENDED: // 128-255
                this_char = 128 + rand() % (255 - 128);
                break;
        }
        buffer[i] = (char)this_char;
        i++;
    }
    buffer[len] = '\0';
    return buffer;
}