#include <string.h>
#include <stdlib.h>
#include "random_string.h"

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
            case CHARSET_EXTENDED: // 128-255
                this_char = 128 + rand() % (255 - 128);
                break;
        }
        *(return_str + i) = (char)this_char;
        i++;
    }
    *(return_str + i) = '\0';
    return return_str;
}