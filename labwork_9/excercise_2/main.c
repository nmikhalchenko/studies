//Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "data_io.h"


/*  T O D O   */

#define FILENAME ("datafile")

void debugPrint(const DataReference data)
{
    printf("DATA:\n--------\n");
    dataPrint(data, -20);
    printf("--------\n\n");
}

int main(void)
{
    Data data = {0};
    dataSetField(&data, FieldName_fullName, "John Smith");
    dataSetField(&data, FieldName_libCardNumber, "25");
    dataSetField(&data, FieldName_bookName, "The Holy Bible");
    dataSetField(&data, FieldName_returnTerm, "31.12.2020");

    debugPrint(&data);

    DataFile file = dataFileOpen(FILENAME, DataFileMode_write);
    dataFileWrite(file, &data);
    dataFileClose(&file);

    dataFileReopen(FILENAME, DataFileMode_read, &file);
    Data another = {0};
    dataFileRead(file, &another);
    
    debugPrint(&another);


    return 0;
}
