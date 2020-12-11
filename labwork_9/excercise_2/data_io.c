#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "data_io.h"

#define DATA_FILE_NAME ("datafile")

typedef enum
{
    FileOpenMode_closed,
    FileOpenMode_read,
    FileOpenMode_write

} FileOpenMode;

typedef struct
{
    FILE* file;
    FileOpenMode currentMode;

} DataFile;

static DataFile g_dataFile =
{
    .file = NULL,
    .currentMode = FileOpenMode_closed
};

static void reopenForRead(void);
static void reopenForWrite(void);

static bool writeData(FILE* file, const DataPointer data);
static bool readData(FILE* file, DataPointer data, int length);

static void reopenForRead(void)
{
    if (g_dataFile.currentMode == FileOpenMode_read)
    {
        return;
    }

    g_dataFile.file = fopen(DATA_FILE_NAME, "r");
    g_dataFile.currentMode = FileOpenMode_read;
}

static void reopenForWrite(void)
{
    if (g_dataFile.currentMode == FileOpenMode_write)
    {
        return;
    }

    g_dataFile.file = fopen(DATA_FILE_NAME, "a");
    g_dataFile.currentMode = FileOpenMode_write;
}

static bool writeData(FILE* file, const DataPointer data)
{
    if (!file || !data)
    {
        return false;
    }

    // A hack to possibly read files easier that might be useful later:
    const unsigned char separator = '\n';

    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        fwrite(data->fields[i], sizeof(char), MAX_DATA_FIELD_SIZE, file);
        if (feof(file))
        {
            break;
        }
    }

    fwrite(&separator, sizeof(separator), 1, file);

    return true;
}

static bool readData(FILE* file, DataPointer data, int length)
{
    if (!file || !data || length < 1)
    {
        return false;
    }

    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        void* ptr = data->fields[i];
        fread(ptr, sizeof(char), MAX_DATA_FIELD_SIZE, file);
        if (feof(file))
        {
            break;
        }
    }

    // To eat the separator:
    fgetc(file);

    return true;
}