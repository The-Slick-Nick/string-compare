#include "string_compare_components.h"
#include <stdlib.h>

int main()
{
    struct listHead* my_list = list_init();

    for(int i = 1; i<200; i++)
    {
        if(i<100)
        {list_append(my_list, i);}
        else
        {list_insert(my_list, i);}
    }
    list_print(my_list);
    free(list_remove(my_list, 10));
    list_print(my_list);
}