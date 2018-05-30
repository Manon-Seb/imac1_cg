#ifndef ENNEMY
#define ENNEMY

typedef struct ennemy{
  float x1;
  float y1;
  float x2;
  float y2;
  struct ennemy *next;
}Ennemy,*ennemyList;

void readEnnemy(ennemyList list);
ennemyList allocateEnnemy(float x1, float y1, float x2, float y2);
ennemyList saveEnnemy(int level[100][10][3],ennemyList *list);

#endif