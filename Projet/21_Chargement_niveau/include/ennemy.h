#ifndef ENNEMY
#define ENNEMY

#include "collision.h"

typedef struct ennemy{
  /*float x1;
  float y1;
  float x2;
  float y2;*/
  BoundingBox boxEnnemy;
  struct ennemy *next;
}Ennemy,*ennemyList;

ennemyList allocateEnnemy(float x1, float y1, float x2, float y2);
void readEnnemy(ennemyList list);
ennemyList saveEnnemy(int level[100][10][3],ennemyList *list);
ennemyList updateEnnemy(ennemyList *ennemy,int *ennemyMove);
int collision_ennemy(BoundingBox vaisseau, ennemyList list);
void drawEnnemy(ennemyList list,float speed,GLuint textureID[10]);
ennemyList freeEnnemy(ennemyList *list);
ennemyList deleteEnnemy(ennemyList *list,float x, float y);
#endif
