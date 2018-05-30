#include "shape.h"

Sphere createSphere(Point3D center, float radius, Color3f color) {
    Sphere sphere;
    sphere.center = center;
    sphere.radius = radius;
    sphere.color = color;
    return sphere;
}
