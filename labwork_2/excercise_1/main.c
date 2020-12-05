// Вариант 5

#include <stdlib.h>
#include <stdio.h>

#include "shared_code/shared_code.h"
#include "trifuncs.h"

Point requestPoint(const char* pointName)
{
    Point p = {0, 0};

    printf("Enter the x coordinate of %s:\n", pointName);
    p.x = requestDouble(NULL);

    printf("Enter the y coordinate of %s:\n", pointName);
    p.y = requestDouble(NULL);

    return p;
}

int main(void)
{
    Point p1 = requestPoint("A");
    Point p2 = requestPoint("B");
    Point p3 = requestPoint("C");

    TriangleType tType = getTriangleType(p1, p2, p3);

    switch (tType)
    {
        case TriangleType_BadTriangle:
            puts("Impossible triangle.");
            break;
        
        case TriangleType_AcuteAngled:
            puts("Acute-angled triangle.");
            break;

        case TriangleType_RightAngled:
            puts("Right-angled triangle.");
            break;

        case TriangleType_Obtuse:
            puts("Obtuse triangle.");
            break;
    }

    return 0;
}