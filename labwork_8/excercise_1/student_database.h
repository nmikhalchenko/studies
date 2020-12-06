#ifndef STUDENT_DATABASE_H
#define STUDENT_DATABASE_H

#include <stdbool.h>

#include "student.h"

#define MAX_STUDENTS (8)

bool    Students_TryAdd                (Student student, int* resultingIndex);
bool    Students_TryRemove             (int index);
bool    Students_TryGetStudentByIndex  (int index, Student* output);
void    Students_PrintStudent          (const Student* student);
void    Students_Print                 (void);
void    Students_SortBy                (StudentField field);
bool    Students_TrySearchBy           (StudentField field, const char* key, Student* output);

#endif // STUDENT_DATABASE_H