#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

#include "ennemy.h"
#include "ppm.h"
#include "texture.h"

ennemyList allocateEnnemy(float x1, float y1, float x2, float y2){
  /* Allocation */
  Ennemy *newEnnemy;
  newEnnemy= malloc(sizeof*(newEnnemy));

  if(newEnnemy== NULL)
  {
    printf("NOT ENOUGH MEMORY !\n");
    return NULL;
  }

  /* Initialisation */
  newEnnemy->boxEnnemy.pMinX = 50 + x1;
  newEnnemy->boxEnnemy.pMinY = y1;
  newEnnemy->boxEnnemy.pMaxX = 50 + x2;
  newEnnemy->boxEnnemy.pMaxY = y2;
  newEnnemy->next = NULL;

  return newEnnemy;
}

void readEnnemy(ennemyList list){
  int i=0;
  printf("--------- ENNEMIES LIST -----------\n");
  while (list!= NULL){
    printf(" POSITION DE L'ENNEMY %d : (%f,%f)/(%f,%f)\n",i,list->boxEnnemy.pMinX,list->boxEnnemy.pMinY,list->boxEnnemy.pMaxX,list->boxEnnemy.pMaxY);
    list = list->next;
    i++;
  }
}




ennemyList saveEnnemy(int level[100][10][3],ennemyList *ennemy){
  int i=0;
  int j=0;
  int x=-100/2;
  int y=10/2;
  Ennemy *tmp = NULL;
  BoundingBox boxEnnemy;
  // Browse the level array
  while (j<10){
    i=0;
    x=-100/2;
    while (i<100){
      // if green color has been detected, we had an ennemy to the list
      if (level[i][j][0]==0 && level[i][j][1]==255 && level[i][j][2]==0){
        if (*ennemy == NULL){
          *ennemy = allocateEnnemy(x+i-0.5,y-j+0.5,x+i+0.5,y-j-0.5);
          boxEnnemy.pMinX = x+i-0.5;
          boxEnnemy.pMinY = y-j+0.5;
          boxEnnemy.pMaxX = x+i+0.5;
          boxEnnemy.pMaxY = y-j-0.5;
          tmp = *ennemy;
        }
       else{
          while ((*ennemy)->next!=NULL){
            (*ennemy) = (*ennemy)->next;
          }
          (*ennemy)->next = allocateEnnemy(x+i-0.5,y-j+0.5,x+i+0.5,y-j-0.5);
          boxEnnemy.pMinX = x+i-0.5;
          boxEnnemy.pMinY = y-j+0.5;
          boxEnnemy.pMaxX = x+i+0.5;
          boxEnnemy.pMaxY = y-j-0.5;
        }
      }
      i++;
    }
    j++;
  }

  *ennemy = tmp;
  return (*ennemy);
}

int collision_ennemy(BoundingBox vaisseau, ennemyList list){
    while ((list)!=NULL){
      if (vaisseau.pMinX>=(list)->boxEnnemy.pMinX && vaisseau.pMaxX<=(list)->boxEnnemy.pMaxX){
          if ((vaisseau.pMinY<=(list)->boxEnnemy.pMaxY && vaisseau.pMinY>=(list)->boxEnnemy.pMinY)||
              (vaisseau.pMaxY<=(list)->boxEnnemy.pMinY && vaisseau.pMaxY>=(list)->boxEnnemy.pMaxY)){
            return 0;
          }
      }
      (list)=(list)->next;
    }
    return 1;
}


ennemyList updateEnnemy(ennemyList *ennemy,int *ennemyMove){
  Ennemy *tmp = NULL;
  int nb = rand()%3+1;
  // the ennemy translate randomly on the Y axis
  if ((*ennemy) == NULL) return *ennemy;
  tmp = *ennemy;
  while (*ennemy!=NULL){
    if (((*ennemyMove)+nb)%2== 0){
      (*ennemy)->boxEnnemy.pMinY+=0.5;
      (*ennemy)->boxEnnemy.pMaxY+=0.5;
    }
    else{
      (*ennemy)->boxEnnemy.pMinY-=0.5;
      (*ennemy)->boxEnnemy.pMaxY-=0.5;
    }
    (*ennemy) =(*ennemy)->next;
  }
  return tmp;
}

ennemyList freeEnnemy(ennemyList *list){
  // delete and free the ennemy list and return NULL
  if (*list==NULL) return NULL;
  freeEnnemy(&((*list)->next));
  free(*list);
  return NULL;
}

ennemyList deleteEnnemy(ennemyList *list,float x, float y){
  if ((*list)==NULL) return NULL;
  if ((*list)->boxEnnemy.pMinX == x && (*list)->boxEnnemy.pMinY == y){
    ennemyList tmp = (*list)->next;
    free(*list);
    return tmp;
  }
  else{
    (*list)->next = deleteEnnemy(&(*list)->next,x,y);
    return *list;
  }
}

void drawEnnemy(ennemyList list,float speed,GLuint textureID[10]){
  if (list == NULL) return;
  else{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(speed,0,0);
    glScalef(0.1,0.15,0);
    glTranslatef((list)->boxEnnemy.pMaxX,(list)->boxEnnemy.pMaxY+0.25,0);
    //drawRect(0,255,0);
    glColor3ub(255,255,255);
    glScalef(0.5,0.5,0);
    display(textureID[7]);
    glPopMatrix();
    drawEnnemy((list)->next,speed,textureID);
  }
}
