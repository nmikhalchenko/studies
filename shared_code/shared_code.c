#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "shared_code.h"

/*============ TODO ===========================
    
    1.  Need to improve security:
        add null checks on generic
        functions and maybe
        somewhere else.

    2.  requestString() is still wonky
        and needs fixing.

    3.  Tabbed printers are unused for now.
        Need to make use of them.

=============================================*/

#define DEFINE_PRINTERS(_typename)\
void _UntabbedPrinter_##_typename(NumType _type, void* value)\
{\
    printf(NumberInfoTable[_type].formatSpecifier, *(_typename*)value);\
}\
void _TabbedPrinter_##_typename(NumType _type, void* value)\
{\
    printf(NumberInfoTable[_type].formatSpecifierTabbed, *(_typename*)value);\
}

#define GET_PRINTER_UNTABBED(_typename) (&_UntabbedPrinter_##_typename)
#define GET_PRINTER_TABBED(_typename) (&_TabbedPrinter_##_typename)

typedef enum
{
    NumType_Unknown,
    NumType_Double,
    NumType_Float,
    NumType_Int

} NumType;

typedef void (*Printer)(NumType type, void* value);

typedef struct
{
    int size;
    const char* formatSpecifier;
    const char* formatSpecifierTabbed;
    Printer untabbedPrinter;
    Printer tabbedPrinter;

} NumInfo;

static NumInfo const NumberInfoTable[];

/*====================
  Definitions of
  functions that print
  values of various
  types
====================*/
DEFINE_PRINTERS(double);
DEFINE_PRINTERS(float);
DEFINE_PRINTERS(int);
/*==================*/

/*====================
  Number type info
  used by generic funcs
====================*/
static NumInfo const NumberInfoTable[] =
{
    [NumType_Unknown]   = { 0,                  NULL,   NULL,       NULL,                           NULL                        },
    [NumType_Double]    = { sizeof(double),     "%lg",  "%-20lg",   GET_PRINTER_UNTABBED(double),   GET_PRINTER_TABBED(double)  },
    [NumType_Float]     = { sizeof(float),      "%g",   "%-20g",    GET_PRINTER_UNTABBED(float),    GET_PRINTER_TABBED(float)   },
    [NumType_Int]       = { sizeof(int),        "%i",   "%-10i",    GET_PRINTER_UNTABBED(int),      GET_PRINTER_TABBED(int)     },
};

/*====================
   Tool functions
====================*/
static void*    getArrayElem            (NumType type, int length, void* array, int index);
static void*    getMatrixElem           (NumType type, int rows, int cols, void* matrix, int row, int col);
static void*    getMatrixRow            (NumType type, int rows, int cols, void* matrix, int row);
static void     assignNumber            (NumType type, void* left, void* right);
static void     requestNumber           (NumType type, void* output, const char* nullableMsg, ...);
static void     requestArray            (NumType type, int length, void* array, bool showElemMsgs, bool isMatrixRow, const char* nullableMsg, ...);
static void     requestMatrix           (NumType type, int rows, int cols, void* matrix, bool showElemMsgs, const char* nullableMsg, ...);
static void     printNumber             (NumType type, void* value, bool newline);
static void     printArray              (NumType type, int length, void* array, bool newline);
static void     printMatrix             (NumType type, int rows, int cols, void* matrix, bool newline);
static void     printNullableOrDefault  (const char* nullableMsg, const char* defaultMsg);
static void     printNullable           (const char* nullableMsg);
static void     vprintNullable          (const char* nullableMsg, va_list* params);

/*====================
     Interface,
     for use in
     other code
====================*/

// Used inside main() for quick testing
void test(void)
{
    #define ROWS (3)
    #define COLS (3)
    
    double matrix[ROWS][COLS] = {0};
    requestDoubleMatrix(ROWS, COLS, (double*)matrix, "Enter a matrix of ints:\n", true);
    puts("");
    printDoubleMatrix(ROWS, COLS, (double*)matrix, true);
    puts("done");

    #undef ROWS
    #undef COLS
}

double requestDouble(const char* nullableMsg)
{
    printNullable(nullableMsg);
    double input = 0.0;
    requestNumber(NumType_Double, &input, NULL);
    return input;
}

float requestFloat(const char* nullableMsg)
{
    printNullable(nullableMsg);
    float input = 0.0f;
    requestNumber(NumType_Float, &input, NULL);
    return input;
}

int requestInt(const char* nullableMsg)
{
    printNullable(nullableMsg);
    int input = 0;
    requestNumber(NumType_Int, &input, NULL);
    return input;
}

int requestSize(const char* nullableMsg)
{
    printNullable(nullableMsg);
    
    int input = 0;
    requestNumber(NumType_Int, &input, NULL);
    
    while (input <= 0)
    {
        requestNumber(NumType_Int, &input, "The number must be higher than zero.\n");
    }

    return input;
}

bool tryRequestSize(const char* nullableMsg, int* output)
{
    printNullable(nullableMsg);
    
    int input = 0;
    requestNumber(NumType_Int, &input, NULL);
    
    if (input <= 0)
    {
        return false;
    }

    *output = input;
    return true;
}

char* requestString(int length, char* output, const char* nullableMsg)
{
    if (!output)
    {
        return NULL;
    }
    
    printNullable(nullableMsg);

    char buffer[length];
    if (fseek(stdin, 0, SEEK_END) > 0)
    {
        getchar();
        rewind(stdin);
    }
    fgets(buffer, length, stdin);
    
    if (buffer[length - 2] == '\n')
    {
        buffer[length - 2] = '\0';
    }
    snprintf(output, strlen(buffer), "%s", buffer);
    return output;
}

