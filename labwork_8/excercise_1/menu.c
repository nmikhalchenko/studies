#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shared_code/shared_code.h"

#include "student_database.h"
#include "menu.h"

#define INPUT_BUFFER_SIZE (64)

typedef enum
{
    Choice_Add,
    Choice_Print,
    Choice_Exit

} Choice;

typedef struct
{
    const char* name;
    void (*action)(void);

} MenuOption;

/*========================
    MENU OPTIONS
========================*/

static StudentFieldIndex requestFieldIndex(void);
static void printDivider(void);
static void printMenu(void);
static void requestStudent(Student* output);

void Add(void)
{
    Student s = {0};
    requestStudent(&s);
    Students_TryAdd(&s, NULL);
}

void Sort(void)
{
    StudentFieldIndex field = requestFieldIndex();

    Students_SortByField(field);
    puts("");
}

void Search(void)
{
    StudentFieldIndex field = requestFieldIndex();
    char buffer[INPUT_BUFFER_SIZE];
    requestString(sizeof(buffer), buffer, "Enter desired value: ");
    
    int outputLength = Students_GetCount();
    Student* outputStudents = (Student*)calloc(outputLength, sizeof(Student));
    int* outputIndices = (int*)calloc(outputLength, sizeof(int));

    int howManyFound = Students_SearchByField(field, buffer, outputLength, outputStudents, outputIndices);
    printf("howManyFound: %i\n", howManyFound);
    printDivider();
    if (howManyFound > 0)
    {
        for (int i = 0; i < howManyFound; i++)
        {
            printf (" %i. ", outputIndices[i]);
            Students_PrintStudent(&outputStudents[i]);
        }
    }
    else
    {
        puts("The search has yielded no result.");
    }
    printDivider();

    free(outputStudents);
    free(outputIndices);
}

void Change(void)
{
    int index = requestSize("Enter the student's index: ") - 1;
    printDivider();

    Student* s = NULL;
    bool found = Students_TrySearchByIndex(index, &s);
    if (!found)
    {
        puts("No student with such an index was found.");
        return;
    }

    StudentFieldIndex field = requestFieldIndex();

    char buffer[INPUT_BUFFER_SIZE];
    requestString(sizeof(buffer), buffer, "Enter desired value: ");
    strncpy(s->fields[field], buffer, MAX_STUDENT_FIELD_SIZE);
    puts("Field changed.");
}

void Remove(void)
{
    int index = requestSize("Enter the student's index: ") - 1;
    printDivider();

    bool removed = Students_TryRemove(index);
    if (!removed)
    {
        puts("No student with such an index was found.");
        return;
    }
    puts("Student removed.");
}

void Print(void)
{
    puts("");
    printDivider();
    Students_Print();
    printDivider();
}

/*========================
          MENU
========================*/

#define MAX_MENU_OPTIONS (6)

static const MenuOption menu[MAX_MENU_OPTIONS] =
{
    {"Add student",                 &Add    },
    {"Sort students by field",      &Sort   },
    {"Search students by field",    &Search },
    {"Change student by index",     &Change },
    {"Remove student by index",     &Remove },
    {"Print students",              &Print  }
};

/*========================
    TOOL FUNCTIONS
========================*/

static StudentFieldIndex requestFieldIndex(void)
{
    char buffer[INPUT_BUFFER_SIZE];

    printf("Available fields:\n");
    for (int i = 0; i < MAX_STUDENT_FIELDS; i++)
    {
        Students_FieldNameToString(i, false, sizeof(buffer), buffer);
        printf("    %i. \"%s\"\n", i + 1, buffer);
    }
    puts("");

    int choice = 0;
    printf("Enter field number: ");
    while (true)
    {
        bool result = tryRequestSize(NULL, &choice);
        if (result && choice <= MAX_STUDENT_FIELDS)
        {
            break;
        }
        else
        {
            printf("The choice is out of range.\n");
        }
    }

    return choice - 1;
}

static void printDivider(void)
{
    puts("----------------");   
}

static void printMenu(void)
{
    puts("");

    int i = 0;
    const char* format = "%i. %s\n";
    for (; i < MAX_MENU_OPTIONS; i++)
    {
        printf(format, i + 1, menu[i].name);
    }
    printf(format, i + 1, "Exit");
}

static void requestStudent(Student* output)
{
    if (!output)
    {
        return;
    }

    char buffer[INPUT_BUFFER_SIZE];

    for (int i = 0; i < MAX_STUDENT_FIELDS; i++)
    {
        printf("Enter the ");
        printf("%s: ", Students_FieldNameToString(i, true, sizeof(buffer), buffer));

        buffer[0] = '\0';
        while (strlen(buffer) < 1)
        {
            requestString(sizeof(buffer), buffer, NULL);
        }
        strncpy(output->fields[i], buffer, MAX_STUDENT_FIELD_SIZE);
    }
}

/* --------------------------------- */

void loop(void)
{
    bool exit = false;
    int choice = 0;
    bool inputSuccess = false;

    while (!exit)
    {
        printMenu();
        printf("Enter menu option: ");

        retryInput:

        inputSuccess = tryRequestSize(NULL, &choice);
        while (!inputSuccess)
        {
            goto retryInput;
        }
        if (choice == MAX_MENU_OPTIONS + 1)
        {
            exit = true;
        }
        else if ((choice < MAX_MENU_OPTIONS + 1) && choice > 0)
        {
            puts("");
            menu[choice - 1].action();
        }
        else
        {
            goto retryInput;
        }
    }
}