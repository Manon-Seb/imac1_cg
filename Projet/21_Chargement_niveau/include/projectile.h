#ifndef PROJECT
#define PROJECT

#include "ennemy.h"

typedef struct projectile{
  float x;
  float y;
  BoundingBox projectileBB;
  struct projectile *next;
}Projectile,*PList;

PList allocateProjectile(float x,float y);
PList addProjectile(float x,float y,PList *list);
PList subProjectile(float x,PList *list);
PList updateProjectile(PList *list);
void ReadProjectile(PList list);
void drawProjectile(PList list,float speed,GLuint textureID[10]);
void drawProjectile_(GLuint textureID[10],PList list);
PList freeProjectile(PList *list);
int collision_projectile_obstacle(PList *lprojectile,obsList list);
int collision_projectile_ennemy(PList *lprojectile,ennemyList *Elist);
PList deleteProjectile(PList *projectile,float x,float y);
#endif
