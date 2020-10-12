//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "unique.h"

#define ARRSIZE 11

void displayArray(int* arr, size_t size)
{
    for (int i = 0; i < size; i++)
        printf("%i\n", arr[i]);
}

int main(void)
{
    int arr1[ARRSIZE] = {2, 2, 3, 6, 6, 5, 7, 10, 20, 20, 20};

    puts("Изначальный массив:");
    displayArray(arr1, ARRSIZE);
    puts("");

    puts("Уникальные элементы этого массива:");
    printUnique(arr1, ARRSIZE);

    return 0;
}
