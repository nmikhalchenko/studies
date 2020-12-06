#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "shared_code/shared_code.h"

#include "student_database.h"
#include "menu.h"

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
    char buffer[64];
    requestString(sizeof(buffer), buffer, "Enter desired value: ");
    
    int outputLength = Students_GetCount();
    Student* outputStudents = (Student*)calloc(outputLength, sizeof(Student));
    int* outputIndices = (int*)calloc(outputLength, sizeof(int));

    int howManyFound = Students_SearchByField(field, buffer, outputLength, outputStudents, outputIndices);
    printf("howManyFound: %i\n", howManyFound);
    puts("----------------");
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
    puts("----------------");

    free(outputStudents);
    free(outputIndices);
}

void Change(void)
{
    

}

void Remove(void)
{

}

void Print(void)
{
    puts("");
    puts("----------------");
    Students_Print();
    puts("----------------");
}

/*========================
          MENU
========================*/

#define MAX_MENU_OPTIONS (4)

static const MenuOption menu[MAX_MENU_OPTIONS] =
{
    {"Add student",                 &Add    },
    {"Sort students by field",      &Sort   },
    {"Search students by field",    &Search },
    {"Print students",              &Print  }
};

/*========================
    TOOL FUNCTIONS
========================*/

static StudentFieldIndex requestFieldIndex(void)
{
    char buffer[64];

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

static void printMenu(void)
{
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

    char stringBuffer[64];

    for (int i = 0; i < MAX_STUDENT_FIELDS; i++)
    {
        printf("Enter the ");
        printf("%s: ", Students_FieldNameToString(i, true, sizeof(stringBuffer), stringBuffer));

        stringBuffer[0] = '\0';
        while (strlen(stringBuffer) < 1)
        {
            requestString(sizeof(stringBuffer), stringBuffer, NULL);
        }
        strncpy(output->fields[i], stringBuffer, MAX_STUDENT_FIELD_SIZE);
    }
}

/* --------------------------------- */

void loop(void)
{
    bool exit = false;
    int choice = 0;
    bool requestSizeResult = false;

    while (!exit)
    {
        printMenu();
        printf("Enter menu option: ");

        retryInput:

        requestSizeResult = tryRequestSize(NULL, &choice);
        while (!requestSizeResult)
        {
            goto retryInput;
        }
        if (choice == MAX_MENU_OPTIONS + 1)
        {
            exit = true;
        }
        else if ((choice < MAX_MENU_OPTIONS + 1) && choice > 0)
        {
            menu[choice - 1].action();
        }
        else
        {
            goto retryInput;
        }
    }
}