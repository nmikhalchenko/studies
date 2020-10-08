//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "unique.h"

#define ARRSIZE 5

int main(void)
{
    // Наш "какой-то" массив.
    int in[ARRSIZE] = {1, 2, 2, 3, 4};

    int* out = NULL;
    size_t outSize = 0;

    extractUnique(in, ARRSIZE, &out, &outSize);

    for (size_t i = 0; i < outSize; i++)
        printf("%i\n", out[i]);

    free(out);
    out = NULL;

    return 0;
}