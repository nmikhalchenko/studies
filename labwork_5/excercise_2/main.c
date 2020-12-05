//Вариант 5

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "shared_code/shared_code.h"

int countColumnsWithoutZeroes(int rowCount, int colCount, int matrix[rowCount][colCount])
{
    int count = 0;

    for (int j = 0; j < colCount; j++)
    {
        bool hasZeroes = false;
        for (int i = 0; i < rowCount; i++)
        {
            if (matrix[i][j] == 0)
            {
                hasZeroes = true;
                break;
            }
        }
        count += hasZeroes ? 0 : 1;
    }
    
    return count;
}

int main(void)
{
    int rows = requestSize("Enter row amount (higher than zero): ");
    int cols = requestSize("Enter column amount (higher than zero): ");
    int* matrix = (int*)calloc(rows * cols, sizeof(int));

    requestIntMatrix(rows, cols, matrix, NULL, true);
    printf("Zeroless column count: %i\n", countColumnsWithoutZeroes(rows, cols, matrix));

    free(matrix);

    return 0;
}