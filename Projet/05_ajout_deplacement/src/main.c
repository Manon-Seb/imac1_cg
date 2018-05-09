#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

#include "gameplay.h"
#include "ppm.h"
#include "projectile.h"
#include "obstacle.h"
#include "list.h"
#include "collision.h"

static unsigned int WINDOW_WIDTH = 1024;
static unsigned int WINDOW_HEIGHT = 748;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape();
void setVideoMode();
void drawPlayer();
int KeyHit();

float transX = 0.0;
float transY = 0.0;
float transZ = 0.0;
float speed = 0.0;

int main(int argc, char** argv) {
  /* Game Initialisation */
  //Level current;
  //list enemyList;
  Player one;
  PList projectile = NULL;
  //current = initLevel(1);
  //readLevel(current);

  //enemyList = allocateEnemy(1);
  //enemyList->next = allocateEnemy(1);
  //readEnnemies(enemyList);

  one = createPlayer();
  readPlayer(one);

  char *filename = "New_level_1.ppm";
  FILE *f = fopen("New_level_1.ppm", "r");

  /* Récupération des infos de l'header de l'image */
  Header header = get_header(f);
  /* Affichage des infos (vérif) */
  // print_header(header);

  /* On attribue comme largeur et hauteur les valeurs récupérées dans l'header */
  int largeur = header.width;
  int hauteur = header.height;

  /* Je vérifie que les valeurs ont été attribuées */
  //printf("%d %d\n", largeur, hauteur);

  int levelarray[largeur][hauteur][3];
  createTab(levelarray,filename);

  /* Liste chaînée des obstacles */
  obsList obstaclesList;
  obstaclesList = saveObstacle(levelarray, &obstaclesList);
  readObstacle(obstaclesList);


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

/*** Animation / vitesse des élement ***/
  /*** vitesse du level */
    speed -= 0.005;
    if (speed < -11){
      loop = 0;
    }
  /*** Projectile ***/
  projectile=updateProjectile(&projectile);
  //ReadProjectile(projectile);
/*** Dessin des éléments ***/

    Uint32 startTime = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    drawLevel(levelarray);

    glPopMatrix();

    drawProjectile(projectile,speed);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(0.12,0.12,0.12);
    glColor3ub(255,0,0);
    glPushMatrix();
    drawPlayer();
    /* Bpunding box */
    BoundingBox playerBB = calculateBoundingBox();
    drawBoundingBox(playerBB);
    glPopMatrix();

    int touched = collision(playerBB, obstaclesList->boxObstacle);
    if(touched == 1){
      printf("AIE\n");
    }

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
              if(one.posY > WINDOW_HEIGHT/106){
                transY+=0.0;
              }
              else{
                one.posY+=1.0;
                transY+=1.0;
              }
              break;

            case SDLK_DOWN:
              if(one.posY < -7.0){
              transY+=0.0;
              }
              else{
                one.posY-=1.0;
                transY-=1.0;
              }
              break;

            default:
              break;
          }
          break;

          case SDL_KEYUP:
            switch(e.key.keysym.sym){
              /* Tir de projectile */
              case SDLK_SPACE:
                projectile = addProjectile(-speed,transY,&projectile);
                break;

              default:
                break;
            }
            break;


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

int KeyHit()
{
  SDL_Event e;
  if (SDL_PollEvent(&e))
    if (e.type == SDL_KEYDOWN)
      return 1;
  return 0;
}

void drawLevel(int level[w][h][3]){
  int i=0;
  int j=0;
  int x=0;
  int y=h/2;


  while (j<h){
    i=0;
    //x=-w/2;
    while (i<w){
      if (level[i][j][0]== 255 && level[i][j][1]== 255 && level[i][j][2]== 255){
        i++;
      }
      else{
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(speed,0,0);
        glScalef(0.1,0.25,0);
        glTranslatef(x+i,y-j,0);
        drawRect(level[i][j][0],level[i][j][1],level[i][j][2]);
        glPopMatrix();
        i++;
      }
    }
    j++;
  }
}

void drawPlayer(){
  glTranslatef(transX,transY,transZ);
  glBegin(GL_POLYGON);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glVertex2f(-0.5,-0.5);
  glEnd();
}