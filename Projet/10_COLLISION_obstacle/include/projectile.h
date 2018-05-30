#ifndef PROJECT
#define PROJECT

typedef struct projectile{
  float x1;
  float y1;
  float x2;
  float y2;
  //BoundingBox boxProjectile;
  struct projectile *next;
}Projectile,*PList;

PList allocateProjectile(float x1,float y1, float x2, float y2);
PList addProjectile(float x1,float y1, float x2, float y2, PList *list);
PList subProjectile(float x1, PList *list);
PList updateProjectile(PList *list);

void ReadProjectile(PList list);
void drawProjectile(PList list,float speed);

#endif
