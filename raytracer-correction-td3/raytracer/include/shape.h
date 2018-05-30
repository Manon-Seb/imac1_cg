#ifndef SHAPE_H
#define SHAPE_H

#include "geometry.h"
#include "colors.h"
#include "shading.h"

/*typedef struct Sphere {
    Point3D center; // origin / center
    float radius;
    Color3f color;
} Sphere;

Sphere createSphere(Point3D center, float radius, Color3f color);*/

typedef struct Sphere {
    Point3D center; // origin / center
    float radius;
    Material mat;
} Sphere;

Sphere createSphere(Point3D center, float radius, Material mat);

#endif