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
    gluOrtho2D(-20., 20., -20., 20.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

/* Fonctions dessins de forme */
/* Carré */
void drawSquare(float size){
    glBegin(GL_QUADS);
    glVertex2d(-(size/20.0), -(size/20.0));
    glVertex2d(-(size/20.0), (size/20.0));
    glVertex2d((size/20.0), (size/20.0));
    glVertex2d((size/20.0), -(size/20.0));
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
    int i;
    glPointSize(5.0);
    glColor3ub(255,255,255);
    glBegin(GL_POINTS);
    for(i=0 ; i<=20 ; i++){
        glVertex2d((i/20.0), 0.0);
        glVertex2d(0.0, (i/20.0));
    }
    glEnd();
}

void drawCircle(float rayon, float nbFaces, float angle){
    int i;
    glColor3ub(255,165,0);
    glBegin(GL_POLYGON);
    for(i=0 ; i<nbFaces ; i++){
        angle = 2*M_PI*i/nbFaces;
        glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
    }
    glEnd();
}

void drawRoundedSquare(){
	drawSquare(0.5);
}

void drawFirstArm(){
	glPushMatrix();
		drawCircle((2.0/20.0) ,40.0, 5.0);
		glTranslatef((6.0/20.0), 0.0, 0.0);
		drawCircle((1.0/20.0), 40.0, 5.0);
	glPopMatrix();
	glColor3ub(255,165,0);
    glBegin(GL_QUADS);
    glVertex2d(0.0, -(2.0/20.0));
    glVertex2d(0.0, (2.0/20.0));
    glVertex2d((6.0/20.0), (1.0/20.0));
    glVertex2d((6.0/20.0), -(1.0/20.0));
    glEnd();
}

void drawSecondArm(){
	glColor3ub(0,255,0);
	glPushMatrix();
		drawSquare(0.5);
		glTranslatef((4.0/20.0),0.0, 0.0);
		drawSquare(0.5);
	glPopMatrix();

	glColor3ub(255,255,0);
	glBegin(GL_QUADS);
    glVertex2d(-(0.25/20.0), -(0.3/20.0));
    glVertex2d(-(0.25/20.0), (0.3/20.0));
    glVertex2d((4.25/20.0), (0.3/20.0));
    glVertex2d((4.25/20.0), -(0.3/20.0));
    glEnd();
}

void drawThirdArm(){
	glColor3ub(0,255,255);
	glPushMatrix();
		drawSquare(0.3);
		glTranslatef((3.5/20.0),0.0,0.0);
		drawCircle((0.4/20.0),40.0,5.0);
	glPopMatrix();
	glColor3ub(130,40,255);
	glBegin(GL_QUADS);
    glVertex2d(-(0.20/20.0), -(0.2/20.0));
    glVertex2d(-(0.20/20.0), (0.2/20.0));
    glVertex2d((3.5/20.0), (0.2/20.0));
    glVertex2d((3.5/20.0), -(0.2/20.0));
    glEnd();
}

/* Liste */
/* On veut générer une liste */
GLuint createFirstArmIDList = glGenLists(1);
glNewList(createFirstArmIDList, GL_COMPILE);
    
    drawFirstArm();
glEndList();

/*GLuint createSecondArmIDList = glGenLists(1);
glNewList(createSecondArmIDList, GL_COMPILE);
    
    drawSecondArm();
glEndList();

GLuint createThirdArmIDList = glGenLists(1);
glNewList(createThirdArmIDList, GL_COMPILE);
    drawThirdArm();
glEndList();*/

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
        glColor3ub(255,0,0);
        /*drawSquare();*/
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        glPushMatrix();
        	drawRoundedSquare();
            glRotatef(25, 0.0, 0.0, 1.0);
        	glCallList(createFirstArmIDList);
        glPopMatrix();
       /* glPushMatrix();
            glTranslatef((5.5/20.0),(2.5/20.0),0.0);
        	glCallList(createSecondArmIDList);
        glPopMatrix();
        glPushMatrix();
        glTranslatef((9.5/20.0),(2.5/20.0),0.0);
        glRotatef(35, 0.0, 0.0, 1.0);
        	glCallList(createThirdArmIDList);
        	glRotatef(-35, 0.0, 0.0, 1.0);
        	glCallList(createThirdArmIDList);
        	glRotatef(-35, 0.0, 0.0, 1.0);
        	glCallList(createThirdArmIDList);
        glPopMatrix();*/


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