#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* Structures */
typedef struct point_link{
    float x, y; /* Position 2D du point */
    unsigned char r,g,b; /* Couleur du point */
    struct point_link* next; /* Point suivant à dessiner */
} PointLink, *PointList;

typedef struct primitive_link{
    GLenum primitiveType;
    PointList points;
    struct primitive_link* next;
} PrimitiveLink, *PrimitiveList;

/* Fonctions */

SDL_Surface* SDL_SetVideoMode(int width, int height, int bitsperpixel,Uint32 flags);
void SDL_WM_SetCaption(const char *title, const char *icon);

void projection();
void colorSelection();

PointLink* AllocPointLink(float x, float y, unsigned char r, unsigned char g, unsigned char b);
void AddPoint(PointLink* link, PointList* list);
void DrawPoints(PointList list);
void DeletePoints(PointList* list);

PrimitiveLink* AllocPrimitiveLink(GLenum primitiveType);
void AddPrimitiveLink(PrimitiveLink* link, PrimitiveList* list);
void DeletePrimitives(PrimitiveList* list);
void DrawPrimitives(PrimitiveList list);