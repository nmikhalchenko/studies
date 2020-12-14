#ifndef DATA_IO_H
#define DATA_IO_H

#include <stdbool.h>

#include "data.h"

typedef enum
{
    DataFileMode_append,
    DataFileMode_read,
    DataFileMode_write

} DataFileMode;

typedef struct
{
    FILE* file;
    DataFileMode mode;

} DataFile;

DataFile dataFileOpen(const char* filename, DataFileMode mode);
bool dataFileReopen(const char* filename, DataFileMode mode, DataFile* file);
void dataFileClose(DataFile* file);
bool dataFileAppend(DataFile file, const DataReference data);
bool dataFileRead(DataFile file, DataReference output);
bool dataFileWrite(DataFile file, const DataReference data);

#endif // DATA_IO_H