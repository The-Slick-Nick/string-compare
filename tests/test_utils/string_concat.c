#include "string_concat.h"


#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


// Concat all provided strings, writing result into a provided character buffer.
// Note it is up to the caller to ensure the buffer is large enough to fit every
// string.
char* string_concat(char* buffer, int num_strings, ...)
{
    va_list to_concat;

    // int total_len = 0;
    int this_len;
    char* loop_str;
    // char* to_return;

    // int idx_arg;

    // calculate total length for allocation
    // va_start(to_concat, num_strings);
    // for (int i = 0; i < num_strings; i++)
    // {
    //     loop_str = va_arg(to_concat, char*);
    //     total_len += strlen(loop_str);
    // }
    // va_end(to_concat);

    // create pointer to newly allocated character array of appropriate length
    // to_return = (char*)malloc((1 + total_len) * sizeof(char));

    // populate new array with every character from all string arguments
    int idx_return = 0;
    va_start(to_concat, num_strings);
    for (int i = 0; i < num_strings; i++)
    {
        loop_str = va_arg(to_concat, char*);
        this_len = strlen(loop_str);
        for (int idx_arg = 0; idx_arg < this_len; idx_arg++)
        {
            buffer[idx_return] = loop_str[idx_arg];
            // buffer[idx_return] = *(loop_str + idx_arg);
            // *(to_return + idx_return) = *(loop_str + idx_arg);
            idx_return ++;
        }
    }
    // don't forget the null terminator
    buffer[idx_return] = '\0';
    // *(to_return + idx_return) = '\0';
    va_end(to_concat);
    // return to_return;
    return buffer;
}
