#ifndef COLLISION
#define COLLISION
#include "list.h"
#include "obstacle.h"
#include "ennemy.h"
#include "bonus.h"
#include "projectile.h"

typedef struct boundingBox{
	float pMinX, pMinY;
	float pMaxX, pMaxY;
} BoundingBox;

int collision(BoundingBox vaisseau, BoundingBox decor);
BoundingBox calculateBoundingBox();
void drawBoundingBox(BoundingBox box);
int collision_(BoundingBox vaisseau, obsList list);
int collision_ennemy(BoundingBox vaisseau, ennemyList list);
int collision_bonus(BoundingBox vaisseau, bonusList list);
int collision_proj_decor(PList projList, obsList list);
BoundingBox updateBoundingBox(BoundingBox *PlayerBB,int transY);

#endif
