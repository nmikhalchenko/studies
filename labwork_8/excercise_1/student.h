#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENT_FIELDS (6)
#define MAX_STUDENT_FIELD_SIZE (32)

typedef enum
{
    StudentFieldIndex_firstName,
    StudentFieldIndex_lastName,
    StudentFieldIndex_fatherName,
    StudentFieldIndex_homeAddress,
    StudentFieldIndex_groupName,
    StudentFieldIndex_rating

} StudentFieldIndex;

typedef char (StudentField)[MAX_STUDENT_FIELD_SIZE];

typedef struct
{
    StudentField fields[MAX_STUDENT_FIELDS];

} Student;

#endif // STUDENT_H
