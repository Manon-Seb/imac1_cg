#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "displayPPM.h"

#define BUF_SZ 70

/**
  Intermediate function called by parse_pgma().
  Copies the given string into the appropriate 
  field in the given pgma structure.
  Also allocates the memory needed to store
  each pixel value in the structure,
  which must be freed by free_pgma().
*/
static int state = 0;
void parse_pgma_field(pgma_t* pgma, char* field) {  
  static int row, col;
  
  //printf(stderr, "state = %d. i = %d, j = %d. field = '%s'\n", state, i, j, field);
  
  if (strlen(field) <= 0) {
    return;
  }
  
  switch(state) { 
  case 0: // start of file;
    /*if (strcmp(field, "P2") == 0) {
      pgma->type = 2;
    } else */
      if (strcmp(field, "P3") == 0) {
      pgma->type = 3;
    } else {
      fprintf(stderr, "Input file not PGMA or PPM!\n"); 
      exit(1); 
    }
    ++state;
    break; 
  case 1: //width
    /* Fonction atoi retourne valeur numérique représentée par le char comme int
    conversion de char vers int */
    pgma->width = atoi(field); 
    ++state;
    break;
  case 2: //height. 
    pgma->height = atoi(field); 
    pgma->size = pgma->width * pgma->height;
    // at this point we can create the array for the pixels 
    pgma->pixels = (GLuint*)malloc(3 * sizeof(GLuint) * pgma->size);
    row = pgma->height - 1;
    col = 0;
    ++state;
    break;
  case 3: //max_level
    pgma->max_level = atoi(field);
    pgma->scale = 255.0 / pgma->max_level;
    ++state;
    break;
  case 4: // red component of pixel
    pgma->pixels[3*(row*pgma->width + col)] = atoi(field);
    /*if (pgma->type == 2) {
      pgma->pixels[3*(row*pgma->width + col)+1] = atoi(field);
      pgma->pixels[3*(row*pgma->width + col)+2] = atoi(field); 
      if(++col >= pgma->width) {
        row -= 1;
        col = 0;
      }
    }*/ if (pgma->type == 3) { // type == 3
      ++state;
    }
    break;
  case 5: // green component of pixel
    pgma->pixels[3*(row*pgma->width + col)+1] = atoi(field);
    ++state;
    break;
  case 6: // blue component of pixel
    pgma->pixels[3*(row*pgma->width + col)+2] = atoi(field);
    if(++col >= pgma->width) {
      row -= 1;
      col = 0;
    }
    state = 4;
    break;
  }
  
}

/**
  Reads pgma image data from the given FILE stream
  and populates the given pgma structure with it.
*/
void parse_pgma(pgma_t* pgma, FILE* file) {
  // read from file into struct
  
  int cnt = 0, len = 0;
  char buf[1 + 1], field[BUF_SZ + 1];
  
  state = 0;
  while(fgets(buf, 2, file)) {
    // if (cnt++ % 100 * 1024 == 0) {
    //   fprintf(stderr, "read %d bytes.\n", cnt);
    // }
    
    if (isspace(*buf) || *buf == '#') {
      //skip comments
      if (*buf == '#') {
        // fprintf(stderr, "got comment.\n");
        while(fgets(buf, 2, file) && *buf != '\n');
      }
      // fprintf(stderr, "got field: '%*.*s'\n", len, len, field);
      
      // parse field, then clear buffer for next field
      field[len] = 0;
      parse_pgma_field(pgma, field);
      len = 0;
      
    } else {
      field[len++] = *buf;
      if (len == BUF_SZ) {
        fprintf(stderr, "Read more than 70 bytes: '%*.*s", BUF_SZ, BUF_SZ, field);
        exit(1);
      }
    }
  }
  
  //eof. parse last field, if any
  field[len] = 0;
  parse_pgma_field(pgma, field);

  fprintf(stderr, "EOF. read %d bytes.\n", cnt);
  
}

/**
  Frees the memory allocated by parse_pgma() to
  store each pixel value in the image data.
*/
void free_pgma(pgma_t* pgma) {
  free(pgma->pixels);
}

/* Affichage de l'image */
void display(void)
{
  //glClear(GL_COLOR_BUFFER_BIT);
  
  //glRasterPos2i(0,0);
  glDrawPixels(pgma.width, pgma.height, GL_RGB, GL_UNSIGNED_INT, pgma.pixels);

  glFlush();
  printf("finished display \n");
}

/* Redimension */
void myreshape(int h, int w)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, (GLfloat) pgma.width, 0.0, (GLfloat) pgma.height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0,0,h,w);
}

/**
  Read a pgma image from the given file, process the data,
  write the distortion and rate to stdout and
  write the encoded, reconstructed, and error images back out to new files.
*/
/*int main(int argc, char **argv) {
  FILE *infile;
  char *fileName = "Level_1.ppm";
  printf("%s\n", fileName);
  
  printf("Displaying image from %s\n", &fileName[0]);
  
  // parse pgma from infile
  infile = fopen(&fileName[0], "r");
  parse_pgma(&pgma, infile);
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
  glutInitWindowSize(pgma.width, pgma.height);
  glutInitWindowPosition(0,0);
  glutCreateWindow("image");
  glutReshapeFunc(myreshape);
  glutDisplayFunc(display);
  glPixelTransferf(GL_RED_SCALE, pgma.scale);
  glPixelTransferf(GL_GREEN_SCALE, pgma.scale);
  glPixelTransferf(GL_BLUE_SCALE, pgma.scale);
  glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glutMainLoop();
  
  return 0;
}*/