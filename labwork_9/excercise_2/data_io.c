#include <stdlib.h>
#include <stdio.h>

#include "data_io.h"

#define DATA_FILE_NAME ("datafile")
#define DATA_TOTAL_SIZE (MAX_DATA_FIELD_SIZE * MAX_DATA_FIELDS + 1)

#define MAX_DATA_IO_MODES (3)

static const char* const g_dataIOModeStrings[MAX_DATA_IO_MODES] =
{
    "a",
    "r",
    "w"
};

static bool performDataIO(DataFile file, DataFileMode mode, const DataReference input, DataReference output);
static bool readData(DataReference output, FILE* file);
static bool writeData(const DataReference data, FILE* file);

DataFile dataFileOpen(const char* filename, DataFileMode mode)
{
    DataFile dataFile = {.file = NULL, .mode = mode};
    
    const char* openmode = g_dataIOModeStrings[mode];
    FILE* file = fopen(filename, openmode);
    if (file)
    {
        dataFile.file = file;
    }

    return dataFile;
}

bool dataFileReopen(const char* filename, DataFileMode mode, DataFile* file)
{
    dataFileClose(file);
    *file = dataFileOpen(filename, mode);

    return file->file != NULL;
}

void dataFileClose(DataFile* file)
{
    if (file->file)
    {
        fclose(file->file);
        file->file = NULL;
    }
}

bool dataFileAppend(DataFile file, const DataReference data)
{
    return performDataIO(file, DataFileMode_append, data, NULL);
}

bool dataFileRead(DataFile file, DataReference output)
{
    return performDataIO(file, DataFileMode_read, NULL, output);
}

bool dataFileWrite(DataFile file, const DataReference data)
{
    return performDataIO(file, DataFileMode_write, data, NULL);
}

static bool performDataIO(DataFile file, DataFileMode mode, const DataReference input, DataReference output)
{
    if (!file.file || file.mode != mode)
    {
        return false;
    }

    bool operationResult = false;

    switch (mode)
    {
        case DataFileMode_read:
            if (!output)
            {
                Data data = {0};
                operationResult = readData(&data, file.file);
            }
            else
            {
                operationResult = readData(output, file.file);
            }
            break;

        case DataFileMode_append:
        case DataFileMode_write:
            operationResult = writeData(input, file.file);
            break;
            
        default:
            return false;
            break;
    }

    return operationResult;
}

static bool readData(DataReference output, FILE* file)
{
    size_t read = 0;
    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        read += fread(output->fields[i], sizeof(char), MAX_DATA_FIELD_SIZE, file);
    }
    // And the separator:
    if (fgetc(file) == EOF)
    {
        return false;
    }
    else
    {
        read++;
    }
    // Check if we have read a full struct:
    if (read != DATA_TOTAL_SIZE)
    {
        return false;
    }
    
    return true;
}

static bool writeData(const DataReference data, FILE* file)
{
    // A hack to possibly read files easier that might be useful later:
    const unsigned char separator = '\n';
    size_t written = 0;
    
    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        written += fwrite(data->fields[i], sizeof(char), MAX_DATA_FIELD_SIZE, file);
    }
    written += fwrite(&separator, sizeof(separator), 1, file);
    if (written != DATA_TOTAL_SIZE || ferror(file))
    {
        return false;
    }
    return true;
}