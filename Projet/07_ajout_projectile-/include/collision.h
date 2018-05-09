#ifndef COLLISION

#include "list.h"

typedef struct boundingBox{
	int pMinX, pMinY;
	int pMaxX, pMaxY;
} BoundingBox;

int collision(BoundingBox vaisseau, BoundingBox decor);
void destruction();

#endif