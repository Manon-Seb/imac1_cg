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
Le champ "next" est un pointeur sur un autre point, permettant de créer une liste chaînée de Points.
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

void addPointToList(Point* newPoint, Point* pointList) {
    /*
    Cette fonction ajoute un nouveau point à une liste de points existante. Une liste de points est représentée par le pointeur sur le premier point de la liste.
    */
    assert(newPoint); // la fonction assert() permet de crasher volontairement le programme si la condition passée en paramètre est fausse.
    assert(pointList); // On ne veut pas traiter le cas de la liste vide dans cette fonction.
    
    // On itère sur tous les points de la liste jusqu'à trouver le dernier élément (celui qui a un champs "next" à NULL)
    Point* currentPoint = pointList;
    while (currentPoint->next != NULL) {
        currentPoint = currentPoint->next;
    }
    // Une fois le dernier point de la liste identifié, on dit que le nouveau point à ajouter est son suivant.
    currentPoint->next = newPoint;
}

void drawPoints(Point* pointList) {
    /*
    Cette fonction dessine tous les points d'une liste de points.
    */
    Point* currentPoint = pointList;
    while(currentPoint) {
        glColor3ub(currentPoint->r, currentPoint->g, currentPoint->b);
        glVertex2f(currentPoint->x, currentPoint->y);
        currentPoint = currentPoint->next;
    }
}

void deletePoints(Point* pointList) {
    /*
    Cette fonction libère l'espace mémoire alloué par la fonction malloc() pour chacun des points.
    */
    assert(pointList);
    Point* currentPoint = pointList;
    while (currentPoint) {
        Point* nextPoint = pointList->next; // on sauvegarde le pointeur sur le point suivant
        free(currentPoint); // on libère les ressource du point courant
        currentPoint = nextPoint; // on itère sur la liste
    }
}


/************************************/
/******* Structure Primitive ********/
/************************************/

/*
La structure Primitive est un objet qui associe une liste de points avec un type de primitive OpenGL.
Le champ "next" est un pointeur sur une autre primitive, permettant de créer une liste chaînée de Primitives (pour dessiner plusieurs formes.
*/

typedef struct Primitive {
    Point* pointList;
    GLenum primitiveType;
    struct Primitive* next;
} Primitive;

Primitive* allocPrimitive(GLenum primitiveType) {
    /*
    Cette fonction alloue de l'espace mémoire pour stocker une primitive et retourne le pointeur correspondant.
    */

    // Allocation de l'espace mémoire
    Primitive* primitive = (Primitive*) malloc(sizeof(Primitive));
    if (!primitive) {
        return NULL; // Si tu pointeur est NULL, c'est qu'il y a un problème.
    }

    // Initialisation des champs de la structure
    primitive->primitiveType = primitiveType;
    primitive->pointList = NULL; // Pour l'instant il n'y a pas de points dans la liste
    primitive->next = NULL; // on initialise le champs "next" à NULL
    return primitive;
}

void addPrimitiveToList(Primitive* newPrimitive, Primitive* primitiveList) {
    /*
    Cette fonction ajoute une nouvelle primitive à une liste de primitives existante.
    Une liste de primitive est représentée par un pointeur sur la première primitive de la liste.
    */
    assert(newPrimitive); // la fonction assert() permet de crasher volontairement le programme si la condition passée en paramètre est fausse.
    assert(primitiveList); // On ne traite pas ici le cas où la liste est vide
    
    // On itère sur la liste de primitive jusqu'à trouver le dernier élément
    Primitive* currentPrimitive = primitiveList;
    while (currentPrimitive->next != NULL) {
        currentPrimitive = currentPrimitive->next;
    }
    // On ajoute la nouvelle primitive au nouvel élément de la liste.
    currentPrimitive->next = newPrimitive;
}

void drawPrimitives(Primitive* primitiveList) {
    /*
    Cette fonction dessine une liste de primitive complète en partant de la première.
    */
    Primitive* currentPrimitive = primitiveList;
    while (currentPrimitive) {
        glBegin(currentPrimitive->primitiveType);
        drawPoints(currentPrimitive->pointList);
        glEnd();
        currentPrimitive = currentPrimitive->next;
    }
}

