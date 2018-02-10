#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <foncions.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/* Couleurs */
static const unsigned char COLORS[] = {
     255, 255, 255 /* Blanc */
     0, 0, 0 , /* Noir */
     255, 0, 0 , /* Rouge */
     0, 255, 0 , /* Vert */
     0, 0, 255 , /* Bleu */
     255, 255, 0 , /* Jaune */
     255, 0, 255 , /* Cyan */
     0, 255, 255 , /* Magenta */
};

static const unsigned int NB_COLORS = sizeof(COLORS) / (3 * sizeof(unsigned char));

/* Fonctions */

void projection(){
    glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(width, height, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

void colorSelection(){
  int i;
  GLfloat dx = 2.f / NB_COLORS;
  glBegin(GL_QUADS);
    for(i = 0; i < NB_COLORS; ++i){
      glColor3ubv(COLORS + i * 3);
      
      glVertex2f(-1 + i * dx, -1);
      glVertex2f(-1 + (i + 1) * dx, -1);
      glVertex2f(-1 + (i + 1) * dx, 1);
      glVertex2f(-1 + i * dx, 1);
    }
  glEnd();
}


PointLink* AllocPointLink(float x, float y, unsigned char r, unsigned char g, unsigned char b){
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

void AddPoint(PointLink* link, PointList* list){
  assert(link);
  assert(list);
  
  if(*list == NULL){
    *list = link;
  } else {
    AddPoint(link, &(*list)->next);
  }
}

void DrawPoints(PointList list){
  while(list){
    glColor3ub(list->r, list->g, list->b);
    glVertex2f(list->x, list->y);
    list = list->next;
  }
}

void DeletePoints(PointList* list){
  assert(list);
  while(*list){
    PointLink* next = (*list)->next;
    free(*list);
    *list = next;
  }
}

PrimitiveLink* AllocPrimitiveLink(GLenum primitiveType){
  PrimitiveLink* link = (PrimitiveLink*) malloc(sizeof(PrimitiveLink));
  if(!link){
    return NULL;
  }
  link->primitiveType = primitiveType;
  link->points = NULL;
  link->next = NULL;
  return link;
}

void AddPrimitiveLink(PrimitiveLink* link, PrimitiveList* list){
  assert(link);
  assert(list);
  
  link->next = *list;
  *list = link;
}

void DeletePrimitives(PrimitiveList* list){
  assert(list);
  while(*list){
    PrimitiveLink* next = (*list)->next;
    DeletePoints(&(*list)->points);
    free(*list);
    *list = next;
  }
}

void DrawPrimitives(PrimitiveList list){
  while(list) {
    glBegin(list->primitiveType);
    DrawPoints(list->points);
    glEnd();
    list = list->next;
  }
}

int main(int argc, char** argv){

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Désactivation du double buffering*/
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Titre de la fenêtre */
    SDL_WM_SetCaption("Fenêtre redimensionnable", NULL);

    /* Couleur cyan par défaut*/
    unsigned int currentColor = 6;
    /* Mode (on choisit 0 par défaut */
    int mode = 0;

    PrimitiveList primitives = NULL;
    AddPrimitiveLink(AllocPrimitiveLink(GL_POINTS), &primitives);
    
    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Efface le contenu de la fenêtre */
        glClear(GL_COLOR_BUFFER_BIT);
        
        if(mode == 1){
            colorSelection();
        }
        else{
            DrawPrimitives(primitives);
        }
        
        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();
        
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) {

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    if(mode == 1){
                        currentColor = e.button.x * NB_COLORS / WINDOW_WIDTH;
                    }
                    else{
                        AddPoint(AllocPointLink(-1 + 2. * e.button.x / WINDOW_WIDTH, - (-1 + 2. * e.button.y / WINDOW_HEIGHT), COLORS[currentColor * 3], COLORS[currentColor * 3 + 1], COLORS[currentColor * 3 + 2]), &primitives->points);
                    }
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
        		    /* Changement de la couleur de l'écran selon où on clique - EX 05 */
        		    glClearColor(e.button.x%255, e.button.y%255, 0, 1);
                    glBegin(GL_POINTS);
                    glVertex2f(-1 + 2. * e.button.x / WINDOW_WIDTH, -(-1 + 2. * e.button.y / WINDOW_HEIGHT));
                    glColor4ubv(-1 + 2. * e.button.x / WINDOW_WIDTH, -(-1 + 2. * e.button.y / WINDOW_HEIGHT));
                    glEnd();
                    break;

	           /* Mouvement souris */
	           case SDL_MOUSEMOTION:
		          glClearColor(e.button.xrel%255, e.button.yrel%255, 0, 1);
		          break;

                case SDL_KEYUP:
                    if(e.key.keysym.symp == SDLK_SPACE){
                        mode = 0;
                    }
                    else{
                        switch(e.key.keysym.sym){
                            case SDLK_p:
                                AddPrimitiveLink(AllocPrimitiveLink(GL_POINTS), &primitives);
                                break;

                            case SDLK_l:
                                AddPrimitiveLink(AllocPrimitiveLink(GL_LINES), &primitives);
                                break;

                            case SDLK_t:
                                AddPrimitiveLink(AllocPrimitiveLink(GL_TRIANGLES), &primitives);
                                break;

                            default:
                                break;
                        }
                    }
                    break;
		   
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
		            /* si on appuie sur q, la fenêtre se ferme
		            On teste si la touche enfoncée est bien "q" */
		            if(e.key.keysym.sym == SDLK_q){
		              loop = 0;
		            }
                   
                    if(e.key.keysym.symp == SDLK_SPACE){
                        /* Passage en mode palette */
                        mode = 1;
                    }
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_HEIGHT = e.resize.h;
                    WINDOW_WIDTH = e.resize.w;
                    projection();
                    break;

                default:
                    break;
            }
        }

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Libération de la mémoire allouée pour les primitives*/
    DeletePrimitives(&primitives);

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
