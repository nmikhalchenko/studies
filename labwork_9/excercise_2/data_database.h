#ifndef DATA_DATABASE_H
#define DATA_DATABASE_H

#include <stdbool.h>

#include "data.h"

void dataBaseInit(void);
void dataBaseUninit(void);
bool dataBaseIsInit(void);
bool dataBaseAdd(const Data* data);
void dataBasePrint(void);
int dataBaseFindAndPrint(FieldName field, const char* value);
void dataBaseClear(void);

#endif // DATA_DATABASE_H