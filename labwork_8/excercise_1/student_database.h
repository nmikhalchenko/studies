#ifndef STUDENT_DATABASE_H
#define STUDENT_DATABASE_H

#include <stdbool.h>

#include "student.h"

#define MAX_STUDENTS (128)

bool        Students_TryAdd                 (const Student* student, int* outputIndex);
bool        Students_TryRemove              (int index);
bool        Students_TryGetIndexByStudent   (const Student* student, int* outputIndex);
bool        Students_TrySearchByIndex       (int index, Student** output);
void        Students_PrintStudent           (const Student* student);
void        Students_Print                  (void);
void        Students_SortByField            (StudentFieldIndex field);
int         Students_SearchByField          (StudentFieldIndex field, const char* key, int length, Student* outputArray, int* indexArray);
char*       Students_FieldNameToString      (StudentFieldIndex field, bool toLower, int length, char* output);
int         Students_GetCount               (void);

#endif // STUDENT_DATABASE_H