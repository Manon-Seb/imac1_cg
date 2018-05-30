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
#include "projectile.h"
#include "ennemy.h"
#include "texture.h"

PList allocateProjectile(float x,float y){
  /* Allocation */

  Projectile *newProjectile;
  newProjectile = malloc(sizeof*(newProjectile));

  if(newProjectile == NULL)
  {
    printf("NOT ENOUGH MEMORY !\n");
    return NULL;
  }

  /* Initialisation */
  newProjectile->x=x;
  newProjectile->y=y;
  newProjectile->projectileBB.pMinX=1.0;
  newProjectile->projectileBB.pMinY=+y;
  newProjectile->projectileBB.pMaxX=0;
  newProjectile->projectileBB.pMaxY=0.25+y;
  newProjectile->next=NULL;

  return newProjectile;
}

void ReadProjectile(PList list){
  if (list == NULL){
    printf("Empty List !E\n");
  }
  while(list!=NULL){
    printf("Projectiles position : (%f,%f)\n",list->projectileBB.pMinX+list->x,list->projectileBB.pMinY+list->y);
    list=list->next;
  }
}

PList addProjectile(float x,float y,PList *list){
  Projectile * tmp = NULL;
  if (*list == NULL){
    *list = allocateProjectile(x,y);
    return *list;
  }
  tmp = *list;
  while ((*list)->next!= NULL){
    *list = (*list)->next;
  }
  (*list)->next = allocateProjectile(x,y);
  *list = tmp;
  return *list;
}

PList subProjectile(float x,PList *list){
  PList tmp;
  while ((*list)!=NULL && (*list)->x>x){
    tmp = *list;
    *list = (*list)->next;
    free(tmp);
  }
  return *list;
}


PList updateProjectile(PList *list){
  Projectile * tmp = NULL;
  if (*list == NULL){
    return *list;
  }
  tmp = *list;
  while ((*list)!= NULL){
    updateBoundingBoxProjectile(&((*list)->projectileBB),0);
    (*list) = (*list)->next;
  }
  *list = tmp;
  return *list;
}

void drawProjectile(PList list,float speed,GLuint textureID[10]){
  if (list == NULL){
    return ;
  }
  while ((list)!= NULL){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glScalef(0.1,0.15,0);
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D); // activation texturing
  	glBindTexture(GL_TEXTURE_2D,textureID[6]); //bind la texture à utiliser
    glBegin(GL_POLYGON);
    glTexCoord2f(1,1);
    glVertex2f(list->projectileBB.pMinX, list->projectileBB.pMaxY);
    glTexCoord2f(0,1);
    glVertex2f(list->projectileBB.pMaxX, list->projectileBB.pMaxY);
    glTexCoord2f(0,0);
    glVertex2f(list->projectileBB.pMaxX, list->projectileBB.pMinY);
    glTexCoord2f(1,0);
    glVertex2f(list->projectileBB.pMinX, list->projectileBB.pMinY);
    glEnd();
    glDisable(GL_TEXTURE_2D); //desactivation sampling texture
  	glBindTexture(GL_TEXTURE_2D,0); //débind texture
    glPopMatrix();
    list = list->next;
  }
  return ;
}


PList freeProjectile(PList *list){
  if ((*list)==NULL) return NULL;
  freeProjectile(&((*list)->next));
  free((*list));
  return NULL;
}

int collision_projectile_obstacle(PList *lprojectile,obsList list){
  PList projectile = *lprojectile;
  while( projectile!=NULL){
    while ((list)!=NULL){
      if (projectile->projectileBB.pMinX+projectile->x>(list)->x1 && projectile->projectileBB.pMaxX+projectile->x<(list)->x2){
          if (projectile->projectileBB.pMinY<(list)->y1 && projectile->projectileBB.pMinY>(list)->y2){
            *lprojectile=deleteProjectile(&(*lprojectile),projectile->projectileBB.pMinX,projectile->projectileBB.pMinY);
            return 0;
          }
      }
      (list)=(list)->next;
    }
    projectile = projectile->next;
  }
  return 1;
}

int collision_ennemyprojectile_obstacle(PList *lprojectile,obsList list){
  PList projectile = *lprojectile;
  while( projectile!=NULL){
    while ((list)!=NULL){
      if (projectile->projectileBB.pMinX+projectile->x+5>(list)->x1 && projectile->projectileBB.pMaxX+projectile->x+5<=(list)->x2){
        printf("proj : %f %f obs :%f %f \n\n",projectile->projectileBB.pMinX+projectile->x,projectile->projectileBB.pMinY,(list)->x1,(list)->y1);
          if (projectile->projectileBB.pMinY+0.5<=(list)->y1 && projectile->projectileBB.pMinY+0.5>=(list)->y2){
            *lprojectile=deleteProjectile(&(*lprojectile),projectile->projectileBB.pMinX,projectile->projectileBB.pMinY);
            return 0;
          }
      }
      (list)=(list)->next;
    }
    projectile = projectile->next;
  }
  return 1;
}

