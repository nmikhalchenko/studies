#include <math.h>

#include "trifuncs.h"

typedef struct TriSides_s
{
    double a;
    double b;
    double c;
}
TriSides;

static double getSegmentLength(Point p1,
                               Point p2)
{
    return sqrt(
           pow(p2.x - p1.x, 2.0) +
           pow(p2.y - p1.y, 2.0));
}

static TriSides verticesToSides(Point p1,
                                Point p2,
                                Point p3)
{
    TriSides sides = {0.0, 0.0, 0.0};
    sides.a = getSegmentLength(p1, p2);
    sides.b = getSegmentLength(p2, p3);
    sides.c = getSegmentLength(p1, p3);
    return sides;
}

static int isValidTriangle(Point p1,
                         Point p2,
                         Point p3)
{
    TriSides sides = verticesToSides(p1, p2, p3);

    if (((sides.a + sides.b) > sides.c) &&
        ((sides.a + sides.c) > sides.b) &&
        ((sides.b + sides.c) > sides.a))
        return 1;

    return 0;
}

TriangleType getTriangleType(Point p1,
                             Point p2,
                             Point p3)
{
    if (!isValidTriangle(p1, p2, p3))
        return TriangleType_BadTriangle;

    TriSides sides = verticesToSides(p1, p2, p3);

    double k = 0.0;
    double l = 0.0;
    double h = 0.0;

    k = sides.a < sides.b ?
        sides.a : sides.b;

    l = sides.a < sides.b ?
        sides.b : sides.a;

    if (l < sides.c)
        h = sides.c;
    else
    {
        h = l;
        l = sides.c;
    }

    double t1 = pow(h, 2.0);
    double t2 = pow(k, 2.0) + pow(l, 2.0);

    if (t1 == t2)
        return TriangleType_RightAngled;
    else if (t1 < t2)
        return TriangleType_AcuteAngled;
    else
        return TriangleType_Obtuse;
}