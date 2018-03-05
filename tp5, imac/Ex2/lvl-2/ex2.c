#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void drawFilledCircle(float rayon, float nbFaces, float angle){
    int i;
    glBegin(GL_POLYGON);
    for(i=0 ; i<nbFaces ; i++){
        angle = 2*M_PI*i/nbFaces;
        glVertex2f(cos(angle)*rayon, sin(angle)*rayon);
    }
    glEnd();
}

//const char* soleil = "textures/sun.bmp";
const char* mercure = "textures/mercure.bmp";
/*const char* venus = "textures/venus.bmp";
const char* terre = "textures/terre.bmp";
const char* mars = "textures/mars.bmp";
const char* jupiter = "textures/jupiter.bmp";
const char* saturne = "textures/saturne.bmp";
const char* uranus = "textures/uranus.bmp";
const char* neptune = "textures/neptune.bmp";*/

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
    SDL_WM_SetCaption("td05 - ex 02 - lvl 2", NULL);
    resizeViewport();

    // TODO: Chargement et traitement de la texture
    SDL_Surface *image;
    image = SDL_LoadBMP(mercure);
    if(image == NULL){
        fprintf(stderr, "Impossible de charger l'image.\n");
        return EXIT_FAILURE;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        image->w,
        image->h,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    // TODO: Libération des données CPU
    
    SDL_FreeSurface(image);

    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();
        // on veut activer la fontionnalité de texturing
        glEnable(GL_TEXTURE_2D);
        // on bind la texture pour pouvoir l'utiliser
        glBindTexture(GL_TEXTURE_2D, textureID);

        // TODO: Code de dessin

        glClear(GL_COLOR_BUFFER_BIT);
        // soleil
        //glColor3ub(255,255,0);
        glTexCoord2f(0,1);
        drawFilledCircle(0.05,40.0,5.0);
        // orbites
        int i;
            for(i=1 ; i<10 ; i++){
            	drawCircle((0.1*i), 40.0, 5.0);
            }
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        glPushMatrix();
        	// Mercure
        	glTranslatef(-0.08,-0.06,0.0);
        	glColor3ub(190,190,190);
        	drawFilledCircle(0.02,40.0,5.0);
        glPopMatrix();
        glPushMatrix();
        	// Vénus
        	glTranslatef(-0.2,0.0,0.0);
        	glColor3ub(239,155,15);
        	drawFilledCircle(0.02,40.0,5.0);
        	glPopMatrix();
        glPushMatrix();
        	// Terre
        	glTranslatef(-0.04,-0.3,0.0);
        	glColor3ub(0,127,255);
        	drawFilledCircle(0.02,40.0,5.0);
        glPopMatrix();
        glPushMatrix();
        	// Mars
        	glTranslatef(0.08,-0.39,0.0);
        	glColor3ub(136,66,29);
        	drawFilledCircle(0.02,40.0,5.0);
        glPopMatrix();
        glPushMatrix();
        	// Jupiter
        	glTranslatef(0.4,0.3,0.0);
        	glColor3ub(254,195,172);
        	drawFilledCircle(0.02,40.0,5.0);
        glPopMatrix();
        glPushMatrix();
        	// Saturne
        	glTranslatef(0.6,0.03,0.0);
        	glColor3ub(253,233,224);
        	drawFilledCircle(0.02,40.0,5.0);
        glPopMatrix();
        glPushMatrix();
        	// Uranus
        	glTranslatef(0.67,0.2,0.0);
        	glColor3ub(116,208,241);
        	drawFilledCircle(0.02,40.0,5.0);
        glPopMatrix();
        glPushMatrix();
        	// Neptune
        	glTranslatef(0.2,0.67,0.0);
        	glColor3ub(38,196,236);
        	drawFilledCircle(0.02,40.0,5.0);
        glPopMatrix();
        glPushMatrix();
        	// Pluton
        	glTranslatef(-0.3,0.85,0.0);
        	glColor3ub(126,88,53);
        	drawFilledCircle(0.02,40.0,5.0);
        glPopMatrix();

        // Fin du code de dessin

        // désactivation du sampling de texture
        glDisable(GL_TEXTURE_2D);
        // Débind de la texture
        glBindTexture(GL_TEXTURE_2D, 0);

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

    // TODO: Libération des données GPU
    glDeleteTextures(1, &textureID);

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}