#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "geometry.h"

// construit point (x,y,z)
Point3D pointXYZ(float x, float y, float z){
	Point3D point;
	point.x=x;
	point.y=y;
	point.z=z;
	return point;
}
// construit vecteur (x,y,z)
Vector3D vectorXYZ(float x, float y, float z){
	Vector3D vector;
	vector.x=x;
	vector.y=y;
	vector.z=z;
	return vector;
}
// construit le vecteur AB = B-A
Vector3D vector(Point3D A, Point3D B){
	Vector3D AB;
	AB.x=((B.x)-(A.x));
	AB.y=((B.y)-(A.y));
	AB.z=((B.z)-(A.z));
	return AB;
}
// construit le point P+V
Point3D pointPlusVector(Point3D P, Vector3D V){
	Point3D PV;
	PV.x = ((P.x)+(V.x));
	PV.y = ((P.y)+(V.y));
	PV.z = ((P.z)+(V.z));
	return PV;
}
// fonctions d'addition et soustraction de vecteurs
Vector3D addVectors(Vector3D A, Vector3D B){
	Vector3D addAB;
	addAB.x = ((A.x)+(B.x));
	addAB.y = ((A.y)+(B.y));
	addAB.z = ((A.z)+(B.z));
	return addAB;
}
Vector3D subVector(Vector3D A, Vector3D B){
	Vector3D subAB;
	subAB.x = ((A.x)+(-B.x));
	subAB.y = ((A.y)+(-B.y));
	subAB.z = ((A.z)+(-B.z));
	return subAB;
}
// fonctions de multiplication et division d'un vecteur par un scalaire
Vector3D multVector(Vector3D V, float a){
	Vector3D multVa;
	multVa.x = (V.x)*a;
	multVa.y = (V.y)*a;
	multVa.z = (V.z)*a;
	return multVa;
}
Vector3D divVector(Vector3D V, float a){
	Vector3D divVa;
	divVa.x = (V.x)/a;
	divVa.y = (V.y)/a;
	divVa.z = (V.z)/a;
	return divVa;
}
// fonction calculant le produit scalaire de deux vecteurs
float dot(Vector3D A, Vector3D B){
	float prodScalAB;
	prodScalAB = ((A.x)*(B.x))+((A.y)*(B.y))+((A.z)*(B.z));
	return prodScalAB;
}
// fonction calculant la norme d'un vecteur
float norm(Vector3D A){
	float normA;
	// norme = racine de X^2 + Y^2 + Z^2
	normA = sqrt(pow((A.x),2) + pow((A.y),2) + pow((A.z),2));
	return normA;
}
// fonction retournant le vecteur normalisé passé en paramètre
Vector3D normalize(Vector3D A){
	Vector3D normalizeA;
	normalizeA.x = (A.x)/norm(A);
	normalizeA.y = (A.y)/norm(A);
	normalizeA.z = (A.z)/norm(A);
	return normalizeA;
}

// affiche le contenu du vecteur et du point passés en paramètres
 void printVector3D(Vector3D v){
 	printf("x = %f, y = %f, z = %f\n", v.x, v.y, v.z);
 }
 void printPoint3D(Point3D p){
 	printf("x = %f, y = %f, z = %f\n", p.x, p.y, p.z);
 }