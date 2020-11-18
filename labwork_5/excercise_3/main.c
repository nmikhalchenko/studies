//Вариант 5

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int indexOfFirstRowWithPositiveElement(int rowCount, int colCount, int matrix[rowCount][colCount])
{
    int positiveIndex = -1;

    for (int i = 0; i < rowCount; i++)
    {
        bool hasPositive = false;
        for (int j = 0; j < colCount; j++)
        {
            if (hasPositive = (matrix[i][j] > 0))
            {
                positiveIndex = i;
                break;
            }
        }
        if (hasPositive)
            break;
    }

    return positiveIndex;
}

void flipSigns(int length, int row[length])
{
    for (int i = 0; i < length; i++)
        row[i] = -row[i];
}

void printRow(int length, int row[length])
{
    printf("{ ");
    for (int i = 0; i < length; i++)
    {
        printf("%i", row[i]);
        if (i < length - 1)
            printf(" ");
    }
    printf(" }");
}

int main(void)
{
    #define ROWS (5)
    #define COLS (4)

    int matrix[ROWS][COLS] =
    {
        { 0, 0, 0, 0},
        {-1, 0,-1, 0},
        {-1, 1, 0, 1},
        { 0, 0, 0, 0},
        {-1,-1,-1,-1}
    };

    int positiveIndex = indexOfFirstRowWithPositiveElement(ROWS, COLS, matrix);

    if (positiveIndex >= 0)
    {
        printf("The index of the first row with a positive element: %i\n", positiveIndex + 1);
        printf("The row itself: ");
        printRow(COLS, matrix[positiveIndex]);
        puts("");

        int prevRowIndex = positiveIndex - 1;
        if (prevRowIndex >= 0)
        {
            int* flippedRow = matrix[positiveIndex - 1];
            printf("Previous row: ");
            printRow(COLS, flippedRow);
            puts("");

            flipSigns(COLS, flippedRow);
            printf("Previous row with element signs flipped: ");
            printRow(COLS, flippedRow);
            puts("");
        }
        else
            printf("This row has no previous row.");
    }
    else
        puts("This matrix has no rows with positive elements.");

    return 0;
}
