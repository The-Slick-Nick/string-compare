#include "string_compare_components.h"
#include <stdlib.h>

int main()
{
    struct listHead* my_list = list_init();

    list_append(my_list, 'h');

    char* result = list_to_char_array(my_list);
    printf("%s", result);
    printf("%c", -1);

}