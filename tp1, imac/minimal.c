#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void projection(){
    glViewport(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
}

int main(int argc, char** argv) {

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

    /* Efface le contenu de la fenêtre */
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* Boucle d'affichage */
    int loop = 1;
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        
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
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
		    /* Changement de la couleur de l'écran selon où on clique*/
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
		   
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);
		            /* si on appuie sur q, la fenêtre se ferme
		            On teste si la touche enfoncée est bien "q" */
		            if(e.key.keysym.sym == SDLK_q){
		              loop = 0;
		            }
                    else if(e.key.keysym.symp == SDLK_p){
                        glBegin(GL_POINTS);
                        glVertex2f(x,y);
                        glEnd();
                    }
                    else if(e.key.keysym.symp == SDLK_l){
                        glBegin(GL_LINES);
                        glVertex2f(x0, x1);
                        glVertex2f(x1, y1);
                        glEnd();
                    }
                    else if(e.key.keysym.symp == SDLK_t){
                        glBegin(GL_TRIANGLES);
                        glEnd();
                    }
                    else if(e.key.keysym.symp == SDLK_SPACE){
                        glBegin(GL_RECT);
                        glVertex2f(x0, x1);
                        glVertex2f(x1, y1);
                        glVertex2f(x2, y2);
                        glEnd();
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

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
