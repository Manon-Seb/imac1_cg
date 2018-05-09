#ifndef GAMEPLAY
#define GAMEPLAY 50

typedef struct player{
  int pv;
  int shield;
  int attack;
  int speed;
}Player;

typedef struct enemy{
  int id;
  int level;
  int pv;
  int attack;
  int speed;
  struct enemy *next;
}Enemy,*list;

typedef struct level{
  int level;
  int nb_obstacle;
  int nb_enemy;
}Level;

Level initLevel(int nblevel);
list allocateEnemy(int level);
Enemy * createEnemies(Level name);
Player createPlayer();
void readPlayer(Player name);
void readLevel(Level name);
void readEnnemies(list enemylist);
#endif
