#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "student_database.h"

#define TOP_INVALID (-1)

typedef Student* StudentPointer;
typedef __compar_fn_t StudentComparer;

static int stringComparer(StudentField field, const void* left, const void* right);
static int intComparer(StudentField field, const void* left, const void* right);

#define DEFINE_STRING_COMPARER(field)\
static int field##Comparer(const StudentPointer* left, const StudentPointer* right)\
{\
    return stringComparer(StudentField_##field, left, right);\
}

#define DEFINE_INT_COMPARER(field)\
static int field##Comparer(const StudentPointer* left, const StudentPointer* right)\
{\
    return intComparer(StudentField_##field, left, right);\
}

#define GET_COMPARER(field) (&field##Comparer)

typedef struct
{
    const char* name;
    StudentComparer comparer;

} StudentFieldInfo;

DEFINE_STRING_COMPARER(firstName);
DEFINE_STRING_COMPARER(lastName);
DEFINE_STRING_COMPARER(fatherName);
DEFINE_STRING_COMPARER(groupName);
DEFINE_INT_COMPARER(rating);

static const StudentFieldInfo g_fieldInfoTable[MAX_STUDENT_FIELDS] =
{
    {"First name",      GET_COMPARER(firstName)},
    {"Last name",       GET_COMPARER(lastName)},
    {"Patronymic",      GET_COMPARER(fatherName)},
    {"Group",           GET_COMPARER(groupName)},
    {"Rating",          GET_COMPARER(rating)}
};

static StudentPointer g_students[MAX_STUDENTS] = {0};
static int g_top = 0;

static bool isTopValid(void)
{
    return g_top != TOP_INVALID;
}

static bool tryAdvanceTop(void)
{
    int failsafe = 0;

    while (g_students[g_top])
    {
        failsafe++;
        g_top++;

        if (failsafe >= MAX_STUDENTS)
        {
            return false;
            g_top = TOP_INVALID;
        }

        if (g_top >= MAX_STUDENTS)
        {
            g_top -= MAX_STUDENTS;
        }
    }

    return true;
}

static bool isIndexInRange(int index)
{
    return (index < MAX_STUDENTS) && (index >= 0);
}

static int resolveNullComparison(StudentPointer left, StudentPointer right)
{
    if (!left && !right) 
    {
        return 0;
    }
    else if (!left) 
    {
        return -1;
    }
    else 
        return 1;   
}

static int stringComparer(StudentField field, const void* left, const void* right)
{
    StudentPointer l = *(StudentPointer*)left;
    StudentPointer r = *(StudentPointer*)right;

    if (!l || !r)
    {
        return resolveNullComparison(l, r);
    }

    const char* lf = l->fields[field];
    const char* rf = r->fields[field];

    int ll = strlen(lf);
    int rl = strlen(rf);
    int len = rl < ll ? rl : ll;

    for (int i = 0; i < len; i++)
    {
        int dif = (int)(lf[i] - rf[i]);
        if (dif != 0)
        {
            return dif;
        }
    }

    return 0;
}

static int intComparer(StudentField field, const void* left, const void* right)
{
    StudentPointer l = *(StudentPointer*)left;
    StudentPointer r = *(StudentPointer*)right;

    if (!l || !r)
    {
        return resolveNullComparison(l, r);
    }

    const char* lf = l->fields[field];
    const char* rf = r->fields[field];

    int lnum = atoi(lf);
    int rnum = atoi(rf);

    return lnum - rnum;
}

bool Students_TryAdd(Student student, int* resultingIndex)
{
    if (!resultingIndex)
    {
        return false;
    }

    if (!isTopValid())
    {
        if (!tryAdvanceTop())
        {
            return false;
        }
    }

    int index = g_top;
    g_students[index] = (StudentPointer)malloc(sizeof(Student));
    memcpy(g_students[index], &student, sizeof(Student));

    tryAdvanceTop();

    *resultingIndex = index;
    return true;
}

bool Students_TryRemove(int index)
{
    if (!isIndexInRange(index) || !g_students[index])
    {
        return false;
    }

    free(g_students[index]);
    g_students[index] = NULL;
    g_top = index;
    return true;
}

bool Students_TryGetStudentByIndex(int index, Student* output)
{
    if (!isIndexInRange(index) || !g_students[index] || !output)
    {
        return false;
    }

    *output = *(g_students[index]);
    return true;
}

void Students_PrintStudent(const Student* student)
{
    if (!student) 
    {
        return;
    }

    for (int j = 0; j < MAX_STUDENT_FIELDS; j++)
    {
        printf("  %-20s: \"%s\"\n", g_fieldInfoTable[j].name, student->fields[j]);
    }
    puts("");
}

void Students_Print(void)
{
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        StudentPointer p = g_students[i];
        Students_PrintStudent(p);
    }
}

void Students_SortBy(StudentField field)
{
    qsort(g_students, MAX_STUDENTS, sizeof(StudentPointer), g_fieldInfoTable[field].comparer);
}

bool Students_TrySearchBy(StudentField field, const char* key, Student* output)
{
    if (!output)
    {
        return false;
    }

    Student dummy = {0};
    dummy.fields[field] = key;
    StudentPointer result =
        (StudentPointer)bsearch(&dummy, g_students, MAX_STUDENTS, sizeof(StudentPointer), g_fieldInfoTable[field].comparer);

    if (!result)
    {
        return false;
    }
    
    *output = *result;
    return true;
}