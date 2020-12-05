#include <stdbool.h>
#include <stdio.h>

#include "unique.h"

typedef struct
{
    int number;
    bool isRepeated;
} NumberUniqueness;

typedef struct
{
    int* array;
    int size;
} UniqueArray;

static UniqueArray getUniqueElements(int* inputArr, int arrSize)
{
    NumberUniqueness* knownNumbersBuf = 
        (NumberUniqueness*)calloc(arrSize, sizeof(NumberUniqueness));
    
    int knownBufTop = 0;

    for (int i = 0; i < arrSize; i++)
    {
        // Проверяем, был ли уже такой номер.
        bool isRepeated = false;
        for (int j = 0; j < knownBufTop; j++)
        {
            if (inputArr[i] == knownNumbersBuf[j].number)
            {
                isRepeated = true;
                knownNumbersBuf[j].isRepeated = isRepeated;
                break;
            }
        }

        // Смотрим на флажок. Он показывает, есть ли
        // уже такой номер. Если нет - добавляем.
        if (!isRepeated)
        {
            knownNumbersBuf[knownBufTop].number = inputArr[i];
            knownNumbersBuf[knownBufTop].isRepeated = false;
            knownBufTop++;
        }
    }

    int outSize = 0;

    for (int i = 0; i < knownBufTop; i++)
        outSize += !knownNumbersBuf[i].isRepeated;

    UniqueArray uniqueNumbers;
    uniqueNumbers.array = (int*)calloc(outSize, sizeof(int));
    uniqueNumbers.size = outSize;

    int uniqueArrayTop = 0;

    for (int i = 0; i < knownBufTop; i++)
        if (!knownNumbersBuf[i].isRepeated)
            uniqueNumbers.array[uniqueArrayTop++] = 
                knownNumbersBuf[i].number;

    free((void*)knownNumbersBuf);
    knownNumbersBuf = NULL;

    return uniqueNumbers;
}

static void freeUniqueArray(UniqueArray* uniques)
{
    free((void*)uniques->array);
    uniques->array = NULL;
    uniques->size = 0;
}

void getUnique(int* inputArr, int inputArrSize, 
                   int** outputArr, int* outputArrSize)
{
    UniqueArray uniques = getUniqueElements(inputArr, inputArrSize);
    *outputArr = uniques.array;
    *outputArrSize = uniques.size;
}

void printUnique(int* arr, int size)
{
    UniqueArray uniques = getUniqueElements(arr, size);
    for (int i = 0; i < uniques.size; i++)
    {
        printf("%i\n", uniques.array[i]);
    }
    freeUniqueArray(&uniques);
}