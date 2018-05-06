#ifndef DISPLAYPPM
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
/**
  Structure for holding information about the PGMA file.
*/
typedef struct _pgma_t {
  int type; // 2 = PGMA. 3 = PPM
  int width; 
  int height;
  int size; // width * height
  int max_level;
  float scale;
  GLuint *pixels;
} pgma_t;

pgma_t pgma;

void parse_pgma_field(pgma_t* pgma, char* field);
void parse_pgma(pgma_t* pgma, FILE* file);
void free_pgma(pgma_t* pgma);
/* Affichage de l'image */
void display(void);
/* redimension */
void myreshape(int h, int w);

#endif