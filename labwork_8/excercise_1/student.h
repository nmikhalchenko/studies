#ifndef STUDENT_H
#define STUDENT_H

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
    const char* fields[MAX_STUDENT_FIELDS];

} Student;

#endif // STUDENT_H
