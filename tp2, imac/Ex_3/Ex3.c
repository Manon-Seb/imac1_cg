#include <SDL/SDL.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-8., 8., -6., 6.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

/* Fonctions dessins de forme */
/* Carré */
void drawSquare(){
    glColor3ub(255,0,0);
    glBegin(GL_QUADS);
    glVertex2d(-0.5, -0.5);
    glVertex2d(-0.5, 0.5);
    glVertex2d(0.5, 0.5);
    glVertex2d(0.5, -0.5);
    glEnd();
}

void drawSquarePurple(){
    glColor3ub(102,0,153);
    glBegin(GL_QUADS);
    glVertex2d(-0.5, -0.5);
    glVertex2d(-0.5, 0.5);
    glVertex2d(0.5, 0.5);
    glVertex2d(0.5, -0.5);
    glEnd();
}
void drawSquareYellow(float x, float y){
    glColor3ub(255,255,0);
    glBegin(GL_QUADS);
    glVertex2d(-(x/8.0), -(y/8.0));
    glVertex2d(-(x/8.0), (y/8.0));
    glVertex2d((x/8.0), (y/8.0));
    glVertex2d((x/8.0), -(y/8.0));
    glEnd();
}
/* Repère */
void drawLandmark(){
    /* Axe horizontal X */
    glColor3ub(255,0,0);
    glBegin(GL_LINES);
    glVertex2d(0.0, 0.0);
    glVertex2d(8.0, 0.0);
    glEnd();
    /* Axe vertical Y*/
    glColor3ub(0,255,0);
    glBegin(GL_LINES);
    glVertex2d(0.0, 0.0);
    glVertex2d(0.0, 6.0);
    glEnd();
}

void drawLandmarkPoints(){
    int i, j;
    glPointSize(5.0);
    glColor3ub(255,255,255);
    glBegin(GL_POINTS);
    for(i=0 ; i<=8 ; i++){
        glVertex2d(i/8.0, 0.0);
    }
    for(j=0 ; j<=6 ; j++){
        glVertex2d(0.0, j/6.0);
    }
    glEnd();
}

void drawCircle(float rayon, float nbFaces, float angle){
    int i;
    glColor3ub(150,100,0);
    glBegin(GL_LINE_LOOP);
    for(i=0 ; i<nbFaces ; i++){
        angle = 2*M_PI*i/nbFaces;
        glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
    }
    glEnd();
}

void drawBlueCircle(float rayon, float nbFaces, float angle){
    int i;
    glColor3ub(0,0,255);
    glBegin(GL_LINE_LOOP);
    for(i=0 ; i<nbFaces ; i++){
        angle = 2*M_PI*i/nbFaces;
        glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
    }
    glEnd();
}

int main(int argc, char** argv) {

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("Paint IMAC", NULL);

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    int loop = 1;

    /* Boucle d'affichage */
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Code de dessin */

        glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer
        
        /* Dessin des fonctions */
        drawLandmark();
        drawLandmarkPoints();
        /*drawSquare();*/
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        glPushMatrix();
        glTranslatef((1.0/8.0), (2.0/8.0), 0.0);
        drawCircle(0.5, 40.0, 5.0);

        glRotatef(45, 0.0, 0.0, 1.0);
        glTranslatef((2.0/8.0), 0.0, 0.0);
        drawSquare();
        glRotatef(45, 0.0, 0.0, 1.0);
        glTranslatef((2.0/8.0), 0.0, 0.0);
        drawSquarePurple();
        drawSquareYellow(0.5, 0.5);
        glPopMatrix();

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

                    if(e.button.button == SDL_BUTTON_LEFT){
                      printf("clic gauche\n");
                      /* drawSquareYellow(e.button.x, e.button.y); */
                    }
                    break;

                /* Touche clavier */
                case SDL_KEYDOWN:

                    printf("touche pressée (code = %d)\n", e.key.keysym.sym);

                    switch(e.key.keysym.sym) {

                        case SDLK_q:
                            loop = 0;

                        default:
                            break;
                    }

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();

                default:
                    break;
            }
        }

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

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