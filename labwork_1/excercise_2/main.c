// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VALUE_TO_COMPARE_TO -182.038
#define X -15.246
#define Y 0.04642
#define Z 21.0

double deg2rad(double deg)
{
    return deg * M_PI / 180.0;
}

double expression(double x, double y, double z)
{
    double result = 
        log(pow(y, -sqrt(abs(x)))) *
        (x - y / 2.0) + 
        pow(deg2rad(sin(atan(deg2rad(z)))), 2);

    

    return result;
}

int main(void)
{
    // При запуске было равно -182.038 .
    printf("Значение для сравнения: %g\n", 
        VALUE_TO_COMPARE_TO);

    // При запуске было равно -181.553 .
    printf("Значение выражения: %g\n",
        expression(X, Y, Z));

    return 0;
}