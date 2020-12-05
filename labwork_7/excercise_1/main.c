//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "shared_code/shared_code.h"

int indexOfFirstRowWithPositiveElement(int rows, int cols, int matrix[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int elem = matrix[i][j];

            if (elem > 0)
            {
                return i;
            }
        }
    }

    return -1;
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
    printf("The number of a row with a positive element: %i\n", 
        indexOfFirstRowWithPositiveElement(rows, cols, matrix) + 1);

    return 0;
}
