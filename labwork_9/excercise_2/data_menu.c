#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "data.h"
#include "data_menu.h"
#include "data_database.h"
#include "shared_code/shared_code.h"

#define DIVIDER_CHAR ('-')
#define DIVIDER_LENGTH (48)
#define MAX_MENU_COMMANDS (5)

typedef bool (*Operation)(void);

typedef struct
{
    const char* name;
    Operation operation;

} MenuOption;

static bool operationPrint(void);
static bool operationAdd(void);
static bool operationFind(void);
static bool operationClear(void);
static bool operationExit(void);

static const MenuOption g_menuCommands[MAX_MENU_COMMANDS] =
{
    { .name = "Print",      .operation = &operationPrint    },
    { .name = "Add",        .operation = &operationAdd      },
    { .name = "Find",       .operation = &operationFind     },
    { .name = "Clear",      .operation = &operationClear    },
    { .name = "Exit",       .operation = &operationExit     }
};

static bool g_exit = false;

static void menuLogic(void);
static int requestRangedInt(int min, int max, const char* nullableMsg);
static Data requestData(void);
static bool requestFieldValue(FieldName field, char* output, int length);
static FieldName requestFieldName(void);
static int requestMenuOption(void);
static void printFields(void);
static void printNamedDivider(const char* name);
static void printDivider(void);
static void printMenu(void);

void startMenu(void)
{
    if (!dataBaseIsInit())
    {
        dataBaseInit();
    }

    while (!g_exit)
    {
        menuLogic();
    }

    puts("EXITING...");
    dataBaseUninit();
}

static bool operationPrint(void)
{
    puts("");
    printNamedDivider("DATABASE ENTRIES");
    dataBasePrint();
    return true;
}

static bool operationAdd(void)
{
    Data data = dataBlank();
    data = requestData();

    bool result = dataBaseAdd(&data);
    if (!result)
    {
        puts("Failed to add entry to the data base.");
    }

    return result;
}

static bool operationFind(void)
{
    puts("");
    printNamedDivider("FIELDS TO SEARCH BY");
    printFields();
    puts("");
    FieldName field = requestFieldName();
    puts("");

    char buffer[MAX_DATA_FIELD_SIZE];
    requestFieldValue(field, buffer, MAX_DATA_FIELD_SIZE);
    puts("");

    printDivider();
    int count = dataBaseFindAndPrint(field, buffer);
    if (count <= 0)
    {
        puts("The search has yielded no results.");
    }
    else
    {
        printf("Yielded %i result(s).\n", count);
    }

    return true;
}

static bool operationClear(void)
{
    char buffer[32];
    if (!requestString(sizeof(buffer), buffer, "Are you sure you want to clear the database? (Y/N)\n") ||
        strlen(buffer) < 1)
    {
        puts("Invalid input.");
        return false;
    }
    
    if (tolower(buffer[0]) == 'y')
    {
        puts("Clearing...");
        dataBaseClear();
    }

    return true;
}

static bool operationExit(void)
{
    g_exit = true;
    return true;
}

static void menuLogic(void)
{
    printMenu();
    int option = requestMenuOption();

    bool result = g_menuCommands[option].operation();
    if (!result)
    {
        printf("The command has finished with failure.\n\n");
    }
    return;
}

static int requestRangedInt(int min, int max, const char* nullableMsg)
{
    int input = 0;
    bool valid = false;
    while (!valid)
    {
        input = requestInt(nullableMsg);
        valid = (input >= min && input <= max);
        if (!valid)
        {
            puts("The input is out of range. Try again.");
        }
    }
    return input;
}

static Data requestData(void)
{
    Data data = dataBlank();

    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        char buffer[MAX_DATA_FIELD_SIZE];
        requestFieldValue(i, buffer, sizeof(buffer));
        dataSetField(&data, i, buffer);
    }

    return data;
}

static bool requestFieldValue(FieldName field, char* output, int length)
{
    if (output)
    {
        if (length < MAX_DATA_FIELD_SIZE)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    Data data = dataBlank();    
    bool valid = false;
    char buffer[MAX_DATA_FIELD_SIZE];

    while (!valid)
    {
        printf("Enter \'%s\': ", g_fieldInfoTable[field].name);
        if (!requestString(MAX_DATA_FIELD_SIZE, buffer, NULL))
        {
            puts("Malformed string. Try again.");
            continue;
        }
        if (!dataSetField(&data, field, buffer))
        {
            puts("Invalid value. Try again.");
            continue;
        }
        valid = true;
    }

    if (output)
    {
        snprintf(output, MAX_DATA_FIELD_SIZE, "%s", buffer);
    }

    return true;
}

static FieldName requestFieldName(void)
{
    int field = requestRangedInt(1, MAX_DATA_FIELDS, "Enter field number: ");
    return field - 1;
}

static int requestMenuOption(void)
{
    int input = requestRangedInt(1, MAX_MENU_COMMANDS, "Enter menu option number: ");
    return input - 1;
}

static void printFields(void)
{
    for (int i = 0; i < MAX_DATA_FIELDS; i++)
    {
        printf("%i. %s\n", i + 1, g_fieldInfoTable[i].name);
    }
}

static void printNamedDivider(const char* name)
{
    int namelen = name == NULL ? 0 : strlen(name);
    int threshold = name == NULL ? 0 : DIVIDER_LENGTH / 2 - namelen / 2;

    int count = threshold > 0 ? threshold : DIVIDER_LENGTH;
    
    for (int i = 0; i < count; i++)
    {
        printf("%c", DIVIDER_CHAR);
    }

    if (name)
    {
        printf("%s", name);
        for (int i = 0; i < count; i++)
        {
            printf("%c", DIVIDER_CHAR);
        }
    }
    
    puts(""); 
}

static void printDivider(void)
{
    printNamedDivider(NULL);
}

static void printMenu(void)
{
    printNamedDivider("MENU");

    for (int i = 0; i < MAX_MENU_COMMANDS; i++)
    {
        printf("%i. %s\n", i + 1, g_menuCommands[i].name);
    }

    printDivider();
}