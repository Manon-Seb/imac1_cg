#ifndef TEXTURE
#define TEXTURE 100

#include <stdio.h>
#include <string.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void display(GLuint textureID);
  /* Display textureID in a square */
GLuint loadTexture(const char* filename);
  /* Load a jpg image and return a GLuint object */
GLuint loadTextureTransparency(const char* filename);
  /* Load a png image and return a GLuint object */
#endif
