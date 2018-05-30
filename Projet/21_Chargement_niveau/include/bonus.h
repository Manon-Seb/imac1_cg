#ifndef BONUS
#define BONUS

typedef struct bonus{
  float x1;
  float y1;
  float x2;
  float y2;
  struct bonus *next;
}Bonus,*bonusList;

void readBonus(bonusList list);
bonusList allocateBonus(float x1, float y1, float x2, float y2);
bonusList saveBonus(int level[100][10][3],bonusList *bonus);

#endif