// Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int isNaturalNumber(float n)
{
    if (n <= 0.0f)
        return 0;

    float preDot = truncf(n);
    if ((n - preDot) > 0.0f)
        return 0;

    return 1;
}

int getPopulationTripleYear(int n)
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
    puts("Население города ежегодно увеличивается на 1 / n.");
    puts("Введите значение натурального числа n:");

    float input = 0.0f;
    scanf("%f", &input);

    printf("Вы ввели значение: %i\n", (int)input);

    int checkedInput = 0;

    if (!isNaturalNumber(input))
    {
        puts("Ошибка: введено ненатуральное число!");
        return -1;
    }

    checkedInput = (int)input;

    printf("Население города утроится через %i лет.\n",
        getPopulationTripleYear(checkedInput));

    return 0;
}