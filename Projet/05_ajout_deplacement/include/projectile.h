#ifndef PROJECT
#define PROJECT

typedef struct projectile{
  float x;
  float y;
  struct projectile *next;
}Projectile,*PList;

PList allocateProjectile(float x,float y);
PList addProjectile(float x,float y,PList *list);
PList subProjectile(float x,PList *list);
PList updateProjectile(PList *list);

void ReadProjectile(PList list);
void drawProjectile(PList list,float speed);

#endif
