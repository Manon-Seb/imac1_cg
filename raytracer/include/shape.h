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
	float pointMin, pointMax;
	Color3f color;
} Cube;

Sphere createSphere(Point3D pCenter, Color3f c);
Cube createCube(float pMin, float pMax, Color3f c);

#endif