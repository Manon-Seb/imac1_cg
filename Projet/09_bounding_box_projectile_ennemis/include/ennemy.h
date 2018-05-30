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

#endif