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

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

/* Fonctions dessins de forme */
/* Carré */
void drawSquare(float width, float height){
    glBegin(GL_QUADS);
    glVertex2d(0.0, 0.0);
    glVertex2d(0.0, (height/20.0));
    glVertex2d((width/20.0), (height/20.0));
    glVertex2d((width/20.0), 0.0);
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
    glColor3ub(255,255,255);
    glBegin(GL_LINE_LOOP);
    for(i=0 ; i<nbFaces ; i++){
        angle = 2*M_PI*i/nbFaces;
        glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
    }
    glEnd();
}

int main(int argc, char** argv) {

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("td05", NULL);
    resizeViewport();

    // fonctions header <time.h>
    time_t rawtime;
	struct tm * timeinfo;
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	printf("hours %d\n", timeinfo->tm_hour);
	printf("minutes %d\n", timeinfo->tm_min);
	printf("seconds %d\n", timeinfo->tm_sec);

    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT);
        
        // dessin du repère
        drawLandmark();
        drawLandmarkPoints();
        // base
        drawCircle(1.0, 40.0, 5.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        glPushMatrix();
        	// aiguilles
        	// heures
        	glRotatef(20.0,0.0,0.0,1.0);
        	drawSquare(0.4, 8.0);
        glPopMatrix();
        glPushMatrix();
        	// minutes
        	drawSquare(0.2, 15.0);
        	// secondes
        	glRotatef(-30.0,0.0,0.0,1.0);
        	drawSquare(0.1, 19.0);
        /*glPopMatrix();
        glPushMatrix();
        	int i;
        	glColor3ub(255,0,0);
        	for(i=0 ; i<12 ; i++){
        		//glTranslatef(0.0,0.8,0.0);
        		glRotatef(-(360.0/12.0),0.0,0.0,1.0);
        		drawSquare(0.2, 2.0);
        	}*/
        glPopMatrix();

        // Fin du code de dessin

        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            switch(e.type) {

                case SDL_QUIT:
                    loop = 0;
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();

                default:
                    break;
            }
        }

        SDL_GL_SwapBuffers();
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
