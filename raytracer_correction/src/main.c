#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "geometry.h"
#include "shape.h"
#include "raytracer.h"

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;

int main(int argc, char** argv) {

    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
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
    // Nettoyage du framebuffer
    SDL_FillRect(framebuffer, NULL, SDL_MapRGB(framebuffer->format, 0, 0, 0));
    
    // Création de la scène
    Scene scene = createScene();
    addSphereToScene(&scene, createSphere(createPoint(0.0, 0, -3), 1, createColor(1, 0, 0)));
    addSphereToScene(&scene, createSphere(createPoint(0.3, 0, -2), 0.5, createColor(0, 1, 0)));

    // Appel au raytracing
    simpleRaytracing(scene, framebuffer);

    int loop = 1;
    while(loop) {

        // On copie le framebuffer à l'écran
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
