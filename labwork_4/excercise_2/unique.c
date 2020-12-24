#include <stdio.h>

#include "unique.h"

typedef struct
{
    int number;
    unsigned char isRepeated;
} NumberUniqueness;

typedef struct
{
    int* uniqueArray;
    size_t arraySize;
} UniqueArrayInfo;

static UniqueArrayInfo getUnique(int* inputArr, size_t arrSize)
{
    NumberUniqueness* knownNumbersBuf = 
        (NumberUniqueness*)calloc(
            arrSize, sizeof(NumberUniqueness));
    
    size_t knownBufTop = 0;

    for (size_t i = 0; i < arrSize; i++)
    {
        // Проверяем, был ли уже такой номер.
        unsigned char isRepeated = 0;
        for (size_t j = 0; j < knownBufTop; j++)
        {
            if (inputArr[i] == knownNumbersBuf[j].number)
            {
                isRepeated = 1;
                knownNumbersBuf[j].isRepeated = isRepeated;
                break;
            }
        }

        // Смотрим на флажок. Он показывает, есть ли
        // уже такой номер. Если нет - добавляем.
        if (!isRepeated)
        {
            knownNumbersBuf[knownBufTop].number = inputArr[i];
            knownNumbersBuf[knownBufTop].isRepeated = 0;
            knownBufTop++;
        }
    }

    size_t outSize = knownBufTop;

    // for (size_t i = 0; i < knownBufTop; i++)
    //     outSize += !knownNumbersBuf[i].isRepeated;

    UniqueArrayInfo info;
    info.uniqueArray = (int*)calloc(outSize, sizeof(int));
    info.arraySize = outSize;

    size_t uniqueArrayTop = 0;

    for (size_t i = 0; i < knownBufTop; i++)
        info.uniqueArray[uniqueArrayTop++] = 
            knownNumbersBuf[i].number;

    free((void*)knownNumbersBuf);
    knownNumbersBuf = NULL;

    return info;
}

static void freeUnique(UniqueArrayInfo* info)
{
    free((void*)info->uniqueArray);
    info->uniqueArray = NULL;
    info->arraySize = 0;
}

void extractUnique(int* inputArr, size_t inputArrSize, 
                   int** outputArr, size_t* outputArrSize)
{
    UniqueArrayInfo info = getUnique(inputArr, inputArrSize);
    *outputArr = info.uniqueArray;
    *outputArrSize = info.arraySize;
}

void printUnique(int* arr, size_t size)
{
    UniqueArrayInfo info = getUnique(arr, size);
    for (size_t i = 0; i < info.arraySize; i++)
    {
        printf("%i\n", info.uniqueArray[i]);
    }
    freeUnique(&info);
}