void requestDoubleArray(int length, double* array, const char* nullableMsg, bool showElemMsgs)
{
    printNullable(nullableMsg);
    requestArray(NumType_Double, length, array, showElemMsgs, false, NULL);
}

void requestFloatArray(int length, float* array, const char* nullableMsg, bool showElemMsgs)
{
    printNullable(nullableMsg);
    requestArray(NumType_Float, length, array, showElemMsgs, false, NULL);
}

void requestIntArray(int length, int* array, const char* nullableMsg, bool showElemMsgs)
{
    printNullable(nullableMsg);
    requestArray(NumType_Int, length, array, showElemMsgs, false, NULL);
}

void requestDoubleMatrix(int rows, int cols, double* matrix, const char* nullableMsg, bool showElemMsgs)
{
    printNullable(nullableMsg);
    requestMatrix(NumType_Double, rows, cols, matrix, showElemMsgs, NULL);
}

void requestFloatMatrix(int rows, int cols, float* matrix, const char* nullableMsg, bool showElemMsgs)
{
    printNullable(nullableMsg);
    requestMatrix(NumType_Float, rows, cols, matrix, showElemMsgs, NULL);
}

void requestIntMatrix(int rows, int cols, int* matrix, const char* nullableMsg, bool showElemMsgs)
{
    printNullable(nullableMsg);
    requestMatrix(NumType_Int, rows, cols, matrix, showElemMsgs, NULL);
}

void printDoubleArray(int length, double* array, bool newline)
{
    printArray(NumType_Double, length, array, newline);
}

void printFloatArray(int length, float* array, bool newline)
{
    printArray(NumType_Float, length, array, newline);
}

void printIntArray(int length, int* array, bool newline)
{
    printArray(NumType_Int, length, array, newline);
}

void printDoubleMatrix(int rows, int cols, double* matrix, bool newline)
{
    printMatrix(NumType_Double, rows, cols, matrix, newline);
}

void printFloatMatrix(int rows, int cols, float* matrix, bool newline)
{
    printMatrix(NumType_Float, rows, cols, matrix, newline);
}

void printIntMatrix(int rows, int cols, int* matrix, bool newline)
{
    printMatrix(NumType_Int, rows, cols, matrix, newline);
}

/*====================
   Tool functions'
   implementation
====================*/


static void* getArrayElem(NumType type, int length, void* array, int index)
{
    if (index >= length || index < 0)
        return NULL;

    int size = NumberInfoTable[type].size;
    unsigned char* elem = (unsigned char*)array + index * size;
    return (void*)elem;
}

static void* getMatrixElem(NumType type, int rows, int cols, void* matrix, int row, int col)
{
    return getArrayElem(type, rows * cols, matrix, cols * row + col);
}

static void* getMatrixRow(NumType type, int rows, int cols, void* matrix, int row)
{
    return getMatrixElem(type, rows, cols, matrix, row, 0);
}

static void assignNumber(NumType type, void* left, void* right)
{
    if (left == right)
        return;
        
    int size = NumberInfoTable[type].size;
    memcpy(left, right, size);
}

static void requestNumber(NumType type, void* output, const char* nullableMsg, ...)
{
    va_list params;
    va_start(params, nullableMsg);
    vprintNullable(nullableMsg, &params);

    char buffer[8];
    sprintf(buffer, " %s", NumberInfoTable[type].formatSpecifier);

    scanf(buffer, output);
    getchar();

    va_end(params);
}

static void requestArray(NumType type, int length, void* array, bool showElemMsgs, bool isMatrixRow, const char* nullableMsg, ...)
{
    va_list params;
    va_start(params, nullableMsg);

    vprintNullable(nullableMsg, &params);

    va_end(params);

    const char* format = isMatrixRow ?
        "Enter element at column %i: " : "Enter element %i: ";
    
    for (int i = 0; i < length; i++)
    {
        void* elem = getArrayElem(type, length, array, i);
        requestNumber(type, elem, showElemMsgs ? format : NULL, i + 1);
    }
}

static void requestMatrix(NumType type, int rows, int cols, void* matrix, bool showElemMsgs, const char* nullableMsg, ...)
{
    va_list params;
    va_start(params, nullableMsg);

    vprintNullable(nullableMsg, &params);

    va_end(params);

    const char* format = "Enter row %i:\n";
    for (int i = 0; i < rows; i++)
    {
        void* row = getMatrixRow(type, rows, cols, matrix, i);
        requestArray(type, cols, row, true, true, showElemMsgs ? format : NULL, i + 1);
    }
}

static void printNumber(NumType type, void* value, bool newline)
{
    NumberInfoTable[type].untabbedPrinter(type, value);
    if (newline)
        puts("");
}

static void printArray(NumType type, int length, void* array, bool newline)
{
    for (int i = 0; i < length; i++)
    {
        void* elem = getArrayElem(type, length, array, i);
        printNumber(type, elem, false);
        if (i < length - 1) 
            putchar(' ');
    }

    if (newline)
        puts("");
}

static void printMatrix(NumType type, int rows, int cols, void* matrix, bool newline)
{
    for (int i = 0; i < rows; i++)
    {
        void* row = getMatrixRow(type, rows, cols, matrix, i);
        //void* column = getArrayElem(type, cols + cols * i, matrix, rows * i);
        printArray(type, cols, row, true);
    }
    if (newline)
        puts("");
}

static void printNullableOrDefault(const char* nullableMsg, const char* defaultMsg)
{
    const char* msg = nullableMsg;
    if (!msg)
        msg = defaultMsg;

    printNullable(msg);
}

static void printNullable(const char* nullableMsg)
{
    if (!nullableMsg)
        return;

    printf("%s", nullableMsg);
}

static void vprintNullable(const char* nullableMsg, va_list* params)
{
    if (!nullableMsg)
        return;

    vprintf(nullableMsg, *params);
}
