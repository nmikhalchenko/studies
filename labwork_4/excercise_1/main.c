//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "unique.h"

#define ARRSIZE 11

int main(void)
{
    int arr1[ARRSIZE] = {2, 2, 3, 6, 6, 5, 7, 10, 20, 20, 20};
    printUnique(arr1, ARRSIZE);

    return 0;
}
