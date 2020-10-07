//Вариант 5

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define SZ 11

typedef struct
{
    int number;
    unsigned char isRepeated;
} NumberUniqueness;

void printUnique(int* arr, size_t size)
{
    NumberUniqueness* knownNumbersBuf = 
        (NumberUniqueness*)calloc(
            size, sizeof(NumberUniqueness));
    size_t knownBufLast = 0;

    for (size_t i = 0; i < size; i++)
    {
        unsigned char isRepeated = 0;
        for (size_t j = 0; j < knownBufLast; j++)
        {
            if (arr[i] == knownNumbersBuf[j].number)
            {
                knownNumbersBuf[j].isRepeated = 1;
                isRepeated = 1;
                break;
            }
        }

        if (!isRepeated)
        {
            knownNumbersBuf[knownBufLast].number = arr[i];
            knownNumbersBuf[knownBufLast].isRepeated = 0;
            knownBufLast++;
        }
    }

    for (size_t i = 0; i < knownBufLast; i++)
    {
        if (!knownNumbersBuf[i].isRepeated)
            printf("%i\n", knownNumbersBuf[i].number);
    }
}

int main(void)
{
    int arr1[SZ] = {2, 2, 3, 6, 6, 5, 7, 10, 20, 20, 20};
    printUnique(arr1, SZ);

    return 0;
}
