#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bonus.h"

bonusList allocateBonus(float x1, float y1, float x2, float y2){
  /* Allocation */
  Bonus *newBonus;
  newBonus= malloc(sizeof*(newBonus));

  if(newBonus == NULL)
  {
    printf("NOT ENOUGH MEMORY !\n");
    return NULL;
  }

  /* Initialisation */
  newBonus->x1 = 50 + x1;
  newBonus->y1 = y1;
  newBonus->x2 = 50 + x2;
  newBonus->y2 = y2;
  newBonus->next = NULL;

  return newBonus;
}

void readBonus(bonusList list){
  int i=0;
  printf("--------- BONUS LIST -----------\n");
  while (list != NULL){
    printf(" POSITION DU BONUS %d : (%f,%f)/(%f,%f)\n",i,list->x1,list->y1,list->x2,list->y2);
    list = list->next;
    i++;
  }
}



bonusList saveBonus(int level[100][10][3],bonusList *bonus){
  int i=0;
  int j=0;
  int x=-100/2;
  int y=10/2;
  Bonus *tmp = NULL;

  while (j<10){
    i=0;
    while (i<100){
      if (level[i][j][0]==0 && level[i][j][1]==0 && level[i][j][2]==255){
        if (*bonus == NULL){
          *bonus = allocateBonus(x+i-0.5,y-j+0.5,x+i+0.5,y-j-0.5);
          tmp = *bonus;
        }
       else{
          while ((*bonus)->next!=NULL){
            (*bonus) = (*bonus)->next;
          }
          (*bonus)->next = allocateBonus(x+i-0.5,y-j+0.5,x+i+0.5,y-j-0.5);

        }
      }
      i++;
    }
    j++;
  }
  *bonus = tmp;
  return (*bonus);
}