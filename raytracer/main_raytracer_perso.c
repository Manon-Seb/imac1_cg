#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "geometry.h"
#include "shape.h"
#include "raytracer.h"

static unsigned int WINDOW_WIDTH = 1;
static unsigned int WINDOW_HEIGHT = 1;
static const unsigned int BIT_PER_PIXEL = 32;

int main(int argc, char** argv) {

    // Initialisation de la SDL
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }

    // Création de la fenêtre SDL
    SDL_Surface* screen = NULL;
    if(NULL == (screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_DOUBLEBUF))) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("Raytracing powa :D", NULL);

    // Création d'une surface SDL dans laquelle le raytracer dessinera
    SDL_Surface* framebuffer = NULL;
    if(NULL == (framebuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, 0, 0, 0, 0))) {
        fprintf(stderr, "Erreur d'allocation pour le framebuffer. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    // Nettoyage du framebuffer par une couleur de fond (noir)
    SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));


    // Création de la scène
    Scene scene = createScene();

    // Ajout d'objets dans la scène
    // ...

    // Appel de la fonction de raytracing
    // ...

    int loop = 1;
    while(loop) {

        SDL_BlitSurface(framebuffer, NULL, screen, NULL);
        SDL_Flip(screen);

        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
        }
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}
