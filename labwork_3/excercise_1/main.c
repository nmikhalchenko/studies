// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shared_code/shared_code.h"

int isNaturalNumber(float n)
{
    if (n <= 0.0f)
        return 0;

    float preDot = truncf(n);
    if ((n - preDot) > 0.0f)
        return 0;

    return 1;
}

int yearsUntilTriple(int n)
{
    int counter = 0;
    for (int i = 0; i < n * 2; i++)
    {
        ++counter;
    }

    return counter;
}

int main(void)
{
    puts("The city's population increases by 1 / n every year.");
    float input = requestFloat("Enter the value of the natural number n: ");

    printf("Received value: %i\n", (int)input);

    int checkedInput = 0;

    if (!isNaturalNumber(input))
    {
        puts("The value received is not natural. Exiting.");
        return -1;
    }

    checkedInput = (int)input;
    int years = yearsUntilTriple(checkedInput);

    printf("The city's population will triple in %i %s.\n",
        years, years == 1 ? "year" : "years");

    return 0;
}