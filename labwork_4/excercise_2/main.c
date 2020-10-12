//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "unique.h"

#define ARRSIZE 5

void displayArray(int* arr, size_t size)
{
    for (int i = 0; i < size; i++)
        printf("%i\n", arr[i]);
}

int main(void)
{
    // Наш "какой-то" массив.
    int in[ARRSIZE] = {1, 2, 2, 3, 4};

    puts("Изначальный массив:");
    displayArray(in, ARRSIZE);
    puts("");

    int* out = NULL;
    size_t outSize = 0;

    extractUnique(in, ARRSIZE, &out, &outSize);

    puts("Массив с вырезанными повторяющимися элементами:");
    displayArray(out, outSize);

    free(out);
    out = NULL;

    return 0;
}