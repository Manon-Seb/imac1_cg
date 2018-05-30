#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


/************************************/
/********* Structure Point **********/
/************************************/

/*
La structure Point représente un simple point, avec des coordonnées x, y et une couleur r, g, b.
Le champ "next" est un pointeur sur un autre point, permettant de créer une liste chaînée de Points
*/
typedef struct Point {
    float x, y; // les coordonnées OpenGL du point
    unsigned char r, g, b; // la couleur du point (chaque composante entre 0 et 255)
    struct Point* next; // Un pointeur sur le point suivant afin de pouvoir créer une liste chaînée
} Point;

Point* allocPoint(float x, float y, unsigned char r, unsigned char g, unsigned char b) {
    /*
    Cette fonction alloue un espace mémoire suffisant pour pouvoir stocker un point, et retourne le pointeur associé.
    */

    // Allocation de l'espace mémoire
    Point* point = (Point*) malloc(sizeof(Point)); // Attention : la fonction malloc() renvoie un void* qu'il faut impérativement caster en Point*.
    if (!point) {
        return NULL; // Si tu pointeur est NULL, c'est qu'il y a un problème.
    }

    // On initialise chaque champ de la structure avec les valeurs reçues en paramètre
    point->x = x;
    point->y = y;
    point->r = r;
    point->g = g;
    point->b = b;
    point->next = NULL; // on initialise le champs "next" à NULL

    // On finit par retourner le pointeur (qui sera utilisé par le reste du programme)
    return point;
}

void addPointToList(Point* newPoint, Point* list) {
    /*
    Cette fonction ajoute un nouveau point à une liste de points existante. Une liste de points est représentée par le pointeur sur le premier point de la liste.
    */
    assert(newPoint); // la fonction assert() permet de crasher volontairement le programme si la condition passée en paramètre est fausse.
    assert(list); // On ne veut pas traiter le cas de la liste vide dans cette fonction.
    
    // On itère sur tous les points de la liste jusqu'à trouver le dernier élément (celui qui a un champs "next" à NULL)
    Point* currentPoint = list;
    while (currentPoint->next != NULL) {
        currentPoint = currentPoint->next;
    }
    // Une fois le dernier point de la liste identifié, on dit que le nouveau point à ajouter est son suivant.
    currentPoint->next = newPoint;
}

void drawPoints(Point* list) {
    /*
    Cette fonction dessine tous les points d'une liste de points.
    */
    while(list) {
        glColor3ub(list->r, list->g, list->b);
        glVertex2f(list->x, list->y);
        list = list->next;
    }
}

void deletePoints(Point* list) {
    /*
    Cette fonction libère l'espace mémoire alloué par la fonction malloc() pour chacun des points.
    */
    assert(list);
    while (list) {
        Point* next = list->next; // on sauvegarde le pointeur sur le point suivant
        free(list); // on libère les ressource du point courant
        list = next; // on itère sur la liste
    }
}


/************************************/
/********** Fonction main ***********/
/************************************/


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

    // Initialisation du contexte
    SDL_WM_SetCaption("Paint IMAC", NULL);
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // On créé quelques points statiques
    Point* p0 = allocPoint(0, 0, 255, 0, 0);
    Point* p1 = allocPoint(0.2, 0, 255, 0, 0);
    Point* p2 = allocPoint(0.2, -0.2, 255, 0, 0);

    // On créé une liste de points et on ajoute tous les points à cette dernière
    Point* pointList = p0; // une liste de points est simplement un pointeur sur le premier point
    addPointToList(p1, pointList);
    addPointToList(p2, pointList);

    // Boucle d'affichage

    int loop = 1;
    while(loop) {

        Uint32 startTime = SDL_GetTicks();
        
        // Code de dessin

        glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer

        glBegin(GL_LINE_STRIP);
        drawPoints(pointList);
        glEnd();


        // Boucle traitant les evenements
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            // L'utilisateur ferme la fenêtre
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            float openglX = 0.0; // les coordonées openGL du clic souris qu'on va récupérer
            float openglY = 0.0; // les coordonées openGL du clic souris qu'on va récupérer

            switch(e.type) {

                // Clic souris
                case SDL_MOUSEBUTTONUP:
                    // On convertit les coordonnées en pixel du clic souris en coordonnées OpenGL
                    openglX = -1. + 2. * e.button.x / WINDOW_WIDTH;
                    openglY = -(-1. + 2. * e.button.y / WINDOW_HEIGHT);
                    // On ajoute un nouveau point à la liste
                    Point* newPoint = allocPoint(openglX, openglY, 255, 0, 0);
                    addPointToList(newPoint, pointList);
                    break;

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

    deletePoints(pointList);

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
