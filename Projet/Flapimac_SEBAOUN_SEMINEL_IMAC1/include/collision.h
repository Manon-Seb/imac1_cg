#ifndef COLLISION
#define COLLISION
#include "obstacle.h"


typedef struct boundingBox{
	float pMinX, pMinY;
	float pMaxX, pMaxY;
} BoundingBox;


BoundingBox calculateBoundingBox();

void drawBoundingBox(BoundingBox box);

int collision_(BoundingBox spaceship, obsList list);
	/* Compare coordonnates and return 0 if coordonnates overlap. */
BoundingBox updateBoundingBox(BoundingBox *PlayerBB,int transY);
	/* Update Bounding Box coordonnate  of the player */
BoundingBox updateBoundingBoxProjectile(BoundingBox *playerBB,int transY);
	/* Update Bounding Box coordonnate of the projectile */
BoundingBox updateBoundingBoxProjectileEnnemy(BoundingBox *playerBB,int transY);
	/* Update Bounding Box coordonnate of the ennemy projectile */
	
#endif
