#ifndef DGAME
#define DGAME 100

#include "projectile.h"
#include "collision.h"
#include "ennemy.h"

float displayGame(int transY_,float speed,float transX,float transY,float transZ,PList *projectile,
  BoundingBox *playerBB,obsList obstacle,int levelarray[100][10][3],
  ennemyList *ennemy,int *ennemyMove,PList *projectileEnnemy,GLuint textureID[10]);
void drawLevel(int level[100][10][3],float speed,float transX, float transY, float transZ,ennemyList ennemy,GLuint textureID[10]);
void drawPlayer(float transX,float transY,float transZ,GLuint textureID[10]);
#endif
