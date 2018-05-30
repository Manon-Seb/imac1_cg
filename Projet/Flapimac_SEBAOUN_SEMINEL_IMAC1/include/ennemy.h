#ifndef ENNEMY
#define ENNEMY

#include "collision.h"

typedef struct ennemy{
  BoundingBox boxEnnemy;
  struct ennemy *next;
}Ennemy,*ennemyList;

ennemyList allocateEnnemy(float x1, float y1, float x2, float y2);
  /* Allocate an ennemy object */
void readEnnemy(ennemyList list);
  /* Read coordonnate of an ennemy list */
ennemyList saveEnnemy(int level[100][10][3],ennemyList *list);
  /* Save every ennemy from the level array in an ennemy chained list */
ennemyList updateEnnemy(ennemyList *ennemy,int *ennemyMove);
  /* Update coordonnate of all the ennemy in the ennemy list */
int collision_ennemy(BoundingBox vaisseau, ennemyList list);
  /* Compare coordonate and return 0 if coordonates overlap */
void drawEnnemy(ennemyList list,float speed,GLuint textureID[10]);
  /* Draw and texture ennemies from the list */
ennemyList freeEnnemy(ennemyList *list);
  /* free the ennemy chained list */
ennemyList deleteEnnemy(ennemyList *list,float x, float y);
  /* delete the ennemy from the chained list where coordonates are x and y */
#endif
