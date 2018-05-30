#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projectile.h"
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

PList allocateProjectile(float x1,float y1,float x2,float y2){
  /* Allocation */

  Projectile *newProjectile;
  newProjectile = malloc(sizeof*(newProjectile));

  if(newProjectile == NULL)
  {
    printf("NOT ENOUGH MEMORY !\n");
    return NULL;
  }

  /* Initialisation */
  newProjectile->x1=x1;
  newProjectile->y1=y1;
  newProjectile->x2=x2;
  newProjectile->y2=y2;
  newProjectile->next=NULL;

  return newProjectile;
}

void ReadProjectile(PList list){
  while(list!=NULL){
    printf("Position : (%f,%f) (%f,%f)\n",list->x1,list->y1, list->x2, list->y2);
    list=list->next;
  }
}

PList addProjectile(float x1,float y1,float x2,float y2,PList *list){
  Projectile * tmp = NULL;
  if (*list == NULL){
    *list = allocateProjectile(x1,y1,x2,y2);
    return *list;
  }

  tmp = *list;

  while ((*list)->next!= NULL){
    *list = (*list)->next;
  }
  (*list)->next = allocateProjectile(x1,y1,x2,y2);
  *list = tmp;
  return *list;
}

PList subProjectile(float x,PList *list){
  while ((*list)!=NULL && (*list)->x1>5){
    *list = (*list)->next;
    // free(list);
  }
  return *list;
}

PList updateProjectile(PList *list){
  float speed=0.0001;
  Projectile * tmp = NULL;
  if (*list == NULL){
    return *list;
  }

  tmp = *list;

  while ((*list)->next!= NULL){
    (*list)->x1+=speed;
    *list = (*list)->next;
  }
  (*list)->x1+=speed;
  *list = tmp;
  subProjectile(5,&(*list));
  return *list;
}


void drawProjectile(PList list,float speed){
  if (list == NULL){
    return ;
  }
  while ((list)!= NULL){
    glColor3ub(255,255,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-((list)->x1+speed),(list)->y1/(8.2),0);
    glPushMatrix();
    //TODO : dessiner plutot un rectancle fin plus facile à texturé ensuite
    glBegin(GL_POLYGON);
      glVertex2f(0.0,0.0);
      glVertex2f(0.2,0.0);
      glVertex2f(0.2, -0.01);
      glVertex2f(0.0, -0.01);
    glEnd();
    glPopMatrix();
    list = (list)->next;
  }
  return ;
}


/*
int main(){
  PList projectile = NULL;
  projectile = addProjectile(7,1,&projectile);
  projectile = addProjectile(5,1,&projectile);
  projectile = addProjectile(3,1,&projectile);
  projectile = addProjectile(2,1,&projectile);
  ReadProjectile(projectile);
  projectile = subProjectile(5,&projectile);
  printf("Nouvelle liste :\n");
  ReadProjectile(projectile);
}
*/
