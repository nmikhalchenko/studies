#ifndef STUDENT_DATABASE_H
#define STUDENT_DATABASE_H

#include <stdbool.h>

#include "student.h"

#define MAX_STUDENTS (8)

int Students_Add(Student student);
bool Students_TryRemove(int index);
void Students_Print(void);
void Students_SortBy(StudentField field);

#endif // STUDENT_DATABASE_H