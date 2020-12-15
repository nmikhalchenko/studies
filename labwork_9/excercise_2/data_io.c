#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#include "data_io.h"

#define DATA_TOTAL_SIZE (MAX_DATA_FIELD_SIZE * MAX_DATA_FIELDS + 1)

struct DataFile
{
    FILE* file;
    DataFileMode mode;

};

static const char* const g_dataIOModeStrings[MAX_DATA_IO_MODES] =
{
    "a",
    "r",
    "w"
};

static bool isDataFileValid(const struct DataFile* file);
static bool performDataIO(const struct DataFile* file, DataFileMode mode, const Data* input, Data* output);
static bool readData(Data* output, FILE* file);
static bool writeData(const Data* data, FILE* file);

struct DataFile* dataFileOpen(const char* filename, DataFileMode mode)
{
    const char* openmode = g_dataIOModeStrings[mode];
    FILE* file = fopen(filename, openmode);
    if (!file)
    {
        return NULL;
    }

    struct DataFile* dataFile = (struct DataFile*)malloc(sizeof(struct DataFile));
    dataFile->file = file;
    dataFile->mode = mode;
    
    return dataFile;
}

bool dataFileReopen(const char* filename, DataFileMode mode, DataFile* file)
{
    if (!isDataFileValid(file))
    {
        return false;
    }

    FILE* newFile = fopen(filename, g_dataIOModeStrings[mode]);
    if (!newFile)
    {
        return false;
    }

    fclose(file->file);
    file->file = newFile;
    file->mode = mode;

    return true;
}

void dataFileClose(DataFile* file)
{
    if (isDataFileValid(file))
    {
        fclose(file->file);
        free(file);
        file->file = NULL;
    }
}

int dataFileCount(const DataFile* file)
{
    if (!isDataFileValid(file) || file->mode != DataFileMode_read)
    {
        return -1;
    }

    FILE* f = file->file;
    int count = 0;
    bool error = false;
    bool eof = false;

    fseek(f, 0, SEEK_SET);

    int seekResult = 0;
    while ((seekResult = fseek(f, DATA_TOTAL_SIZE - 1, SEEK_CUR)) >= 0 && !error && !eof)
    {
        printf("seekResult: %i\n", seekResult);
        int c = fgetc(f);
        switch (c)
        {
            case '\n':
                puts("newline!");
                count++;
                break;
            
            case EOF:
                eof = true;
                break;

            default:
                error = true;
                break;
        }
    }
    if (error)
    {
        return -1;
    }
    
    return count;
}

bool dataFileGoto(const DataFile* file, int index)
{
    if (!isDataFileValid(file))
    {
        return false;
    }

    rewind(file->file);

    int count = dataFileCount(file);
    if (index >= count)
    {
        return false;
    }

    for (int i = 0; i < count; i++)
    {
        bool readResult = dataFileRead(file, NULL);
        if (!readResult)
        {
            break;
        }
    }

    return true;
}

bool dataFileAppend(const DataFile* file, const Data* data)
{
    return performDataIO(file, DataFileMode_append, data, NULL);
}

bool dataFileRead(const DataFile* file, Data* output)
{
    return performDataIO(file, DataFileMode_read, NULL, output);
}

bool dataFileWrite(const DataFile* file, const Data* data)
{
    return performDataIO(file, DataFileMode_write, data, NULL);
}

static bool isDataFileValid(const DataFile* file)
{
    return file && file->file;
}

static bool performDataIO(const DataFile* file, DataFileMode mode, const Data* input, Data* output)
{
    if (!isDataFileValid(file) || file->mode != mode)
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
                operationResult = readData(&data, file->file);
            }
            else
            {
                operationResult = readData(output, file->file);
            }
            break;

        case DataFileMode_append:
        case DataFileMode_write:
            operationResult = writeData(input, file->file);
            break;
            
        default:
            return false;
            break;
    }

    return operationResult;
}

static bool readData(Data* output, FILE* file)
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

static bool writeData(const Data* data, FILE* file)
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