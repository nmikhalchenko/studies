//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "data.h"


/*  T O D O   */
/*
    Rewrite the write and read functions according
    to the current state of data.h and data.c.
*/


int main(void)
{
    Data data = {0};

    char c = 'a';
    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        dataSetField(&data, i, &c);
        c++;
    }

    dataPrint(&data, -20);

    return 0;
}
