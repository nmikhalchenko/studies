#ifndef DATA_IO_H
#define DATA_IO_H

#include <stdbool.h>

#include "data.h"

#define MAX_DATA_IO_MODES (4)
typedef enum
{
    DataFileMode_none,
    DataFileMode_append,
    DataFileMode_read,
    DataFileMode_write

} DataFileMode;

typedef struct DataFile DataFile;

DataFile* dataFileOpen(const char* filename, DataFileMode mode);
bool dataFileReopen(const char* filename, DataFileMode mode, DataFile* file);
void dataFileRewind(DataFile* file);
void dataFileClose(DataFile* file);
DataFileMode dataFileGetMode(const DataFile* file);
int dataFileCount(const DataFile* file);
bool dataFileGoto(const DataFile* file, int index);
bool dataFileAppend(const DataFile* file, const Data* data);
bool dataFileRead(const DataFile* file, Data* output);
bool dataFileWrite(const DataFile* file, const Data* data);

#endif // DATA_IO_H