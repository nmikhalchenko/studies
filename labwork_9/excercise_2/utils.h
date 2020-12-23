#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

int min(int a, int b);
int max(int a, int b);
int digitCount(int number);
bool tryPadFormatSpecifier(const char* specifier, int padding, char* output, int length);

#endif // UTILS_H