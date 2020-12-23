#include <stdbool.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#include "data_database.h"
#include "data_io.h"
#include "utils.h"

/* This is where the design gets worse.

The decision to make a set of static functions
and then either forward them or use them
as utilities has proven to be a mess. 

I could try rewriting it yet again but I can't
be bothered - at this point I've spent way
too much time on it already. */

#define DATABASE_FILENAME ("datafile")
#define DATABASE_PADDING (30)
#define MAX_ENTRIES (256)

struct
{
    bool init;
    DataFile* file;

} g_dataBaseState =
{
    .init = false,
    .file = NULL
};

static void dbInit(void);
static void dbUninit(void);
static void dbClear(void);
static bool dbIsInit(void);
static bool dbIsFileOpen(void);
static DataFileMode dbGetFileMode(void);
static bool dbSetFileMode(DataFileMode mode);
static bool dbAdd(const Data* data);
static bool dbGetNth(int number, Data* output);
static void dbPrint(void);
static int dbFind(FieldName field, const char* value, Data* outputArray, int length);

void dataBaseInit(void)
{
    dbInit();
}

void dataBaseUninit(void)
{
    dbUninit();
}

bool dataBaseIsInit(void)
{
    return dbIsInit();
}

bool dataBaseAdd(const Data* data)
{
    return dbAdd(data);
}

void dataBasePrint(void)
{
    dbPrint();
}

int dataBaseFindAndPrint(FieldName field, const char* value)
{
    Data* data = (Data*)calloc(MAX_ENTRIES, sizeof(Data));
    int count = dbFind(field, value, data, MAX_ENTRIES);
    if (count > 0)
    {
        puts("");
        for (int i = 0; i < count; i++)
        {
            dataPrint(&data[i], DATABASE_PADDING);
        }
        puts("");
    }

    free(data);
    return count;
}

void dataBaseClear(void)
{
    dbClear();
}

static void dbInit(void)
{
    g_dataBaseState.file = dataFileOpen(DATABASE_FILENAME, DataFileMode_append);
    
    g_dataBaseState.init = true;
}

static void dbUninit(void)
{
    dataFileClose(g_dataBaseState.file);
    g_dataBaseState.file = NULL;

    g_dataBaseState.init = false;
}

static void dbClear(void)
{
    dbSetFileMode(DataFileMode_write);
}

static bool dbIsInit(void)
{
    return g_dataBaseState.init;
}

static bool dbIsFileOpen(void)
{
    return g_dataBaseState.file != NULL;
}

static DataFileMode dbGetFileMode(void)
{
    return dataFileGetMode(g_dataBaseState.file);
}

static bool dbSetFileMode(DataFileMode mode)
{
    dataFileRewind(g_dataBaseState.file);

    return dataFileReopen(DATABASE_FILENAME, mode, g_dataBaseState.file);
}

static bool dbAdd(const Data* data)
{
    dbSetFileMode(DataFileMode_append);
    return dataFileAppend(g_dataBaseState.file, data);
}

static bool dbGetNth(int number, Data* output)
{
    dbSetFileMode(DataFileMode_read);
    bool found = dataFileGoto(g_dataBaseState.file, number);

    if (found)
    {
        if (!output) 
        {
            output = NULL;
        }
        bool readResult = dataFileRead(g_dataBaseState.file, output);
        return readResult;
    }

    return false;
}

static void dbPrint(void)
{
    dbSetFileMode(DataFileMode_read);

    Data data = dataBlank();
    while (dataFileRead(g_dataBaseState.file, &data))
    {
        dataPrint(&data, DATABASE_PADDING);
        puts("");
    }
}

static int dbFind(FieldName field, const char* value, Data* outputArray, int length)
{
    dbSetFileMode(DataFileMode_read);

    bool hasOutput = (outputArray != NULL);
    if (hasOutput)
    {
        if (length < 0)
        {
            return 0;
        }
    }
    
    int count = 0;

    Data sample = dataBlank();
    dataSetField(&sample, field, value);

    Data data = dataBlank();
    while (dataFileRead(g_dataBaseState.file, &data))
    {
        if (dataEqualsField(&data, &sample, field))
        {
            if (hasOutput)
            {
                dataCopy(&outputArray[count], &data);
            }
            count++;
        }
    }

    return count;
}