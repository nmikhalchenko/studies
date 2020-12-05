 // Вариант 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shared_code/shared_code.h"
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

Point requestPoint()
{
    Point p = {0, 0};

    p.x = requestDouble("Enter the x coordinate: ");
    p.y = requestDouble("Enter the y coordinate: ");

    return p;
}

int main(void)
{
    Point p = requestPoint();
    printf("%f, %f\n", p.x, p.y);
    if (isPointInCircleTop(p))
        puts("The point is inside the circle's upper half.");
    else
        puts("The point is not inside the circle's upper half.");

    return 0;
}