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
Data dataBlank(void);
bool dataSetField(Data* data, FieldName field, const char* value);
bool dataSetFieldToDefault(Data* data, FieldName field);
const char* dataGetField(const Data* data, FieldName field);
bool dataEqualsField(const Data* left, const Data* right, FieldName field);
bool dataEquals(const Data* left, const Data* right);
bool dataCopy(Data* dest, Data* src);
void dataPrint(const Data* data, int padding);

#endif // DATA_H