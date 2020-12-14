#ifndef DATA_H
#define DATA_H

#include <stdbool.h>

#define MAX_DATA_TYPES (2)
#define MAX_DATA_FIELDS (4)
#define MAX_DATA_FIELD_SIZE (64)

typedef char Field[MAX_DATA_FIELD_SIZE];

typedef struct 
{
    Field fields[MAX_DATA_FIELDS];

} Data;

typedef Data* DataReference;

typedef bool (*TypeValidator)(const char* value);

typedef enum
{
    FieldType_int,
    FieldType_string,

} FieldType;

typedef struct
{
    TypeValidator validator;
    const char* defaultValue;
    const char* formatSpecifier;

} TypeInfo;

typedef enum
{
    FieldName_fullName,
    FieldName_libCardNumber,
    FieldName_bookName,
    FieldName_returnTerm

} FieldName;

typedef struct
{
    const char* name;
    FieldType type;

} FieldInfo;

extern const TypeInfo g_typeInfoTable[MAX_DATA_TYPES];
extern const FieldInfo g_fieldInfoTable[MAX_DATA_FIELDS];

// These must ALWAYS be used for reading and writing to fields.
bool dataSetField(DataReference data, FieldName field, const char* value);
const char* dataGetField(const DataReference data, FieldName field);
void dataPrint(const DataReference data, int padding);

#endif // DATA_H