// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>

#define MULTIPLIER 2
#define EXPONENT 8

int main(void)
{
    // Вызов этой функции не изменяет
    // ход выполнения программы.
    //
    //setlocale(LC_ALL, "Russian");

    float x;
    puts("Введите число:");
    scanf("%f", &x);

    printf(
        "Число %f в степени %i, умноженное на %i: %f\n", 
        x, 
        EXPONENT, 
        MULTIPLIER, 
        powf(x, EXPONENT) * MULTIPLIER);

    return 0;
}