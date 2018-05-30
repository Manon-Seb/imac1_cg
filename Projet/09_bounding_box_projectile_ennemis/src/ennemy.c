#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ennemy.h"

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
  newEnnemy->boxEnnemy.pMinX = x1;
  newEnnemy->boxEnnemy.pMinY = y1;
  newEnnemy->boxEnnemy.pMaxX = x2;
  newEnnemy->boxEnnemy.pMaxY = y2;
  newEnnemy->next = NULL;

  return newEnnemy;
}

void readEnnemy(ennemyList list){
  int i=0;
  printf("--------- ENNEMIES LIST -----------\n");
  while (list != NULL){
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

  while (j<10){
    i=0;
    x=-100/2;
    while (i<100){
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
