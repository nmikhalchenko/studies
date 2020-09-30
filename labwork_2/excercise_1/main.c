// Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "trifuncs.h"

Point pointFromInput(const char* pointName)
{
    Point p = {0, 0};

    printf("Введите координату x точки %s:\n", pointName);
    scanf("%lg", &p.x);

    printf("Введите координату y точки %s:\n", pointName);
    scanf("%lg", &p.y);

    return p;
}

int main(void)
{
    Point p1 = pointFromInput("A");
    Point p2 = pointFromInput("B");
    Point p3 = pointFromInput("C");

    TriangleType tType = getTriangleType(p1, p2, p3);

    switch (tType)
    {
        case TriangleType_BadTriangle:
            puts("Такой треугольник невозможен.");
            break;
        
        case TriangleType_AcuteAngled:
            puts("Треугольник остроугольный.");
            break;

        case TriangleType_RightAngled:
            puts("Треугольник прямоугольный.");
            break;

        case TriangleType_Obtuse:
            puts("Треугольник тупоугольный.");
            break;
    }

    return 0;
}