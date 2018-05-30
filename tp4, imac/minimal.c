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

const char* filename = "logo_imac_400x400.jpg";

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
    SDL_WM_SetCaption("td04", NULL);
    resizeViewport();

    // TODO: Chargement et traitement de la texture
    SDL_Surface *image;
    image = SDL_LoadBMP("galaxy.bmp");
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

    // Boucle de dessin (à décommenter pour l'exercice 3)
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
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        glPushMatrix();
            // transformations
            //glRotatef(45,0.0,0.0,1.0);
            //glScalef(0.5,0.5,0.5);
            glBegin(GL_POLYGON);
            glTexCoord2f(0,0);
            glVertex2f(-1.0, 1.0);
            glTexCoord2f(1,0);
            glVertex2f(1.0, 1.0);
            glTexCoord2f(0,1);
            glVertex2f(-1.0, -1.0);
            glTexCoord2f(1,1);
            glVertex2f(1.0, -1.0);
            glEnd();
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
