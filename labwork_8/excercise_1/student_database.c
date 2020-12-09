#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "student_database.h"

#define TOP_INVALID (-1)

typedef Student* StudentPointer;
typedef __compar_fn_t StudentComparer;
typedef int (*StudentSearcher)(const Student* left, const Student* right);

static int stringComparer(StudentFieldIndex field, const void* left, const void* right);
static int intComparer(StudentFieldIndex field, const void* left, const void* right);
static int stringSearcher(StudentFieldIndex field, const Student* left, const Student* right);
static int intSearcher(StudentFieldIndex field, const Student* left, const Student* right);

#define DEFINE_STRING_COMPARER(field)\
static int field##Comparer(const StudentPointer* left, const StudentPointer* right)\
{\
    return stringComparer(StudentFieldIndex_##field, left, right);\
}

#define DEFINE_INT_COMPARER(field)\
static int field##Comparer(const StudentPointer* left, const StudentPointer* right)\
{\
    return intComparer(StudentFieldIndex_##field, left, right);\
}

#define DEFINE_STRING_SEARCHER(field)\
static int field##Searcher(const Student* left, const Student* right)\
{\
    return stringSearcher(StudentFieldIndex_##field, left, right);\
}

#define DEFINE_INT_SEARCHER(field)\
static int field##Searcher(const Student* left, const Student* right)\
{\
    return intSearcher(StudentFieldIndex_##field, left, right);\
}

#define GET_COMPARER(field) (&field##Comparer)
#define GET_SEARCHER(field) (&field##Searcher)

typedef struct
{
    const char* name;
    StudentComparer comparer;
    StudentSearcher searcher;

} StudentFieldInfo;

DEFINE_STRING_COMPARER(firstName);
DEFINE_STRING_COMPARER(lastName);
DEFINE_STRING_COMPARER(fatherName);
DEFINE_STRING_COMPARER(homeAddress);
DEFINE_STRING_COMPARER(groupName);
DEFINE_INT_COMPARER(rating);

DEFINE_STRING_SEARCHER(firstName);
DEFINE_STRING_SEARCHER(lastName);
DEFINE_STRING_SEARCHER(fatherName);
DEFINE_STRING_SEARCHER(homeAddress);
DEFINE_STRING_SEARCHER(groupName);
DEFINE_INT_SEARCHER(rating);

static const StudentFieldInfo g_fieldInfoTable[MAX_STUDENT_FIELDS] =
{
    {"First name",      GET_COMPARER(firstName),   GET_SEARCHER(firstName)  },
    {"Last name",       GET_COMPARER(lastName),    GET_SEARCHER(lastName)   },  
    {"Patronymic",      GET_COMPARER(fatherName),  GET_SEARCHER(fatherName) },
    {"Home address",    GET_COMPARER(homeAddress), GET_SEARCHER(homeAddress)},
    {"Group",           GET_COMPARER(groupName),   GET_SEARCHER(groupName)  },
    {"Rating",          GET_COMPARER(rating),      GET_SEARCHER(rating)     }
};

static Student* g_students[MAX_STUDENTS] = {0};
static int g_top = 0;
static int g_count = 0;

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

static int resolveNullComparison(Student* left, Student* right)
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

static int stringComparer(StudentFieldIndex field, const void* left, const void* right)
{
    Student* l = *(Student**)left;
    Student* r = *(Student**)right;

    int comparison = 0;

    if (!l || !r)
    {
        comparison = resolveNullComparison(l, r);
        return comparison;
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

static int stringSearcher(StudentFieldIndex field, const Student* left, const Student* right)
{
    const Student* l = left;
    const Student* r = right;

    if (!r)
    {
        return 1;
    }

    const char* lf = l->fields[field];
    const char* rf = r->fields[field];

    if (strncmp(lf, rf, MAX_STUDENT_FIELD_SIZE) == 0)
    {
        return 0;
    }
    return 1;
}

static int intComparer(StudentFieldIndex field, const void* left, const void* right)
{
    Student* l = *(Student**)left;
    Student* r = *(Student**)right;

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

static int intSearcher(StudentFieldIndex field, const Student* left, const Student* right)
{
    const Student* l = left;
    const Student* r = right;

    if (!r)
    {
        return 1;
    }

    const char* lf = l->fields[field];
    const char* rf = r->fields[field];

    int lnum = atoi(lf);
    int rnum = atoi(rf);

    return lnum - rnum;
}

bool Students_TryAdd(const Student* student, int* resultingIndex)
{
    if (!student)
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
    g_students[index] = (Student*)malloc(sizeof(Student));

    for (int i = 0; i < MAX_STUDENT_FIELDS; i++)
    {
        Student* s = g_students[index];
        strncpy(s->fields[i], student->fields[i], MAX_STUDENT_FIELD_SIZE);
        if (i == StudentFieldIndex_rating)
        {
            if ((strtol(s->fields[i], NULL, 0) == 0) && (s->fields[i][0] != '0'))
            {
                strncpy(s->fields[i], "0", MAX_STUDENT_FIELD_SIZE);
            }
        }
    }

    tryAdvanceTop();

    if (resultingIndex)
    {
        *resultingIndex = index;
    }

    g_count++;
    return true;
}

bool Students_TryRemove(int index)
{
    if (!isIndexInRange(index))
    {
        return false;
    }

    int i = 0;
    int studentIndex = 0;

    while (i < MAX_STUDENTS)
    {
        Student* current = g_students[i];
        if (current)
        {
            if (studentIndex == index)
            {
                free(g_students[index]);
                g_students[index] = NULL;
                g_top = index;
                g_count--;
                return true;
            }

            studentIndex++;
        }

        i++;
    }

    return false;
}

bool Students_TryGetIndexByStudent(const Student* student, int* outputIndex)
{
    if (!student)
    {
        return false;
    }

    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        Student* ptr = g_students[i];
        if (!ptr)
        {
            continue;
        }
        if (g_students[i] == student)
        {
            *outputIndex = i;
            return true;
        }
    }

    return false;
}

bool Students_TrySearchByIndex(int index, Student** output)
{
    if (!isIndexInRange(index))
    {
        return false;
    }

    int loopCounter = 0;
    int studentNumber = 0;

    while (loopCounter < MAX_STUDENTS)
    {
        Student* current = g_students[loopCounter];
        if (current)
        {
            if (studentNumber == index)
            {
                if (output) *output = current;
                return true;
            }
            studentNumber++;
        }

        loopCounter++;
    }

    return false;
}

void Students_PrintStudent(const Student* student)
{
    if (!student) 
    {
        return;
    }

    puts("[");
    for (int j = 0; j < MAX_STUDENT_FIELDS; j++)
    {
        printf("  %-20s: \"%s\"\n", g_fieldInfoTable[j].name, student->fields[j]);
    }
    puts("]");
}

void Students_Print(void)
{
    for (int i = 0; i < MAX_STUDENTS; i++)
    {
        StudentPointer p = g_students[i];
        if (p)
        {
            printf (" %i. ", i + 1);
            Students_PrintStudent(p);
        }
    }
}

void Students_SortByField(StudentFieldIndex field)
{
    qsort(g_students, MAX_STUDENTS, sizeof(StudentPointer), g_fieldInfoTable[field].comparer);
}

int Students_SearchByField(StudentFieldIndex field, const char* key, int length, Student* outputArray, int* indexArray)
{
    if (!outputArray || !indexArray)
    {
        return -1;
    }

    Student dummy = {0};
    strncpy(dummy.fields[field], key, MAX_STUDENT_FIELD_SIZE);

    int out_i = 0;

    for (int i = 0; (i < MAX_STUDENTS) && (out_i < length); i++)
    {
        Student* cur = g_students[i];
        if (!cur)
        {
            continue;
        }
        int comparison = g_fieldInfoTable[field].searcher(&dummy, cur);
        if (comparison == 0)
        {
            outputArray[out_i] = *cur;
            indexArray[out_i] = i + 1;
            out_i++;
        }
    }
    printf("out_i: %i\n", out_i);
    return out_i;
}

char* Students_FieldNameToString(StudentFieldIndex field, bool toLower, int length, char* output)
{
    int buflen = strlen(g_fieldInfoTable[field].name) + 1;
    char buffer[buflen];
    strncpy(buffer, g_fieldInfoTable[field].name, buflen);
    buffer[buflen - 1] = '\0';
    if (toLower)
    {
        buffer[0] = (char)tolower(buffer[0]);
    }
    strncpy(output, buffer, length);
    return output;
}

int Students_GetCount(void)
{
    return g_count;
}