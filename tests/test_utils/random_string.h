#include <string.h>
#include <stdlib.h>

#ifndef INCLUDE_GUARD_RANDOM_STRING
#define INCLUDE_GUARD_RANDOM_STRING

#define RANDOMSTR_MIN_LENGTH    1
#define RANDOMSTR_MAX_LENGTH    10

#define CHARSET_NUMBERS         0
#define CHARSET_UPPERCASE       1
#define CHARSET_LOWERCASE       2


// Returns a string of random characters of random length
char* random_string()
{
    int char_set = rand() % 3;
    int len = RANDOMSTR_MIN_LENGTH + rand() % RANDOMSTR_MAX_LENGTH;
    int this_char;

    char* return_str = (char*)malloc((1 + len) * sizeof(char));

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
        *(return_str + i) = (char)this_char;
        i++;
    }
    *(return_str + i) = '\0';
    return return_str;
}

// Returns a random string of characters from only one specific character set
char* random_string_charset(int char_set)
{
    int len = RANDOMSTR_MIN_LENGTH + rand() % RANDOMSTR_MAX_LENGTH;
    
    char* return_str = (char*)malloc((1 + len) * sizeof(char));
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
        }
        *(return_str + i) = (char)this_char;
        i++;
    }
    *(return_str + i) = '\0';
    return return_str;
}

#endif