#ifndef OPENGL_TP1_LIST
#define OPENGL_TP1_LIST

#ifdef __APPLE__
#include <openGL/gl.h>
#else
#include <GL/gl.h>
#endif

/* Listes de points : */

typedef struct point_link {
  float x, y; // Position 2D du point
  unsigned char r, g, b; // Couleur du point
  struct point_link* next; // Suivant
} PointLink, *PointList;

PointLink* AllocPointLink(float x, float y, unsigned char r, unsigned char g, unsigned char b);
void AddPoint(PointLink* link, PointList* list);
void DrawPoints(PointList list);
void DeletePoints(PointList* list);

/* Listes de primitives : */

typedef struct primitive_link {
  GLenum primitiveType; // Type de primive ie. GL_POINTS, GL_LINES, ect.
  PointList points; // Points a dessiner
  struct primitive_link* next;
} PrimitiveLink, *PrimitiveList;

PrimitiveLink* AllocPrimitiveLink(GLenum primitiveType);
void AddPrimitiveLink(PrimitiveLink* link, PrimitiveList* list);
void DeletePrimitives(PrimitiveList* list);
void DrawPrimitives(PrimitiveList list);

#endif
