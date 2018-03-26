#ifndef RAYTRACER
#define RAYTRACER

typedef struct Ray{
	Point3D pOrigine;
	Vector3D direction;
}Ray;

typedef struct Intersection{
	Point3D position;
	Color3f color;
} Intersection;

typedef struct Scene{
	Sphere tabS[10];
	Cube tabC[10];
}Scene;

Ray createRay(Point3D origine, Vector3D dir);
/* teste si le rayon intersecte la forme */
int intersectsSphere(Ray r, Sphere s, Intersection* i);
int intersectsCube(Ray r, Cube s, Intersection* i);
/* création et initialisation des champs de la structure scene */
Scene createScene(Sphere tabs[10], Cube tabc[10]);

void addCubeToScene(Scene* scne, Cube cube);
void addSphereToScene(Scene* scene, Sphere sphere);

#endif
