#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"

int main(int arc, char** argv){
	Point3D p1, p2;
	Vector3D v1,v2,v3,v4,v5,v6,v7,v8;
	float a = 2.0;
	float b = 0.0;
	
	p1 = pointXYZ(0.0,0.0,0.0);
	p2 = pointXYZ(1.0,2.0,0.0);

	v1 = vectorXYZ(1.0,2.0,0.0);
	v2 = vectorXYZ(0.5,1.0,-2.0);
	v3 = vectorXYZ(0.2,-1.0,0.0);
	v4 = vectorXYZ(1.0,0.0,0.0);
	v5 = vectorXYZ(2.0,0.0,0.0);
	v6 = vectorXYZ(0.0,1.0,0.0);
	v7 = vectorXYZ(1.0,1.0,1.0);
	v8 = vectorXYZ(0.0,0.0,0.0);
	
	Point3D somme = pointPlusVector(p1, v1);
	printf("Somme point + vecteur\n");
	printPoint3D(somme);

	Vector3D sommeVect = addVectors(v2,v3);
	printf("Somme de deux vecteurs\n");
	printVector3D(sommeVect);

	Vector3D multiplicationVect1 = multVector(v2,a);
	Vector3D multiplicationVect2 = multVector(v2,b);
	printf("Multiplication de vecteurs\n");
	printVector3D(multiplicationVect1);
	printVector3D(multiplicationVect2);

	Vector3D divisionVect1 = divVector(v2,a);
	Vector3D divisionVect2 = divVector(v2,b);
	printf("Division de deux vecteurs\n");
	printVector3D(divisionVect1);
	printVector3D(divisionVect2);

	float prodScalaire1 = dot(v4,v5);
	float prodScalaire2 = dot(v4,v6);
	printf("Produit scalaire n°1 = %f, n°2 = %f\n", prodScalaire1, prodScalaire2);

	float n1 = norm(v5);
	float n2 = norm(v7);
	float n3 = norm(v8);
	printf("Normes : n°1 = %f, n°2 = %f, n°3 = %f\n", n1,n2,n3);

	Vector3D normalisation1 =  normalize(v7);
	Vector3D normalisation2 = normalize(v8);
	printf("Normalisation vecteur\n");
	printVector3D(normalisation1);
	printVector3D(normalisation2);

	return EXIT_SUCCESS;
}