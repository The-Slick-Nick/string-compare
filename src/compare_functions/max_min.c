#include "max_min.h"

inline int imax(int a, int b)
{
    return ( (a) > (b) ? (a) : (b) );
}

inline int imax3(int a, int b, int c)
{
    return ( imax(a, b) > (c) ? imax(a, b) : (c) );
}

inline int imin(int a, int b)
{
    return ( (a) < (b) ? (a) : (b) );
}

inline int imin3(int a, int b, int c)
{
    return ( imin(a, b) < (c) ? imin(a, b) : (c));
}