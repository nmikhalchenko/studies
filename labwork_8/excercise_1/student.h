#ifndef STUDENT_H
#define STUDENT_H

typedef const char* NullTerminatedString;

#define MAX_STUDENT_FIELDS (5)

typedef enum
{
    StudentField_firstName,
    StudentField_lastName,
    StudentField_fatherName,
    StudentField_groupName,
    StudentField_rating

} StudentField;

typedef struct
{
    //NullTerminatedString keys[MAX_STUDENT_FIELDS];
    NullTerminatedString fields[MAX_STUDENT_FIELDS];

} Student;

#endif // STUDENT_H