int collision_projectile_ennemy(PList *lprojectile,ennemyList *ennemylist){
  ennemyList list = *ennemylist;
  PList projectile = *lprojectile;
  while( projectile!=NULL){
    while ((list)!=NULL){
      if (projectile->projectileBB.pMaxX+projectile->x>=(list)->boxEnnemy.pMinX && projectile->projectileBB.pMaxX+projectile->x<=(list)->boxEnnemy.pMaxX){
        //printf("ennemy.boxEnnemy.pMaxY = %f ennemy.boxEnnemy.pMinY = %f\n projectile.projectilleBB.pMaxY = %f projectile.projectilleBB.pMinY = %f\n",list->boxEnnemy.pMaxY,list->boxEnnemy.pMinY,projectile->projectileBB.pMaxY,projectile->projectileBB.pMinY);
          if ((projectile->projectileBB.pMinY<=(list)->boxEnnemy.pMinY && projectile->projectileBB.pMinY>=(list)->boxEnnemy.pMaxY)||
              (projectile->projectileBB.pMaxY<=(list)->boxEnnemy.pMaxY && projectile->projectileBB.pMaxY>=(list)->boxEnnemy.pMinY)||
              (projectile->projectileBB.pMaxY>=(list)->boxEnnemy.pMaxY && projectile->projectileBB.pMaxY<=(list)->boxEnnemy.pMinY))
            {
              *ennemylist=deleteEnnemy(&(*ennemylist),(list)->boxEnnemy.pMinX,(list)->boxEnnemy.pMinY);
              *lprojectile=deleteProjectile(&(*lprojectile),projectile->projectileBB.pMinX,projectile->projectileBB.pMinY);
            return 0;
          }
      }
      (list)=(list)->next;
    }
    projectile = projectile->next;
  }
  return 1;
}

PList deleteProjectile(PList *projectile,float x,float y){
  if (*projectile == NULL) return NULL;
  if ((*projectile)->projectileBB.pMinX == x && ((*projectile)->projectileBB.pMinY == y)){
    PList tmp = (*projectile)->next;
    return tmp;
  }
  else{
    (*projectile)->next = deleteProjectile(&((*projectile)->next),x,y);
    return *projectile;
  }
}


void drawprojectileEnnemy(PList list,float speed,GLuint textureID[10]){
  if (list == NULL) return;
  else{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(speed,0,0);
    glScalef(0.1,0.15,0);
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D); // activation texturing
  	glBindTexture(GL_TEXTURE_2D,textureID[6]); //bind the texture to use
    glBegin(GL_POLYGON);
        glTexCoord2f(0,1);
  	    glVertex2f((list)->projectileBB.pMinX+(list)->x, (list)->projectileBB.pMaxY);
        glTexCoord2f(1,1);
  	    glVertex2f((list)->projectileBB.pMaxX+(list)->x, (list)->projectileBB.pMaxY);
        glTexCoord2f(1,0);
  	    glVertex2f((list)->projectileBB.pMaxX+(list)->x, (list)->projectileBB.pMinY);
        glTexCoord2f(0,0);
  	    glVertex2f((list)->projectileBB.pMinX+(list)->x, (list)->projectileBB.pMinY);
  	glEnd();
    glDisable(GL_TEXTURE_2D); //desactivation sampling texture
    glBindTexture(GL_TEXTURE_2D,0); //debind texture
    glPopMatrix();
    drawprojectileEnnemy((list)->next,speed,textureID);
  }
}

void addProjectileEnnemy(ennemyList ennemy,PList *projectile){
  if(ennemy==NULL)return;
  else{
    addProjectile(ennemy->boxEnnemy.pMinX,ennemy->boxEnnemy.pMinY-0.5,&(*projectile));
    addProjectileEnnemy(ennemy->next,&(*projectile));
  }
}

PList updateProjectileEnnemy(PList *list){
  Projectile * tmp = NULL;
  if (*list == NULL){
    return *list;
  }
  tmp = *list;
  while ((*list)!= NULL){
    updateBoundingBoxProjectileEnnemy(&((*list)->projectileBB),0);
    (*list) = (*list)->next;
  }
  *list = tmp;
  return *list;
}

int collision_projectileennemy_vaisseau(BoundingBox vaisseau, PList list){
    while ((list)!=NULL){
      if (vaisseau.pMinX<=(list)->projectileBB.pMinX+list->x && vaisseau.pMaxX>=(list)->projectileBB.pMaxX+list->x){
          if ((vaisseau.pMinY<=(list)->projectileBB.pMaxY && vaisseau.pMinY>=(list)->projectileBB.pMinY)||
              (vaisseau.pMaxY<=(list)->projectileBB.pMinY && vaisseau.pMaxY>=(list)->projectileBB.pMaxY)){
            return 0;
          }
      }
      (list)=(list)->next;
    }
    return 1;
}
