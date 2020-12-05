//Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shared_code/shared_code.h"

int getPositiveRowSum(int rang, int sqMatrix[rang][rang])
{
    if (!sqMatrix)
        return 0;

    int totalSum = 0;

    for (int i = 0; i < rang; i++)
    {
        int rowSum = 0;
        for (int j = 0; j < rang; j++)
        {
            if (sqMatrix[i][j] < 0)
            {
                rowSum = 0;
                break;
            }
            
            rowSum += sqMatrix[i][j];
        }
        totalSum += rowSum;
        rowSum = 0;
    }

    return totalSum;
}

int* getParallelDiagonalSums(int rang, int sqMatrix[rang][rang], int* out, size_t outSize)
{
    int outi = 0;
    int dsum = 0;
    int r = rang - 1;
    int c = 0;

    if (!out || !sqMatrix)
        return NULL;

    while (c < rang)
    {
        if ((r != 0) || (c != 0))
        {
            if (outi >= outSize)
                break;

            for (int i = r, j = 0; i < rang; i++, j++)
            {
                int col = j + c;
                if (col >= rang)
                    break;
                dsum += sqMatrix[i][col];
            }

            out[outi++] = abs(dsum);
            dsum = 0;
        }

        if (r > 0)
            r--;
        else
            c++;
    }

    return out;
}

int getMin(int* numbers, int size)
{
    if (!numbers)
        return 0;

    int min = numbers[0];
    for (int i = 1; i < size; i++)
        min = numbers[i] < min ? numbers[i] : min;
    return min;
}

void printPositiveRowSumAndMinimalParallelDiagonalSum(int rang, 
                                                      int sqMatrix[rang][rang])
{
    int positiveRowSum = getPositiveRowSum(rang, sqMatrix);
    
    int parallelDiagonalSumCount = rang * 2 - 2;
    int parallelDiagonalSums[parallelDiagonalSumCount];
    int minParallelDiagonalSum = getMin(
        getParallelDiagonalSums(
            rang, sqMatrix, parallelDiagonalSums, parallelDiagonalSumCount), 
        parallelDiagonalSumCount);

    printf("Sum of rows without negative elements: %i\n", positiveRowSum);
    printf("Minimal parallel diagonal sum: %i\n", minParallelDiagonalSum);
}

int main(void)
{
    int size = requestSize("Enter matrix size (higher than zero): ");
    int* matrix = (int*)calloc(size * size, sizeof(int));

    requestIntMatrix(size, size, matrix, NULL, true);
    puts("Matrix:");
    printIntMatrix(size, size, matrix, true);
    puts("");

    printPositiveRowSumAndMinimalParallelDiagonalSum(size, matrix);

    free(matrix);

    return 0;
}