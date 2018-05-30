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
  newEnnemy->x1 = 50 + x1;
  newEnnemy->y1 = y1;
  newEnnemy->x2 = 50 + x2;
  newEnnemy->y2= y2;
  newEnnemy->next = NULL;

  return newEnnemy;
}

void readEnnemy(ennemyList list){
  int i=0;
  printf("--------- ENNEMIES LIST -----------\n");
  while (list != NULL){
    printf(" POSITION DE L'ENNEMI %d : (%f,%f)/(%f,%f)\n",i,list->x1,list->y1,list->x2, list->y2);
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

  while (j<10){
    i=0;
    while (i<100){
      if (level[i][j][0]==0 && level[i][j][1]==255 && level[i][j][2]==0){
        if (*ennemy == NULL){
          *ennemy = allocateEnnemy(x+i-0.5,y-j+0.5,x+i+0.5,y-j-0.5);
          tmp = *ennemy;
        }
       else{
          while ((*ennemy)->next!=NULL){
            (*ennemy) = (*ennemy)->next;
          }
          (*ennemy)->next = allocateEnnemy(x+i-0.5,y-j+0.5,x+i+0.5,y-j-0.5);
        }
      }
      i++;
    }
    j++;
  }
  *ennemy = tmp;
  return (*ennemy);
}
