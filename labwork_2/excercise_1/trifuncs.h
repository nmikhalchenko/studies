#ifndef TRIFUNCS_H
#define TRIFUNCS_H

typedef struct PointStruct
{
    double x;
    double y;
}
Point;

typedef enum TriangleTypeEnum
{
    TriangleType_BadTriangle, // Невозможный
    TriangleType_AcuteAngled, // Остроугольный
    TriangleType_RightAngled, // Прямоугольный
    TriangleType_Obtuse       // Тупоугольный
} 
TriangleType;

TriangleType getTriangleType(Point p1,
                             Point p2,
                             Point p3);

#endif