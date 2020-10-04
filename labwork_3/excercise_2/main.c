// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ITER_AMT 1000

double getPi(int count)
{
    double pi = 0.0;
    double divisor = 1.0;
    double sign = 1.0;

    for (int i = 1; i <= count; i++)
    {
        pi += 1.0 * sign / divisor;

        divisor += 2.0;
        sign = sign > 0 ? -1.0 : 1.0;
    }

    return pi * 4.0;
}

int main(void)
{
    //int iterAmt = 0;
    //puts("Введите кол-во итераций:");
    //scanf("%i", &iterAmt);
    //
    //if (iterAmt <= 0)
    //    puts("Ошибка: кол-во должно быть больше нуля!");

    printf("Результат: %lg\n", getPi(ITER_AMT));
    return 0;
}