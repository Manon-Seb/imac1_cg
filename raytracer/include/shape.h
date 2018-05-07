#ifndef SHAPE
#define SHAPE

#include "geometry.h"
#include "colors.h"

typedef struct Sphere{
	Point3D center;
	int rayon;
	Color3f color;
} Sphere;

typedef struct Cube{
	Point3D pointMin, pointMax;
	Color3f color;
} Cube;

Sphere createSphere(Point3D pCenter, int r, Color3f c);
Cube createCube(Point3D pMin, Point3D pMax, Color3f c);

#endif