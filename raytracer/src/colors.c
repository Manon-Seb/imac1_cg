#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

// fonction calculant la somme de deux couleurs
Color3f addColors(Color3f c1, Color3f c2){
	Color3f *addc1c2 = NULL;
	addc1c2->r = (c1.r)+(c2.r);
	addc1c2->g = (c1.g)+(c2.g);
	addc1c2->b = (c1.b)+(c2.b);
	return *addc1c2;
}
// fonctions pour la soutraction, la multiplication et la division de couleurs
Color3f subColors(Color3f c1, Color3f c2){
	Color3f *subc1c2 = NULL;
	subc1c2->r = (c1.r)-(c2.r);
	subc1c2->g = (c1.g)-(c2.g);
	subc1c2->b = (c1.b)-(c2.b);
	return *subc1c2;
}
Color3f multColors(Color3f c1, Color3f c2){
	Color3f *multc1c2 = NULL;
	multc1c2->r = (c1.r)*(c2.r);
	multc1c2->g = (c1.g)*(c2.g);
	multc1c2->b = (c1.b)*(c2.b);
	return *multc1c2;
}
Color3f divColors(Color3f c1, Color3f c2){
	Color3f *divc1c2 = NULL;
	divc1c2->r = (c1.r)/(c2.r);
	divc1c2->g = (c1.g)/(c2.g);
	divc1c2->b = (c1.b)/(c2.b);
	return *divc1c2;
}
// fonctions de multiplication et division d'une couleur par un scalaire
Color3f multColor(Color3f c, float a){
	Color3f *multc = NULL;
	multc->r = (c.r)*a;
	multc->g = (c.g)*a;
	multc->b = (c.b)*a;
	return *multc;
}
Color3f divColor(Color3f c, float a){
	Color3f *divc = NULL;
	if(a != 0){
		divc->r = (c.r)/a;
		divc->g = (c.g)/a;
		divc->b = (c.b)/a;
	}
	else{
		printf("Division par 0 impossible.\n");
		exit(1);
	}
	return *divc;
}