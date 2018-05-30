#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
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
    gluOrtho2D(-2., 2., -2., 2.);
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

    // Load image from disk
    SDL_Surface* image = IMG_Load(filename);

    // Create openGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Set texture parameters
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // send image data to OpenGL

    GLenum format;
    switch(image->format->BytesPerPixel) {
        case 1:
            format = GL_RED;
            break;
        case 3:
            /* Ne g`ere pas les machines big-endian (`a confirmer...) */
            format = GL_RGB;
            break;
        case 4:
            /* Ne g`ere pas les machines big-endian (`a confirmer...) */
            format = GL_RGBA;
            break;
        default:
            /* On ne traite pas les autres cas */
            fprintf(stderr, "Format des pixels de l’image %s non pris en charge\n", filename);
            return EXIT_FAILURE;
    }

    printf("format %d\n", format);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Free loaded image (cpu)
    SDL_FreeSurface(image);

    int loop = 1;
    glClearColor(0.1, 0.1, 0.1 ,1.0);
    while(loop) {

        Uint32 startTime = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glRotatef(1, 0, 0, 1);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
            glVertex2f(-0.5, 0.5);
            glTexCoord2f(1, 0);
            glVertex2f(0.5, 0.5);
            glTexCoord2f(1, 1);
            glVertex2f(0.5, -0.5);
            glTexCoord2f(0, 1);
            glVertex2f(-0.5, -0.5);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

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

    // Free loaded image (gpu)
    glDeleteTextures(1, &textureID);

    // Liberation des ressources associées à la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
