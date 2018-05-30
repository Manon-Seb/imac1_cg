#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

#include "texture.h"
#include "displayGame.h"
#include "gameplay.h"
#include "ppm.h"
#include "projectile.h"
#include "obstacle.h"
#include "list.h"
#include "collision.h"
#include "Menu.h"
#include "ennemy.h"
#include "rules.h"

static unsigned int WINDOW_WIDTH = 1024;
static unsigned int WINDOW_HEIGHT = 748;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;



void reshape();
void setVideoMode();

float transX = 0.0;
float transY = 0.0;
float transY_ = 0.0;
float transZ = 0.0;
float speed = 0.0;
BoundingBox playerBB;

int main(int argc, char** argv) {
  /* Temps */
  clock_t temps;
  srand(time(NULL));
  /* Int qui sert au deplacement des ennemy */
  int ennemyMove = 0;
  /* Game Initialisation */
  int currentlevel = 1;
  PList projectile = NULL;
  PList projectileEnnemy = NULL;



  char *filename1 = "level_1.ppm";
  char *filename2 = "level_2.ppm";
  char *filename3 = "level_3.ppm";

  FILE *f = fopen("level_1.ppm", "r");
  if (f == NULL){
    printf("ERREUR : chargement img");
  }
  /* Récupération des infos de l'header de l'image */
  Header header = get_header(f);
  /* Affichage des infos (vérif) */
  //print_header(header);
  /* On attribue comme largeur et hauteur les valeurs récupérées dans l'header */
  int largeur = header.width;
  int hauteur = header.height;

  /* Je vérifie que les valeurs ont été attribuées */
  //printf("%d %d\n", largeur, hauteur);

  int levelarray[largeur][hauteur][3];
  obsList obstacle;
  ennemyList ennemy;
  createTab(levelarray,filename1);
  saveObstacle(levelarray,&obstacle);
  saveEnnemy(levelarray,&ennemy);

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

/*TEXTURE ********************************************************************/
  GLuint textureID[10];
  textureID[0]=loadTexture("FLAP_Level_1_BG.jpg");
  textureID[1]=loadTexture("FLAPIMAC.jpg");
  textureID[2]=loadTexture("FLAPIMAC_GO.jpg");
  textureID[3]=loadTexture("Rules.jpg");
  textureID[4]=loadTexture("texture_obstacle.jpg");
  textureID[5]=loadTextureTransparency("vaisseau.png");
  textureID[6]=loadTextureTransparency("projectile.png");
  textureID[7]=loadTextureTransparency("alien_spaceship.png");
  textureID[8]=loadTexture("FLAP_YOU_WIN.jpg");
/*****************************************************************************/
  int loop = 1;
  int mode = 0;

  while(loop) {
    Uint32 startTime = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);

  if (mode == 0){
    /*** MENU ****/

    displayMenu(textureID[1]);
  }
  if (mode == 1){
    /*** GAME ***/
    /**** image de background ****/
    //glColor3ub(255,255,255);
    //display(textureID[0]);
    speed = displayGame(transY_,speed,transX,transY,transZ,&projectile,&playerBB,
      obstacle,levelarray,&ennemy,&ennemyMove,&projectileEnnemy,textureID);
    transY_ = 0;
    if (projectile!=NULL){
      if(collision_projectile_obstacle(&projectile,obstacle)==0){
        printf("COLLISION W/ OBSTACLE");
      }
      if(collision_projectile_ennemy(&projectile,&ennemy)==0){
        printf("COLLISION W/ ENNEMY ");
      }
    }
    /*** GAME OVER ***/
    if (speed == 0){
      BoundingBox newGame;
      mode = 3;
      transY_ =0;
      transX = 0;
      transY = 0;
      transZ = 0;
      projectile = freeProjectile(&projectile);
      projectile = NULL;
      freeEnnemy(&ennemy);
      ennemy = NULL;
      saveEnnemy(levelarray,&ennemy);
      playerBB = newGame;
      temps = clock();
      printf("High Score: %f\n",(double) temps/CLOCKS_PER_SEC);
    }
    if (speed == 4){
      speed = 0;
      BoundingBox newGame;
      mode = 3;
      transY_ =0;
      transX = 0;
      transY = 0;
      transZ = 0;
      projectile = freeProjectile(&projectile);
      projectile = NULL;
      freeEnnemy(&ennemy);
      ennemy = NULL;
      saveEnnemy(levelarray,&ennemy);
      freeObstacle(&obstacle);
      obstacle = NULL;
      playerBB = newGame;
      temps = clock();
      printf("High Score: %f\n",(double) temps/CLOCKS_PER_SEC);
      mode = 4;
    }
  }
  if (mode == 2){
    /**** RULES & COMMAND *****/
    displayRules();
  }
  if (mode == 3){
    /*** GAME OVER ****/
    displayGameOver();
  }
  if (mode ==4){
    /**** YOU WIN !***/
    displayMenu(textureID[8]);
  }

    SDL_GL_SwapBuffers();
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      switch(e.type) {
        case SDL_MOUSEBUTTONDOWN:
          if (mode == 0 || mode == 3){
            if (e.button.x > 563 && e.button.x<1036){
              if (e.button.y > 324 && e.button.y < 437){
                mode = 1;
              }
              if (e.button.y > 485 && e.button.y < 596){
                mode = 2;
              }
              if (e.button.y > 646 && e.button.y < 756){
                loop = 0;
              }
            }
          }
          if (mode == 4){
            if (e.button.x > 563 && e.button.x<1036){
              if (e.button.y > 324 && e.button.y < 437){
                currentlevel ++;
                if (currentlevel==2){
                  createTab(levelarray,filename2);
                  saveObstacle(levelarray,&obstacle);
                  saveEnnemy(levelarray,&ennemy);
                  mode = 1;
                }
                if (currentlevel==3){
                  createTab(levelarray,filename3);
                  saveObstacle(levelarray,&obstacle);
                  saveEnnemy(levelarray,&ennemy);
                  mode = 1;
                }
              }
              if (e.button.y > 485 && e.button.y < 596){
                mode = 1;
                if (currentlevel==1){
                  createTab(levelarray,filename1);
                  saveObstacle(levelarray,&obstacle);
                  saveEnnemy(levelarray,&ennemy);
                  mode = 1;
                }
                if (currentlevel==2){
                  createTab(levelarray,filename2);
                  saveObstacle(levelarray,&obstacle);
                  saveEnnemy(levelarray,&ennemy);
                  mode = 1;
                }
                if (currentlevel==3){
                  createTab(levelarray,filename3);
                  saveObstacle(levelarray,&obstacle);
                  saveEnnemy(levelarray,&ennemy);
                  mode = 1;
                }
              }
              if (e.button.y > 646 && e.button.y < 756){
                loop = 0;
              }
            }
          }
        break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){

            case SDLK_q:
              /* Fermeture de la fenêtre */
              loop = 0;

            /* Déplacement du vaisseau */
            case SDLK_UP:
              transY+=1.0;
              transY_ = 1;
              break;

            case SDLK_DOWN:
              transY-=1.0;
              transY_ = -1;
              break;
             case SDLK_RETURN:
             if (mode == 2){
               mode = 0;
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
                projectile = addProjectile(playerBB.pMaxX,playerBB.pMaxY,&projectile);
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

  ennemy=freeEnnemy(&ennemy);
  obstacle=freeObstacle(&obstacle);
  int i=0;
   while (i<=6){
     glDeleteTextures(1,&textureID[i]);
     i++;
   }

   // Liberation des ressources associées à la SDL
  SDL_Quit();
  fclose(f);
  return EXIT_SUCCESS;
}
