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
#include <assert.h>
#include <math.h>
#include <time.h>

// Dimensions de la fenêtre
static unsigned int WINDOW_WIDTH = 600;
static unsigned int WINDOW_HEIGHT = 600;

// Nombre de bits par pixel de la fenêtre
static const unsigned int BIT_PER_PIXEL = 32;

// Nombre minimal de millisecondes separant le rendu de deux images
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1, 1);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}


void drawSquare(int full) {
    if (full == 0) {
        glBegin(GL_LINE_LOOP);
    }
    else {
        glBegin(GL_TRIANGLE_FAN);
    }
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
}

void drawSquareFull(float size) {
    glBegin(GL_QUADS);
    glVertex2f(-size, size);
    glVertex2f(size, size);
    glVertex2f(size, -size);
    glVertex2f(-size, -size);
    glEnd();
}


int main(int argc, char** argv) {

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Ouverture d'une fenêtre et création d'un contexte OpenGL
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    SDL_WM_SetCaption("td06", NULL);

    resizeViewport();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Activation de l'option blending en OpenGL
    glEnable(GL_BLEND);
    // Spécification des paremètres de la fonction de blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int loop = 1;
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        // Code de dessin

        glClear(GL_COLOR_BUFFER_BIT);
        // glColor4f(r,v,b,alpha)
        float alpha = 0.5;
        glColor4f(0,255,80,alpha);
        drawSquare(1);

        glColor4f(255,0,0,alpha);
        drawSquareFull(0.2);

        // Event loop

        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }

            switch(e.type) {

                case SDL_MOUSEBUTTONUP:
                    break;

                case SDL_KEYDOWN:

                    switch(e.key.keysym.sym) {

                        case SDLK_q:
                            loop = 0;

                        default:
                            break;
                    }

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