#ifndef OBS
#define OBS

typedef struct obstacle{
  float x1;
  float y1;
  float x2;
  float y2;
  struct obstacle *next;
}Obstacle,*obsList;

void readObstacle(obsList list);
obsList allocateObs(float x1, float y1, float x2, float y2);
obsList saveObstacle(int level[16][8][3],obsList *obstacle);

#endif
