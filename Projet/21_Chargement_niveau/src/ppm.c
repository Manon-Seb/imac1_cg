#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <assert.h>
#include "ppm.h"

#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#define is_sep(c) (c == ' ' || c == '\t' || c == '\n' || c == EOF) /* définition de tous les séparateurs */
#define acces_pixel(e,w,i,j) (*((unsigned int *)e->pixels + w * i + j))

static unsigned int WINDOW_WIDTH = 1600;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/* Ces deux variables posent problème : il faudrait voir pour qu'on ne nous n'ayons pas
à leur attribuer une valeur à la main. Il faudrait, comme dans le main, qu'elles se voient
attribuer les valeurs largeur/hauteur de l'en-tête */
int w=100, h=10;



unsigned char next_char(FILE * f)
{
    char tmp;
    tmp = fgetc(f);
    while (is_sep(tmp)) // on ignore les séparateurs
        tmp = fgetc(f);
    while (tmp == '#') {    // on ignore les commentaires
        while (tmp != '\n')
            tmp = fgetc(f);
        tmp = fgetc(f);
    }
    return tmp;
}

unsigned int next_int(FILE * f) // retourne l'int suivant si nous sommes en P3
{
    unsigned int res = 0;
    char tmp;
    tmp = next_char(f);
    while (!is_sep(tmp)) {
        res = res * 10 + tmp - '0';
        tmp = fgetc(f);
    }
    return res;
}

/* Lecture et stockage des informations de l'header du fichier
Rappel de la structure de l'header :

Nombre magique
Largeur Hauteur
Valeur max de couleur (255 en P3) */
Header get_header(FILE * f) // retourne l'header
{
    Header head;
    /* Format = P3 dans notre cas */
    head.format[0] = fgetc(f);
    head.format[1] = fgetc(f);
    head.width = next_int(f);
    head.height = next_int(f);
    head.max_color = next_int(f);
    return head;
}

/* Pour vérifier les valeurs récupérées */
void print_header(Header head)
{
    printf("#########################\n");
    printf("# Format    : %c%c\t#\n",head.format[0],head.format[1]);
    printf("# Largeur   : %d \t#\n",head.width);
    printf("# Hauteur   : %d \t#\n",head.height);
    printf("# Max color : %d \t#\n",head.max_color);
    printf("#########################\n");
}

void reshape() {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1., 1., -1., 1.);
}

void setVideoMode() {
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape();
}

void drawRepere(){

  glBegin(GL_LINES);
  glVertex2f(-0.5,0);
  glVertex2f(0.5,0);
  glEnd();
  glColor3ub(0,255,0);
  glBegin(GL_LINES);
  glVertex2f(0,0.5);
  glVertex2f(0,-0.5);
  glEnd();
}

void drawRect(int R, int V, int B){
  glColor3ub(R,V,B);

  glBegin(GL_POLYGON);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glVertex2f(-0.5,-0.5);
  glEnd();

}

/* [3] = RVB*/


/* Sauvegarde du fichier  ppm dans un tableau */
int createTab(int levelarray[w][h][3],char *filename){
      FILE* fichier = NULL;
      int caractereActuel = 0;
      int i=0;
      int j=0;
      int cursor = 40; // faire une fonctin pour trouver où le placer automatiquement

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
                  if (width == w){
                    width = 0;
                    height ++;
                    if (height == h){
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

// Je choisis que 1 pixel ppm = 10 pixel
