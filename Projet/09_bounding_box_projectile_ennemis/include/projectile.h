#ifndef PROJECT
#define PROJECT

#include "collision.h"

typedef struct projectile{
  float x;
  float y;
  BoundingBox boxProjectile;
  struct projectile *next;
}Projectile,*PList;

PList allocateProjectile(float x,float y);
PList addProjectile(float x,float y,PList *list);
PList subProjectile(float x,PList *list);
PList updateProjectile(PList *list);

void ReadProjectile(PList list);
void drawProjectile(PList list,float speed);

#endif
