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
  newObstacle->boxObstacle.pMinX = x1;
  newObstacle->boxObstacle.pMinY = y1;
  newObstacle->boxObstacle.pMaxX = x2;
  newObstacle->boxObstacle.pMaxY = y2;
  newObstacle->next = NULL;

  return newObstacle;
}

void readObstacle(obsList list){
  int i=0;
  printf("--------- OBSTACLES LIST -----------\n");
  while (list != NULL){
    printf(" POSITION DE L'OBSTACLE %d : (%f,%f)/(%f,%f)\n",i,list->boxObstacle.pMinX,list->boxObstacle.pMinY,list->boxObstacle.pMaxX,list->boxObstacle.pMaxY);
    list = list->next;
    i++;
  }
}



obsList saveObstacle(int level[100][10][3],obsList *obstacle){
  int i=0;
  int j=0;
  int x=-100/2;
  int y=10/2;
  Obstacle *tmp = NULL;
  BoundingBox boxObstacle;

  while (j<10){
    i=0;
    x=-100/2;
    while (i<100){
      if (level[i][j][0]==255 && level[i][j][1]==0 && level[i][j][2]==0){
        if (*obstacle == NULL){
          *obstacle = allocateObs(x+i-0.5,y-j+0.5,x+i+0.5,y-j-0.5);
          boxObstacle.pMinX = x+i-0.5;
          boxObstacle.pMinY = y-j+0.5;
          boxObstacle.pMaxX = x+i+0.5;
          boxObstacle.pMaxY = y-j-0.5;
          tmp = *obstacle;
        }
       else{
          while ((*obstacle)->next!=NULL){
            (*obstacle) = (*obstacle)->next;
          }
          (*obstacle)->next = allocateObs(x+i-0.5,y-j+0.5,x+i+0.5,y-j-0.5);
          boxObstacle.pMinX = x+i-0.5;
          boxObstacle.pMinY = y-j+0.5;
          boxObstacle.pMaxX = x+i+0.5;
          boxObstacle.pMaxY = y-j-0.5;
        }
      }
      i++;
    }
    j++;
  }
  *obstacle = tmp;
  return (*obstacle);
}
