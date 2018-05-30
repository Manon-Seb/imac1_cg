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
  /* Add a projectile in the chaine list. */
PList subProjectile(float x,PList *list);
  /* Delete all projectiles where x coordonnate is bigger than x. */
PList updateProjectile(PList *list);
  /* Update projectile coordonnates. */
void ReadProjectile(PList list);
  /* Read projectile coordonnates. */
void drawProjectile(PList list,float speed,GLuint textureID[10]);
void drawProjectile_(GLuint textureID[10],PList list);

PList freeProjectile(PList *list);
  /* delete and free a projectile chained list. */
int collision_projectile_obstacle(PList *lprojectile,obsList list);
  /* Compare coordonnate and return 0 if coordonnates overlap */
int collision_projectile_ennemy(PList *lprojectile,ennemyList *Elist);
  /* Compare coordonnate and return 0 if coordonnates overlap */
PList deleteProjectile(PList *projectile,float x,float y);
  /* delete the projectile where coordonnates are x and y from the chained list */
void drawprojectileEnnemy(PList list,float speed,GLuint textureID[10]);

void addProjectileEnnemy(ennemyList ennemy, PList *projectileEnnemy);
  /* Add a projectile in the chaine list. */
PList updateProjectileEnnemy(PList *list);
  /* Update projectile coordonnates. */
int collision_ennemyprojectile_obstacle(PList *lprojectile,obsList list);
  /* Compare coordonnate and return 0 if coordonnates overlap */
int collision_projectileennemy_vaisseau(BoundingBox vaisseau, PList list);
  /* Compare coordonnate and return 0 if coordonnates overlap */
  
#endif
