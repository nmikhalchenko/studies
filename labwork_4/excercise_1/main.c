//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "shared_code/shared_code.h"
#include "unique.h"

#define ARRSIZE 10

int main(void)
{
    int arr1[ARRSIZE];
    requestIntArray(ARRSIZE, arr1, "Enter array:\n", true);

    puts("The array:");
    printIntArray(ARRSIZE, arr1, false);
    puts("");

    puts("Unique elements of the array:");
    printUnique(arr1, ARRSIZE);

    return 0;
}
