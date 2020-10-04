 // Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "point.h"

#define CIRCLE_RADIUS 1.0f

float getSegmentLength(Point p1,
                       Point p2)
{
    return fabsf(sqrtf(
           powf(p2.x - p1.x, 2.0f) +
           powf(p2.y - p1.y, 2.0f)));
}

int isPointInCircleTop(Point p)
{
    if (p.y < 0.0f)
        return 0;

    Point center = {0.0f, 0.0f};
    float dist = getSegmentLength(p, center);

    return dist > CIRCLE_RADIUS ? 0 : 1;
}

Point readPoint(void)
{
    Point p = {0.0f, 0.0f};

    puts("Введите координату x точки: ");
    scanf("%f", &p.x);

    puts("Введите координату y точки: ");
    scanf("%f", &p.y);

    return p;
}

int main(void)
{
    Point p = readPoint();
    printf("%f, %f\n", p.x, p.y);
    if (isPointInCircleTop(p))
        puts("Точка находится в верхней части круга.");
    else
        puts("Точка не находится в верхней части круга.");

    return 0;
}