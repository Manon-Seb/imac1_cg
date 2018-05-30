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

#include "gameplay.h"
#include "ppm.h"
#include "projectile.h"
#include "obstacle.h"
#include "collision.h"
#include "ennemy.h"
#include "displayGame.h"
#include "texture.h"

float displayGame(int transY_,float speed,float transX,float transY,float transZ,
  PList *projectile,BoundingBox *playerBB, obsList obstacle,
  int levelarray[100][10][3],ennemyList *ennemy,
  int *ennemyMove,PList *projectileEnnemy,GLuint textureID[10]){
  int tmp = 1;
  /*** Animation / vitesse des élement ***/
    /*** vitesse du level */
      speed -= 0.005;
      if (speed < -11){
        speed = 0;
        return 4;
      }

      *playerBB = updateBoundingBox(&(*playerBB),transY_);
      *projectile=updateProjectile(&(*projectile));
      (*ennemyMove)++;
      if ((*ennemyMove)==120){
        (*ennemy) = updateEnnemy(&(*ennemy),&(*ennemyMove));
        (*ennemyMove) = 0;
      }
      /* Collision */
      tmp = collision_(*playerBB,obstacle);
      if (tmp == 0){
        return 0;
      }
      tmp = collision_ennemy(*playerBB,*ennemy);
      if (tmp == 0){
        return 0;
      }


      /*** Dessin des éléments ***/
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glPushMatrix();
      drawEnnemy(*ennemy,speed,textureID);
      drawLevel(levelarray,speed,transX,transY,transZ,*ennemy,textureID);
      drawProjectile(*projectile,speed,textureID);
      glPopMatrix();
      return speed;
}

void drawLevel(int level[w][h][3],float speed, float transX, float transY, float transZ,ennemyList ennemy,GLuint textureID[10]){
  int i=0;
  int j=0;
  int x=0;
  int y=h/2;
  while (j<h){
    i=0;
    while (i<w){
      if (level[i][j][0]== 255 && level[i][j][1]== 0 && level[i][j][2]== 0){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glTranslatef(speed,0,0);
        glScalef(0.1,0.15,0);
        glTranslatef(x+i,y-j,0);
        drawRect(level[i][j][0],level[i][j][1],level[i][j][2]);
        glColor3ub(255,255,255);
        glScalef(0.5,0.5,0);
        display(textureID[4]);
        glPopMatrix();
        i++;
      }
      else{
        i++;
      }
    }
    j++;
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glPushMatrix();
  glScalef(0.1,0.15,0);
  drawPlayer(transX,transY,transZ,textureID);
  glPopMatrix();
}

void drawPlayer(float transX,float transY,float transZ,GLuint textureID[10]){
  glTranslatef(transX,transY,transZ);
  glScalef(0.6,0.6,0);
  display(textureID[5]);
}
