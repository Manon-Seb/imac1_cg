#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gameplay.h"


Level initLevel(int nblevel){

  Level newlevel;
  newlevel.level = nblevel;

  if (nblevel == 1){

    newlevel.nb_obstacle = 10;
    newlevel.nb_enemy = 2;
    return newlevel;

  }
  /* A changer quand le nvx 1 marchera
   parfaitement pour créer de nouveaux
  niveaux */

  newlevel.nb_obstacle = 10;
  newlevel.nb_enemy = 2;
  return newlevel;
}


list allocateEnemy(int level){
  /* Allocation */

  Enemy *newEnemy;

  newEnemy = malloc(sizeof*(newEnemy));

  if(newEnemy == NULL)
  {
    printf("NOT ENOUGH MEMORY !\n");
    return NULL;
  }

  /* Initialisation */
  if (level == 1){
    newEnemy->level = 1;
    newEnemy->pv    = 10;
    newEnemy->attack= 1;
    newEnemy->speed = 1;
    newEnemy->next = NULL;
  }

  return newEnemy;
}


Player createPlayer(){
  Player newPlayer;
  newPlayer.pv = 30;
  newPlayer.shield = 0;
  newPlayer.attack = 2;
  newPlayer.speed = 1;
  return newPlayer;
}

void readPlayer(Player name) {
  printf("\n");
  printf("- - - PLAYER ONE STAT - - - \n");
  printf("  PV = %d    SHIELD = %d   \n",name.pv,name.shield);
  printf("  ATTACK = %d   SPEED = %d \n", name.attack,name.speed);
  printf(" - - - - - - - - - - - - - - \n ");
}

void readLevel(Level name) {
  printf("\n");
  printf(" - - - LEVEL STAT - - - \n");
  printf("  LEVEL = %d    nb_obs = %d   \n",name.level,name.nb_obstacle);
  printf("  NB ENNEMY = %d \n", name.nb_enemy);
  printf(" - - - - - - - - - - - - - - \n ");
}

void readEnnemies(list enemylist){
  while (enemylist != NULL){
    printf(" ENEMY ID %d STAT\n",enemylist->level);
    enemylist = enemylist->next;
  }
}

//TODO : freeEnemylist()