void deletePrimitives(Primitive* primitiveList) {
    /*
    Cette fonction libère l'espace mémoire alloué par la fonction malloc() pour chaque primitive de la liste passée en paramètre.
    */
    assert(primitiveList);
    Primitive* currentPrimitive = primitiveList;
    while (currentPrimitive) {
        Primitive* nextPrimitive = currentPrimitive->next; // on sauvegarde le pointeur sur la primitive suivante
        free(currentPrimitive); // on libère les ressource da primitive courante
        currentPrimitive = nextPrimitive; // on itère sur la liste
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

    // On créé une première primitive
    Primitive* prim0 = allocPrimitive(GL_POINTS);

    // On définit une liste de primitive comme étant le pointeur sur la première primitive
    Primitive* primitiveList = prim0;

    // Nous allons avoir besoin du pointeur sur la dernière primitive de la liste, afin de pouvoir y ajouter des points
    Primitive* lastPrimitiveInList = prim0; // pour l'instant, il n'y a qu'une seule primitive dans la liste.

    // Boucle d'affichage

    int loop = 1;
    float openglX = 0.0;
    float openglY = 0.0;
    while(loop) {

        Uint32 startTime = SDL_GetTicks();
        
        // Code de dessin

        glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer

        drawPrimitives(primitiveList);

        // Boucle traitant les evenements
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            // L'utilisateur ferme la fenêtre
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
    
            switch(e.type) {

                // touche clavier
                case SDL_KEYUP:

                    switch(e.key.keysym.sym) {

                        case SDLK_q:
                            loop = 0;
                            break;

                        // Touche P = nouvelle primitive de type GL_POINTS
                        case SDLK_p:
                        
                            // On ne créé pas de nouvelle primitive si c'est la même que la primitive actuelle
                            if (lastPrimitiveInList->primitiveType != GL_POINTS) {
                                lastPrimitiveInList = allocPrimitive(GL_POINTS); // On créé une nouvelle primitive
                                addPrimitiveToList(lastPrimitiveInList, primitiveList); // On l'ajoute à la liste de primitives
                            }
                        
                            break;

                        // Touche L = nouvelle primitive de type GL_LINES
                        case SDLK_l:
                        
                            // On ne créé pas de nouvelle primitive si c'est la même que la primitive actuelle
                            if (lastPrimitiveInList->primitiveType != GL_LINES) {
                                lastPrimitiveInList = allocPrimitive(GL_LINES); // On créé une nouvelle primitive
                                addPrimitiveToList(lastPrimitiveInList, primitiveList); // On l'ajoute à la liste de primitives
                            }
                        
                            break;

                        // Touche T = nouvelle primitive de type GL_TRIANGLES
                        case SDLK_t:
                        
                            // On ne créé pas de nouvelle primitive si c'est la même que la primitive actuelle
                            if (lastPrimitiveInList->primitiveType != GL_TRIANGLES) {
                                lastPrimitiveInList = allocPrimitive(GL_TRIANGLES); // On créé une nouvelle primitive
                                addPrimitiveToList(lastPrimitiveInList, primitiveList); // On l'ajoute à la liste de primitives
                            }
                        
                            break;

                        default:
                            break;
                    
                    }
                    break;

                // Clic souris
                case SDL_MOUSEBUTTONUP:
                
                    // On convertit les coordonnées en pixel du clic souris en coordonnées OpenGL
                    openglX = -1. + 2. * e.button.x / WINDOW_WIDTH;
                    openglY = -(-1. + 2. * e.button.y / WINDOW_HEIGHT);
                    
                    Point* newPoint = allocPoint(openglX, openglY, 255, 0, 0); // On créé le nouvea point
                    
                    if (lastPrimitiveInList->pointList == NULL)
                    {
                        // Si la primitive courante n'a pas encore de liste de points, on désigne ce nouveau point comme étant le premier de la liste
                        lastPrimitiveInList->pointList = newPoint;
                    }
                    else
                    {
                        // Sinon, on utilise la fonction addPointToList qui va ajouter notre point à cette liste
                        addPointToList(newPoint, lastPrimitiveInList->pointList);
                    }
                
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

    deletePrimitives(primitiveList);

    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
