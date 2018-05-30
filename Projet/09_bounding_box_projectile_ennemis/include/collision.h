#ifndef COLLISION
#define COLLISION

#include "list.h"

typedef struct boundingBox{
	float pMinX, pMinY;
	float pMaxX, pMaxY;
} BoundingBox;

int collision(BoundingBox vaisseau, BoundingBox decor);
BoundingBox calculateBoundingBox();
void drawBoundingBox(BoundingBox box);

#endif