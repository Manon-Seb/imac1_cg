#ifndef RULES
#define RULES

int w_rules,h_rules;
int createTabWindow(int levelarray[w_rules][h_rules][3],char *filename);
void drawRectRules(int R, int V, int B);
void drawRules(int level[w_rules][h_rules][3]);

#endif