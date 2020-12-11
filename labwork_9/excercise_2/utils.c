#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

/* Seems like a weird approach at first, but
   see "https://stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c",
   this one seems to be the fastest and the simplest at once. */
int digitCount(int number)
{
    if (number < 0) number = number == INT_MIN ? 
        INT_MAX : -number;
    if (number < 10) return 1;
    if (number < 100) return 2;
    if (number < 1000) return 3;
    if (number < 10000) return 4;
    if (number < 100000) return 5;
    if (number < 1000000) return 6;
    if (number < 10000000) return 7;
    if (number < 100000000) return 8;
    if (number < 1000000000) return 9;
    return 10;
}

bool tryPadFormatSpecifier(const char* specifier, int padding, char* output, int length)
{
    if (!specifier)
    {
        return false;
    }

    int speclen = strlen(specifier);
    int digits = digitCount(padding);
    digits += (padding < 0);
    int reqlen = speclen + digits + 1;
    if (speclen < 2 || length < reqlen)
    {
        return false;
    }
    snprintf(output, length, "%%%i%s", padding, specifier + 1);

    return true;
}