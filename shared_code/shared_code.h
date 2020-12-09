#ifndef SIMPLEUSERIO_H
#define SIMPLEUSERIO_H

#include <stdbool.h>

void test(void);

double  requestDouble       (const char* nullableMsg);
float   requestFloat        (const char* nullableMsg);
int     requestInt          (const char* nullableMsg);
int     requestSize         (const char* nullableMsg);
bool    tryRequestSize      (const char* nullableMsg, int* output);

char*   requestString       (int length, char* output, const char* nullableMsg);

void    requestDoubleArray  (int length, double* array, const char* nullableMsg, bool showElemMsgs);
void    requestFloatArray   (int length, float* array, const char* nullableMsg, bool showElemMsgs);
void    requestIntArray     (int length, int* array, const char* nullableMsg, bool showElemtMsgs);

void    requestDoubleMatrix (int rows, int cols, double* matrix, const char* nullableMsg, bool showElemMsgs);
void    requestFloatMatrix  (int rows, int cols, float* matrix, const char* nullableMsg, bool showElemMsgs);
void    requestIntMatrix    (int rows, int cols, int* matrix, const char* nullableMsg, bool showElemMsgs);

void    printDoubleArray    (int length, double* array, bool newline);
void    printFloatArray     (int length, float* array, bool newline);
void    printIntArray       (int length, int* array, bool newline);

void 	printDoubleMatrix   (int rows, int cols, double* matrix, bool newline);
void 	printFloatMatrix    (int rows, int cols, float* matrix, bool newline);
void 	printIntMatrix	    (int rows, int cols, int* matrix, bool newline);

#endif // SIMPLEUSERIO_H
