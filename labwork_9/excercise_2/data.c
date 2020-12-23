#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "data.h"
#include "utils.h"

#define MAX_PADDING (300)

static bool isValidFieldValue(const char* value, FieldType type);
static bool intValidator(const char* value);
static bool stringValidator(const char* value);

const TypeInfo g_typeInfoTable[MAX_DATA_TYPES] =
{
    {   .validator = &intValidator,     .defaultValue = "0"     },
    {   .validator = &stringValidator,  .defaultValue = "None"  }
};

const FieldInfo g_fieldInfoTable[MAX_DATA_FIELDS] =
{
    {   .name = "Full Name",            .type = FieldType_string    },
    {   .name = "Library Card Number",  .type = FieldType_int       },
    {   .name = "Book Name",            .type = FieldType_string    },
    {   .name = "Return Term",          .type = FieldType_string    }
};

Data dataBlank(void)
{
    Data blank;

    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        FieldType type = g_fieldInfoTable[i].type;
        const char* defaultValue = g_typeInfoTable[type].defaultValue;
        dataSetField(&blank, i, defaultValue);
    }

    return blank;
}

bool dataSetField(Data* data, FieldName field, const char* value)
{
    if (!value)
    {
        return false;
    }

    FieldType type = g_fieldInfoTable[field].type;
    bool valid = isValidFieldValue(value, type);
    if (!valid)
    {
        return false;
    }

    snprintf(data->fields[field], MAX_DATA_FIELD_SIZE, "%s", value);
    
    return true;
}

bool dataSetFieldToDefault(Data* data, FieldName field)
{
    FieldType type = g_fieldInfoTable[field].type;
    const char* defaultValue = g_typeInfoTable[type].defaultValue;
    return dataSetField(data, field, defaultValue);
}

const char* dataGetField(const Data* data, FieldName field)
{   
    if (!data)
    {
        return NULL;
    }

    return data->fields[field];
}

bool dataEqualsField(const Data* left, const Data* right, FieldName field)
{
    if (!left || !right)
    {
        return false;
    }

    const char* l = dataGetField(left, field);
    const char* r = dataGetField(right, field);

    int llen = strlen(l);
    int rlen = strlen(r);
    if (llen != rlen)
    {
        return false;
    }
    
    int n = llen;

    bool equal = (strncmp(l, r, n) == 0);

    return equal;
}

bool dataEquals(const Data* left, const Data* right)
{
    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        if (!dataEqualsField(left, right, i))
        {
            return false;
        }
    }

    return true;
}

bool dataCopy(Data* dest, Data* src)
{
    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        const char* field = dataGetField(src, i);
        if (!field) return false;

        bool isSet = dataSetField(dest, i, field);
        if (!isSet) return false;
    }

    return true;
}

void dataPrint(const Data* data, int padding)
{
    padding = abs(padding);
    padding = padding > MAX_PADDING ? -MAX_PADDING : -padding;

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

static bool isValidFieldValue(const char* value, FieldType type)
{
    if (!value || strlen(value) < 1)
    {
        return false;
    }

    return g_typeInfoTable[type].validator(value);
}

/*========================

    TYPE VALIDATORS

========================*/

static bool intValidator(const char* value)
{
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
    return true;
}