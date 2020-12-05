// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shared_code/shared_code.h"

double getPi(int count)
{
    double quarterOfPi = 0.0;
    double divisor = 1.0;
    double sign = 1.0;

    for (int i = 1; i <= count; i++)
    {
        quarterOfPi += sign / divisor;

        divisor += 2.0;
        sign = sign > 0 ? -1.0 : 1.0;
    }

    return quarterOfPi * 4.0;
}

int main(void)
{
    int iterAmt = requestInt("Enter the amount of iterations: ");
    printf("Результат: %lg\n", getPi(iterAmt));
    return 0;
}