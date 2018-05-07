#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "shape.h"
#include "geometry.h"
#include "colors.h"
#include "raytracer.h"

/* Retourne 1 si le rayon et la forme s'intersecte, sinon 0 */
int intersectsSphere(Ray r, Sphere s, Intersection* i){

	return 1;
}

int intersectsCube(Ray r, Cube s, Intersection* i){
	return 1;
}

Scene createScene(){
	Scene s;
	int i;
	for(i=0 ; i<10 ; i++){
		s.tabS[i] = 0;
		s.tabC[i] = 0;
	}
	return s;
}