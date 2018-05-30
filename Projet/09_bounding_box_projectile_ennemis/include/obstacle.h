#ifndef OBS
#define OBS

#include "collision.h"

typedef struct obstacle{
  /*float x1;
  float y1;
  float x2;
  float y2;*/
  BoundingBox boxObstacle;
  struct obstacle *next;
}Obstacle,*obsList;

void readObstacle(obsList list);
obsList allocateObs(float x1, float y1, float x2, float y2);
obsList saveObstacle(int level[100][10][3],obsList *obstacle);

#endif
