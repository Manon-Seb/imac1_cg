#include <GL/gl.h>

/* Structures */
typedef struct Point{
    float x, y; /* Position 2D du point */
    unsigned char r,g,b; /* Couleur du point */
    struct Point* next; /* Point suivant à dessiner */
} Point, *PointList;

typedef struct Primitive{
    GLenum primitiveType;
    PointListpoints;
    struct Primitive* next;
} Primitive, *PrimitiveList;

/* Fonctions */

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