//Вариант 5

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "shared_code/shared_code.h"

int countColumnsWithoutZeroes(int rows, int cols, int* matrix)
{
    int count = 0;
    for (int j = 0; j < cols; j++)
    {
        bool zero = false;
        for (int i = 0; i < rows; i++)
        {
            if (matrix[rows * i + j] == 0)
                zero = true;
        }
        count += !zero;
    }

    return count;
}

int main(void)
{

    int rows = requestSize("Enter row count: ");
    int cols = requestSize("Enter column count: ");
    int* matrix = (int*)calloc(rows * cols, sizeof(int));

    requestIntMatrix(rows, cols, matrix, "Enter matrix:\n", true);
    puts("");
    puts("Matrix:");
    printIntMatrix(rows, cols, matrix, true);

    int count = countColumnsWithoutZeroes(rows, cols, matrix);
    printf("Zeroless column count: %i\n", count);
    
    free(matrix);
    
    return 0;
}
