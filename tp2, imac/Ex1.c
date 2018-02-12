#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "fonctions.h"

static unsigned int WINDOW_WIDTH = 1024;
static unsigned int WINDOW_HEIGHT = 748;

static const unsigned int BIT_PER_PIXEL = 32;

static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

static const unsigned char COLORS[] = {
     0, 0, 0 ,
     255, 0, 0 ,
     0, 255, 0 ,
     0, 0, 255 ,
     255, 255, 0 ,
     255, 0, 255 ,
     0, 255, 255 ,
     255, 255, 255 
};
static const unsigned int NB_COLORS = sizeof(COLORS) / (3 * sizeof(unsigned char));

void reshape();
void setVideoMode();
void drawColorSelectionView();

int main(int argc, char** argv) {
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  
  setVideoMode();
  SDL_WM_SetCaption("TD2 - EX 01", NULL);
  
  unsigned int currentColor = 1; /* couleur rouge par defaut */
  int mode = 0; /* Mode dessin par defaut */
  
  /* Primitives Ã  dessiner : */
  PrimitiveList primitives = NULL;
  AddPrimitiveLink(AllocPrimitiveLink(GL_POINTS), &primitives);
  
  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    SDL_GL_SwapBuffers();
    
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
      
      switch(e.type) {
        case SDL_MOUSEBUTTONUP:
          if(mode == 1) {
            /* En mode selection de couleur on modifie l'indice de la couleur courante */
            currentColor = e.button.x * NB_COLORS / WINDOW_WIDTH;
          } else {
            /* En mode dessin on ajoute un point dans la liste de la primitive courante */
            AddPoint(AllocPointLink(-1 + 2. * e.button.x / WINDOW_WIDTH, - (-1 + 2. * e.button.y / WINDOW_HEIGHT), COLORS[currentColor * 3], COLORS[currentColor * 3 + 1], COLORS[currentColor * 3 + 2]), &primitives->points);
          }
        break;

        case SDL_MOUSEBUTTONDOWN:
          /*if(e.button.x == SDL_BUTTON_RIGHT){

          } */
          break;
        
        case SDL_KEYUP:
          if(e.key.keysym.sym == SDLK_q) {
            loop = 0;
          } 
        break;
          
        /*case SDL_VIDEORESIZE:
          WINDOW_WIDTH = e.resize.w;
          WINDOW_HEIGHT = e.resize.h;
          setVideoMode();
          break;*/
          
        default:
          break;
      }
    }
    
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }
  
  /* On libere la mémoire allouée pour les primitives */
  DeletePrimitives(&primitives);
  
  SDL_Quit();
  
  return EXIT_SUCCESS;
}

void reshape() {
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  GLKMatrix4MakeOrtho(-1., 1., -1., 1.);
}

void setVideoMode() {
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDLK_OPER/*| SDL_RESIZABLE*/)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  reshape();
}

void drawColorSelectionView() {
  int i;
  GLfloat dx = 2.f / NB_COLORS;
  glBegin(GL_QUADS);
    for(i = 0; i < NB_COLORS; ++i) {
      glColor3ubv(COLORS + i * 3);
      
      glVertex2f(-1 + i * dx, -1);
      glVertex2f(-1 + (i + 1) * dx, -1);
      glVertex2f(-1 + (i + 1) * dx, 1);
      glVertex2f(-1 + i * dx, 1);
    }
  glEnd();
}

/**
 * FONCTIONS DE GESTION DES LISTES
 */

PointLink* AllocPointLink(float x, float y, unsigned char r, unsigned char g, unsigned char b) {
  PointLink* link = (PointLink*) malloc(sizeof(PointLink));
  if(!link) {
    return NULL;
  }
  link->x = x;
  link->y = y;
  link->r = r;
  link->g = g;
  link->b = b;
  link->next = NULL;
  return link;
}

void AddPoint(PointLink* link, PointList* list) {
  assert(link);
  assert(list);
  
  if(*list == NULL) {
    *list = link;
  } else {
    AddPoint(link, &(*list)->next);
  }
}

void DrawPoints(PointList list) {
  while(list) {
    glColor3ub(list->r, list->g, list->b);
    glVertex2f(list->x, list->y);
    list = list->next;
  }
}

void DeletePoints(PointList* list) {
  assert(list);
  while(*list) {
    PointLink* next = (*list)->next;
    free(*list);
    *list = next;
  }
}

PrimitiveLink* AllocPrimitiveLink(GLenum primitiveType) {
  PrimitiveLink* link = (PrimitiveLink*) malloc(sizeof(PrimitiveLink));
  if(!link) {
    return NULL;
  }
  link->primitiveType = primitiveType;
  link->points = NULL;
  link->next = NULL;
  return link;
}

void AddPrimitiveLink(PrimitiveLink* link, PrimitiveList* list) {
  assert(link);
  assert(list);
  
  link->next = *list;
  *list = link;
}

void DeletePrimitives(PrimitiveList* list) {
  assert(list);
  while(*list) {
    PrimitiveLink* next = (*list)->next;
    DeletePoints(&(*list)->points);
    free(*list);
    *list = next;
  }
}

void DrawPrimitives(PrimitiveList list) {
  while(list) {
    glBegin(list->primitiveType);
    DrawPoints(list->points);
    glEnd();
    list = list->next;
  }
}