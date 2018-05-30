/*******************************************************
Nom ......... : main.c
Role ........ : FLAPIMAC is a game where the goal is to avoid obstacles and
                ennemies.
Auteur ...... : SEBAOUN Manon & SEMINEL Marion

Compilation :
make
To execute, write : ./bin/flapimac
********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <assert.h>

#include "texture.h"
#include "displayGame.h"
#include "ppm.h"
#include "projectile.h"
#include "obstacle.h"
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
    printf("ERROR :image can't be found");
  }
  /* Get information from the image header */
  Header header = get_header(f);
  int largeur = header.width;
  int hauteur = header.height;

/*** INITIALISATION FROM THE LEVEL *********************************************/
  int levelarray[largeur][hauteur][3];
  obsList obstacle;
  ennemyList ennemy;
  createTab(levelarray,filename2);
  saveObstacle(levelarray,&obstacle);
  saveEnnemy(levelarray,&ennemy);

  /*** Game view **************************************************************/
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL can't be initialize. End of the programm.\n");
    return EXIT_FAILURE;
  }


  setVideoMode();
  SDL_WM_SetCaption("FLAPIMAC", NULL);

  /*** MUSIC ******************************************************************/
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
    printf("%s\n", Mix_GetError());
  }
  /* Music volume */
  Mix_VolumeMusic(MIX_MAX_VOLUME);
  Mix_Music *mainMusic;
  /* MP3 file */
  mainMusic = Mix_LoadMUS("Space_Zone.mp3");
  Mix_PlayMusic(mainMusic, -1);

  /* Repeat action if a key stays down */
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
      // Background texture
    glColor3ub(255,255,255);
    display(textureID[0]);
      // Call display game which will update and draw the different elements
    speed = displayGame(transY_,speed,transX,transY,transZ,&projectile,&playerBB,
      obstacle,levelarray,&ennemy,&ennemyMove,&projectileEnnemy,textureID);
    transY_ = 0;
      // Check the different collision
    if (projectile!=NULL){
      // if a collision is detected the projectile is deleted
      collision_projectile_obstacle(&projectile,obstacle);
      // if a collision is detected the ennemy is deleted
      collision_projectile_ennemy(&projectile,&ennemy);
    }
    if (projectileEnnemy!=NULL){
      collision_ennemyprojectile_obstacle(&projectileEnnemy,obstacle);
      if(collision_projectileennemy_vaisseau(playerBB,projectileEnnemy)==0){
        // if the player is shot by an ennemy shapeship, it's game over */
        speed = 0;
      }
    }
    /*** GAME OVER ***/
    if (speed == 0){
      // if the game is lost, we reinitialize the game
      BoundingBox newGame;
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
      mode = 3;
    }
    if (speed == 4){
      // if the game is win, we reinitialize the game
      speed = 0;
      BoundingBox newGame;
      transY_ =0;
      transX = 0;
      transY = 0;
      transZ = 0;
      projectile = freeProjectile(&projectile);
      projectile = NULL;
      freeEnnemy(&ennemy);
      ennemy = NULL;
      freeObstacle(&obstacle);
      obstacle = NULL;
      playerBB = newGame;
      temps = clock();
      printf("Score: %f\n",(double) temps/CLOCKS_PER_SEC);
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
            // button which allow to choose the game mode
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
              // if a level is win, the player can
            if (e.button.x > 563 && e.button.x<1036){
              if (e.button.y > 324 && e.button.y < 437){
                currentlevel ++;
                // Play the next level
                if (currentlevel==2){
                  createTab(levelarray,filename2);
                  saveObstacle(levelarray,&obstacle);
                  saveEnnemy(levelarray,&ennemy);
                  mode = 1;
                }
                if (currentlevel==3){
                  createTab(levelarray,filename3);
                  saveObstacle(levelarray,&obstacle);
                  ennemy = saveEnnemy(levelarray,&ennemy);
                  mode = 1;
                }
              }
              if (e.button.y > 485 && e.button.y < 596){
                // Replay the actual level;
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
                  ennemy = saveEnnemy(levelarray,&ennemy);
                  mode = 1;
                }
                mode = 1;
              }
              if (e.button.y > 646 && e.button.y < 756){
                // button which alow to quit the programm
                loop = 0;
              }
            }
          }
        break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){

            case SDLK_q:
              /* Close the window */
              loop = 0;

            /* To move the spaceship */
            case SDLK_UP:

              /* To prevent the player from going out of the screen */
              if(transY > 4.0){
              transY+=0.0;
              transY_=0.0;
              }
              else{
                transY+=1.0;
                transY_ = 1;
              }

              break;

            case SDLK_DOWN:

              if(transY < -4.0){
                transY+=0.0;
                transY_=0.0;
              }
              else{
                transY-=1.0;
                transY_ = -1;
              }
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
              /* To shoot projectiles */
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

  Mix_FreeMusic(mainMusic);
  Mix_CloseAudio();
   // Liberation des ressources associées à la SDL
  SDL_Quit();
  fclose(f);
  return EXIT_SUCCESS;
}
