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

PList allocateProjectile(float x,float y){
  /* Allocation */

  Projectile *newProjectile;
  newProjectile = malloc(sizeof*(newProjectile));

  if(newProjectile == NULL)
  {
    printf("NOT ENOUGH MEMORY !\n");
    return NULL;
  }

  /* Initialisation */
  newProjectile->x=x;
  newProjectile->y=y;
  newProjectile->next=NULL;

  return newProjectile;
}

void ReadProjectile(PList list){
  while(list!=NULL){
    printf("Position : (%f,%f)\n",list->x,list->y);
    list=list->next;
  }
}

PList addProjectile(float x,float y,PList *list){
  Projectile * tmp = NULL;
  if (*list == NULL){
    *list = allocateProjectile(x,y);
    return *list;
  }

  tmp = *list;

  while ((*list)->next!= NULL){
    *list = (*list)->next;
  }
  (*list)->next = allocateProjectile(x,y);
  *list = tmp;
  return *list;
}

PList subProjectile(float x,PList *list){
  while ((*list)!=NULL && (*list)->x>5){
    *list = (*list)->next;
    // free(list);
  }
  return *list;
}

PList updateProjectile(PList *list){
  float speed=0.002;
  Projectile * tmp = NULL;
  if (*list == NULL){
    return *list;
  }

  tmp = *list;

  while ((*list)->next!= NULL){
    (*list)->x+=speed;
    *list = (*list)->next;
  }
  (*list)->x+=speed;
  *list = tmp;
  subProjectile(5,&(*list));
  return *list;
}


void drawProjectile(PList list,float speed){
  if (list == NULL){
    return ;
  }
  while ((list)!= NULL){
    glColor3ub(0,0,255);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-((list)->x+speed),(list)->y/(8.2),0);
    glPushMatrix();
    //TODO : dessiner plutot un rectancle fin plus facile à texturé ensuite
    glBegin(GL_LINES);
      glVertex2f(0,0.0);
      glVertex2f(0.2,0.0);
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
