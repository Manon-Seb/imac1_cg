#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL_mixer/SDL_mixer.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#include <SDL_image/SDL_image.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SDL/SDL_image.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "gameplay.h"
#include "ppm.h"
#include "projectile.h"
#include "obstacle.h"
#include "ennemy.h"
#include "bonus.h"
#include "list.h"
#include "collision.h"
#include "Menu.h"

static unsigned int WINDOW_WIDTH = 1600;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape();
void setVideoMode();
void drawPlayer();
int KeyHit();

int w,h;
float transX = 0.0;
float transY = 0.0;
float transY_ = 0.0;
float transZ = 0.0;
float speed = 0.0;
BoundingBox playerBB;

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

  char *filename = "level_3.ppm";
  FILE *f = fopen("level_3.ppm", "r");

  if (f == NULL){
    printf("ERREUR : chargement img");
  }
  /* Récupération des infos de l'header de l'image */
  Header header = get_header(f);

  /* On attribue comme largeur et hauteur les valeurs récupérées dans l'header */
  int largeur = header.width;
  int hauteur = header.height;

  int levelarray[largeur][hauteur][3];
  obsList obstacle;
  createTab(levelarray,filename);
  obstacle = saveObstacle(levelarray,&obstacle);
  //readObstacle(obstacle);

  ennemyList ennemies;
  ennemies = saveEnnemy(levelarray, &ennemies);
  //readEnnemy(ennemies);

  bonusList bonus;
  bonus = saveBonus(levelarray, &bonus);
  readBonus(bonus);

  /* Game view */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }


  setVideoMode();
  SDL_WM_SetCaption("FLAPIMAC", NULL);

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
    printf("%s\n", Mix_GetError());
  }
  Mix_Music *music;
  music = Mix_LoadMUS("Phantastic_Journey.mp3");
  Mix_PlayMusic(music, -1);

  /* Si touche reste enfoncée, répète l'action (comme monter et descendre)
  SDL_EnableKeyRepeat(durée, délai) (en millisecondes) */
  SDL_EnableKeyRepeat(10, 50);

  int loop = 1;
  int mode = 0;

  while(loop) {
    Uint32 startTime = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);

  if (mode == 0){
    /*** MENU ****/
    displayMenu();
  }
  if (mode == 1){
  /*** Animation / vitesse des élement ***/
  /*** vitesse du level */
    speed -= 0.005;
    //speed = 0;
    if (speed < -11){
      mode = 0;
      speed = 0;
    }
  /*** Projectile ***/
   projectile=updateProjectile(&projectile);
   playerBB = updateBoundingBox(&playerBB,transY_);
   transY_ = 0;
   // printf("(%f,%f)\n",playerBB.pMinX,playerBB.pMinY);

   int tmp, tmp2, tmp3;
   tmp = collision_(playerBB,obstacle);
   tmp2 = collision_ennemy(playerBB, ennemies);
   
   if (tmp == 0 || tmp2 == 0){
     loop = 0;
   }

  //ReadProjectile(projectile);
/*** Dessin des éléments ***/

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    drawLevel(levelarray);
    glPopMatrix();

    drawProjectile(projectile,speed);


    tmp3 = collision_bonus(playerBB, bonus);
    if(tmp3 == 0){
      // passage en mode spécial
      /* problème à résoudre : la modification dans le niveau ne se fait que quand tmp3=0
      dès que tmp3=1, l'effet disparait*/
    }

   /* ---- INVINCIBILITE ----

   Passage en mode invincibilité pendant une durée limitée 
   Il faudrait voir si on peut rajouter un petit effet visuel (changement de texture, de couleur...)
   pour montrer au joueur quand il est invincible et quand il ne l'est plus */
   if( (speed <= -(bonus->x1)/10) && (speed >= -((bonus->x2)/10)-2.5) ){
    /* Pour le moment, pour indiquer incvincibilité, joueur devient jaune */
    glColor3ub(255,255,0);
    glPushMatrix();
    glScalef(0.1,0.15,0);
    drawPlayer();
    glPopMatrix();
    /* Si on touche un ennemi/obstacle ou projectile, on ne meurt pas */
    if(tmp == 0 || tmp2 == 0){
      loop = 1;
    }
  }

  }
  if (mode == 2){
    /**** RULES & COMMAND *****/
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
          if (mode == 0){
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
        break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym){

            case SDLK_q:
              /* Fermeture de la fenêtre */
              loop = 0;

            /* Déplacement du vaisseau */
            case SDLK_UP:
            if(one.posY > 5.0){
              transY+=0.0;
              transY_=0.0;
            }
            else{
              transY+=1.0;
              transY_ = 1;
              one.posY+=1.0;
            }
              break;

            case SDLK_DOWN:
            if(one.posY < -5.0){
              transY+=0.0;
              transY_=0.0;
            }
            else{
              transY-=1.0;
              transY_ = -1;
              one.posY-=1.0;
            }
              break;

            case SDLK_RETURN:
              /* Pour retourner au menu après avoir consulté les règles */
              if(mode == 2){
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
                projectile = addProjectile(-speed,transY,-speed+0.2,transY-0.01,&projectile);
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

  Mix_FreeMusic(music);
  Mix_CloseAudio();
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
        glScalef(0.1,0.15,0);
        glTranslatef(x+i,y-j,0);
        drawRect(level[i][j][0],level[i][j][1],level[i][j][2]);
        glPopMatrix();
        i++;
      }
    }
    j++;
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();
  //glTranslatef(speed,0,0);
  glScalef(0.1,0.15,0);
  drawPlayer();
  glPopMatrix();
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
