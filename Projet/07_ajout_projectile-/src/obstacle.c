#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "obstacle.h"

obsList allocateObs(float x1, float y1, float x2, float y2){
  /* Allocation */
  Obstacle *newObstacle;
  newObstacle= malloc(sizeof*(newObstacle));

  if(newObstacle == NULL)
  {
    printf("NOT ENOUGH MEMORY !\n");
    return NULL;
  }

  /* Initialisation */
  newObstacle->x1 = x1;
  newObstacle->y1 = y1;
  newObstacle->x2 = x2;
  newObstacle->y2 = y2;
  newObstacle->next = NULL;

  return newObstacle;
}

void readObstacle(obsList list){
  int i=0;
  printf("--------- OBSTACLES LIST -----------\n");
  while (list != NULL){
    printf(" POSITION DE L'OBSTACLE %d : (%f,%f)/(%f,%f)\n",i,list->x1,list->y1,list->x2,list->y2);
    list = list->next;
    i++;
  }
}



obsList saveObstacle(int level[16][8][3],obsList *obstacle){
  int i=0;
  int j=0;
  int x=-16/2;
  int y=8/2;
  Obstacle *tmp = NULL;

  while (j<8){
    i=0;
    x=-16/2;
    while (i<16){
      if (level[i][j][0]==255 && level[i][j][1]==0 && level[i][j][2]==0){
        if (*obstacle == NULL){
          *obstacle = allocateObs(x+i-05,y-j+0.5,x+i+0.5,y-j-0.5);
          tmp = *obstacle;
        }
       else{
          while ((*obstacle)->next!=NULL){
            (*obstacle) = (*obstacle)->next;
          }
          (*obstacle)->next = allocateObs(x+i-05,y-j+0.5,x+i+0.5,y-j-0.5);

        }
      }
      i++;
    }
    j++;
  }
  *obstacle = tmp;
  return (*obstacle);
}
