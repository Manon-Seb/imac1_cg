#include <stdlib.h>
#include <stdio.h>
#include "geometry.h"

int main(int arc, char** argv){
	Point3D p1, p2;
	//Vector3D v1, v2;
	
	p1 = pointXYZ(0.0,0.0,0.0);
	p2 = pointXYZ(1.0,2.0,0.0);
	printPoint3D(p1);
	//printVector3D(v);

	return EXIT_SUCCESS;
}