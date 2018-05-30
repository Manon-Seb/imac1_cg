#ifndef BONUS
#define BONUS

typedef struct bonus{
  // minimum point
  float x1;
  float y1;
  // maximum point
  float x2;
  float y2;
  struct bonus *next;
}Bonus,*bonusList;


void readBonus(bonusList list);
  /* Fonction which allow to read Bonus' coordonate */
bonusList allocateBonus(float x1, float y1, float x2, float y2);
  /* Fonction which allocate and initialize a Bonus structure */
bonusList saveBonus(int level[100][10][3],bonusList *bonus);
  /* Browse level array and create a bonus chained list */

#endif
