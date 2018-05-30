#include <math.h>
#include "geometry.h"

Point3D createPoint(float x, float y, float z) {
    Point3D p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

Vector3D createVectorXYZ(float x, float y, float z) {
    Vector3D v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vector3D createVectorFromPoints(Point3D p1, Point3D p2) {
    Vector3D v;
    v.x = p2.x - p1.x;
    v.y = p2.y - p1.y;
    v.z = p2.z - p1.z;
    return v;
}

Point3D pointPlusVector(Point3D p, Vector3D v) {
    v.x += p.x;
    v.y += p.y;
    v.z += p.z;
    return v;
}

Vector3D addVectors(Vector3D v1, Vector3D v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.z += v2.z;
    return v1;
}

Vector3D subVectors(Vector3D v1, Vector3D v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.z -= v2.z;
    return v1;
}

Vector3D multVector(Vector3D v, float a) {
    v.x *= a;
    v.y *= a;
    v.z *= a;
    return v;
}

Vector3D divVector(Vector3D v, float a) {
    v.x /= a;
    v.y /= a;
    v.z /= a;
    return v;
}

float dot(Vector3D v1, Vector3D v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float norm(Vector3D v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3D normalize(Vector3D v) {
    float n = norm(v);
    v.x /= n;
    v.y /= n;
    v.z /= n;
    return v;
}

float distance(Point3D p1, Point3D p2) {
    return norm(createVectorFromPoints(p1, p2));
}

Vector3D reflect(Vector3D V, Vector3D N){
    // normalisation des vecteurs
    V = normalize(V);
    N = normalize(N);

    Vector3D R;
    Vector3D mult1 = multVector(N,2.0);
    Vector3D multV_N, multTotal;
    multV_N.x = (V.x)*(N.x);
    multV_N.y = (V.y)*(N.y);
    multV_N.z = (V.z)*(N.z);
    
    multTotal.x = (mult1.x)*(multV_N.x);
    multTotal.x = (mult1.y)*(multV_N.y);
    multTotal.x = (mult1.z)*(multV_N.z);

    return R;
}
