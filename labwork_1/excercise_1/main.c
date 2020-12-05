// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shared_code/shared_code.h"

#define MULTIPLIER 2
#define EXPONENT 8

int main(void)
{
    float x = requestFloat("Enter a number: ");

    printf(
        "(%f ^ %i) * %i = %f\n", 
        x, 
        EXPONENT, 
        MULTIPLIER, 
        powf(x, EXPONENT) * MULTIPLIER);

    return 0;
}