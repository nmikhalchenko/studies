#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "data.h"
#include "utils.h"

static bool checkValue(const char* value, FieldType type);
static bool intValidator(const char* value);
static bool stringValidator(const char* value);

const TypeInfo g_typeInfoTable[MAX_DATA_TYPES] =
{
    {   .validator = &intValidator,     .defaultValue = "0",    .formatSpecifier = "%li" },
    {   .validator = &stringValidator,  .defaultValue = "None", .formatSpecifier = "%s"  }
};

const FieldInfo g_fieldInfoTable[MAX_DATA_FIELDS] =
{
    {   .name = "Full Name",            .type = FieldType_string    },
    {   .name = "Library Card Number",  .type = FieldType_int       },
    {   .name = "Book Name",            .type = FieldType_string    },
    {   .name = "Return Term",          .type = FieldType_string    }
};

bool dataSetField(DataPointer data, FieldName field, const char* value)
{
    if (!value)
    {
        return false;
    }

    FieldType type = g_fieldInfoTable[field].type;
    bool valid = checkValue(value, type);
    const char* writtenValue = valid ? value : g_typeInfoTable[type].defaultValue;
    
    snprintf(data->fields[field], MAX_DATA_FIELD_SIZE, "%s", writtenValue);
    
    return valid;
}

const char* dataGetField(const DataPointer data, FieldName field)
{
    
    return data->fields[field];
}

void dataPrint(const DataPointer data, int padding)
{
    padding = padding > 999 ? 999 : padding;

    char buffer[6];
    char format[12];

    bool result = tryPadFormatSpecifier("%s", padding, buffer, sizeof(buffer));
    snprintf(format, sizeof(format), "%s: %%s\n", buffer);
    
    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        printf(format, g_fieldInfoTable[i].name, dataGetField(data, i));
    }
}

/*========================

    STATIC FUNCTIONS

========================*/

static bool checkValue(const char* value, FieldType type)
{
    return g_typeInfoTable[type].validator(value);
}

static bool intValidator(const char* value)
{
    if (!value)
    {
        return false;
    }

    char* endptr = NULL;

    long parsed = strtol(value, &endptr, 0);
    if (parsed == 0)
    {
        if ((endptr && endptr == value) || errno == ERANGE)
        {
            return false;
        }
    }

    return true;
}

static bool stringValidator(const char* value)
{
    if (!value)
    {
        return false;
    }

    return true;
}