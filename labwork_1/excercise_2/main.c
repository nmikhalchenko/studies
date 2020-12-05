// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VALUE_TO_COMPARE_TO -182.038
#define X -15.246
#define Y 0.04642
#define Z 21.0

double expression(double x, double y, double z)
{
    double result = 
        log(pow(y, -sqrt(fabs(x)))) *
        (x - y / 2.0) + 
        pow(sin(atan(z)), 2.0);

    return result;
}

int main(void)
{
    printf("X: %lg\nY: %lg\nZ: %lg\n", X, Y, Z);

    printf("Demanded value: %lg\n", 
        VALUE_TO_COMPARE_TO);

    printf("Expression value: %lg\n",
        expression(X, Y, Z));

    return 0;
}