#ifndef COLLISION
#define COLLISION
#include "list.h"
#include "obstacle.h"


typedef struct boundingBox{
	float pMinX, pMinY;
	float pMaxX, pMaxY;
} BoundingBox;

int collision(BoundingBox vaisseau, BoundingBox decor);
BoundingBox calculateBoundingBox();
void drawBoundingBox(BoundingBox box);
int collision_(BoundingBox vaisseau, obsList list);
BoundingBox updateBoundingBox(BoundingBox *PlayerBB,int transY);
BoundingBox updateBoundingBoxProjectile(BoundingBox *playerBB,int transY);

#endif
