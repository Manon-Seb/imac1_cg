#ifndef GEOMETRY
#define GEOMETRY

typedef struct vec3{
	float x, y, z;
}Point3D, Vector3D;

// construit point (x,y,z)
Point3D pointXYZ(float x, float y, float z);
// construit vecteur (x,y,z)
Vector3D vectorXYZ(float x, float y, float z);
// construit le vecteur AB = B-A
Vector3D vector(Point3D A, Point3D B);
// construit le point P+V
Point3D pointPlusVector(Point3D P, Vector3D V);
// fonctions d'addition et soustraction de vecteurs
Vector3D addVectors(Vector3D A, Vector3D B);
Vector3D subVector(Vector3D A, Vector3D B);
// fonctions de multiplication et division d'un vecteur par un scalaire
Vector3D multVector(Vector3D V, float a);
Vector3D divVector(Vector3D V, float a);
// fonction calculant le produit scalaire de deux vecteurs
float dot(Vector3D A, Vector3D B);
// fonction calculant la norme d'un vecteur
float norm(Vector3D A);
// fonction retournant le vecteur normalisé passé en paramètre
Vector3D normalize(Vector3D A);
// affiche le contenu du vecteur et du point passés en paramètres
void printVector3D(Vector3D v);
void printPoint3D(Point3D p);

 #endif