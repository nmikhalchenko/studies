//Вариант 5

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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
    #define ROWS (5)
    #define COLS (4)

    int matrix[ROWS][COLS] =
    {
        {2, 3, 4, 1},
        {1, 0, 3, 0},
        {1, 0, 2, 0},
        {2, 3, 4, 5},
        {1, 2, 5, 1}
    };

    printf("Column without zeroes count: %i\n", countColumnsWithoutZeroes(ROWS, COLS, matrix));

    return 0;
}