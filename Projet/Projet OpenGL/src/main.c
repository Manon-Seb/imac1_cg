#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gameplay.h"
#include "ppm.h"

/*int main(){*/
/*
  Level easy;
  Player One;
  list enemyList = NULL;

  easy = initLevel(1);
  readLevel(easy);
*/
/* A placer dans la fonction createEnemies

  enemyList = allocateEnemy(1);
  enemyList->next = allocateEnemy(1);
 ---------------------------------------*/
/*
  readEnnemies(enemyList);

  One = createPlayer();
  readPlayer(One);

  return 1;
*/

#include <SDL/SDL.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"

static unsigned int WINDOW_WIDTH = 1024;
static unsigned int WINDOW_HEIGHT = 748;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape();
void setVideoMode();
void drawPlayer();
void drawProjectile();
float transX = 0.0;
float transY = 0.0;
float transZ = 0.0;

int main(int argc, char** argv) {
  /* Game Initialisation */
  Level current;
  list enemyList;
  Player one;

  current = initLevel(1);
  readLevel(current);

  enemyList = allocateEnemy(1);
  enemyList->next = allocateEnemy(1);
  readEnnemies(enemyList);

  one = createPlayer();
  readPlayer(one);

  char *filename = "test.ppm";
  FILE *f = fopen("test.ppm", "r");

  /* Récupération des infos de l'header de l'image */
  Header header = get_header(f);
  /* Affichage des infos (vérif) */
  print_header(header);

  /* On attribue comme largeur et hauteur les valeurs récupérées dans l'header */
  int largeur = header.width;
  int hauteur = header.height;

  /* Je vérifie que les valeurs ont été attribuées */
  printf("%d %d\n", largeur, hauteur);

  int levelarray[largeur][hauteur][3];

  createTab(levelarray,filename);

  /* Game view */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  setVideoMode();
  SDL_WM_SetCaption("FLAPIMAC", NULL);

  /* Si touche reste enfoncée, répète l'action (comme monter et descendre)
  SDL_EnableKeyRepeat(durée, délai) (en millisecondes) */
  SDL_EnableKeyRepeat(10, 50);

  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);
    drawLevel(levelarray);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(0.12,0.12,0.12);
    glColor3ub(255,0,0);
    /* Forme pour vérifier que lorsqu'on déplace le carré, le reste ne bouge pas*/
    glBegin(GL_POLYGON);
      glVertex2f(-0.2,0.2);
      glVertex2f(0.2,0.2);
      glVertex2f(0.2,-0.2);
      glVertex2f(-0.2,-0.2);
    glEnd();
    
    glPushMatrix();
    drawPlayer();
    glPopMatrix();
    

    SDL_GL_SwapBuffers();
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      switch(e.type) {
        case SDL_MOUSEBUTTONUP:
        break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){
            
            case SDLK_q:
              /* Fermeture de la fenêtre */
              loop = 0;

            /* Déplacement du vaisseau */
            case SDLK_UP:
              transY+=1.0;
              break;

            case SDLK_DOWN:
              transY-=1.0;
              break;

            /* Tir de projectile */
            case SDLK_SPACE:
              drawProjectile();
              break;

            default:
              break;
          }
          break;

        /*case SDL_KEYUP:
          switch(e.key.keysym.sym){
            case SDLK_SPACE:

          }
        break;*/

        case SDL_VIDEORESIZE:
          WINDOW_WIDTH = e.resize.w;
          WINDOW_HEIGHT = e.resize.h;
          setVideoMode();
          break;

        default:
          break;
      }
    }

    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }


  SDL_Quit();
  fclose(f);
  return EXIT_SUCCESS;
}

/*void reshape() {
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
}*/

void drawPlayer(){
  glTranslatef(transX,transY,transZ);
  glBegin(GL_POLYGON);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glVertex2f(-0.5,-0.5);
  glEnd();
}

void drawProjectile(){
  glColor3ub(255,255,0);
  glBegin(GL_LINES);
    glVertex2f(0.5,0.0);
    glVertex2f(0.8,0.0);
  glEnd();
}
