//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "shared_code/shared_code.h"
#include "unique.h"

#define ARRSIZE 10

void displayArray(int* arr, size_t size)
{
    for (int i = 0; i < size; i++)
        printf("%i\n", arr[i]);
}

int main(void)
{
    int in[ARRSIZE];
    requestIntArray(ARRSIZE, in, "Enter array:\n", true);

    puts("The array:");
    printIntArray(ARRSIZE, in, true);
    puts("");

    int* out = NULL;
    size_t outSize = 0;

    extractUnique(in, ARRSIZE, &out, &outSize);

    puts("Without duplicate elements:");
    printIntArray(outSize, out, true);

    free(out);
    out = NULL;

    return 0;
}