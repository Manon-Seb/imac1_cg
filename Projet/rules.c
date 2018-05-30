#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <assert.h>
#include "rules.h"

#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

static unsigned int WINDOW_WIDTH = 1600;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int w_rules=1024, h_rules=748;

/* [3] = RVB*/


/* Sauvegarde du fichier  ppm dans un tableau */
int createTabWindow(int levelarray[w_rules][h_rules][3],char *filename){
      FILE* fichier = NULL;
      int caractereActuel = 0;
      int i=0;
      int j=0;
      int cursor = 40; 

      int width = 0;
      int height = 0;
      int RVB = 0;
      int nbpixel=0;

      char copy[3];

      fichier = fopen(filename, "r");
      fseek(fichier,cursor,SEEK_CUR);
      if (fichier != NULL)
      {
          // Boucle de lecture des caractères un à un
          do
          {
              caractereActuel = fgetc(fichier); // On lit le caractère
              if (caractereActuel == '\n' || caractereActuel == ' '){
                i ++;
                if (i%3 == 0){
                  nbpixel++;
                }
                levelarray[width][height][RVB] = atoi(copy);
                copy[0]=' ';
                copy[1]=' ';
                copy[2]=' ';
                //printf("%d",levelarray[width][height][RVB]);
                j=0;
                RVB ++;
                if (RVB == 3){
                  RVB = 0;
                  width ++;
                  if (width == w_rules){
                    width = 0;
                    height ++;
                    if (height == h_rules){
                      return 1;
                    }
                  }
                }
              }
              else{
                copy[j] = caractereActuel;
                j++;
              }
          } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)

          fclose(fichier);
      }

      return 0;
  }

  void drawRectRules(int R, int V, int B){
  glColor3ub(R,V,B);

  glBegin(GL_POLYGON);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glVertex2f(-0.5,-0.5);
  glEnd();

}

void drawRules(int tab[w_rules][h_rules][3]){
  int i=0;
  int j=0;


  while (j<h_rules){
    i=0;
    //x=-w/2;
    while (i<w_rules){
      if (tab[i][j][0]== 255 && tab[i][j][1]== 255 && tab[i][j][2]== 255){
        i++;
      }
      else{
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        //glScalef(0.1,0.15,0);
        //glTranslatef(x+i,y-j,0);
        drawRectRules(tab[i][j][0],tab[i][j][1],tab[i][j][2]);
        glPopMatrix();
        i++;
      }
    }
    j++;
  }
}
