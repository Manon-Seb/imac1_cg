#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

#include "texture.h"

void display(GLuint textureID){

	glEnable(GL_TEXTURE_2D); // activation texturing
	glBindTexture(GL_TEXTURE_2D,textureID); //bind the texture to use



	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(-1,1);
	glTexCoord2f(1,0);
	glVertex2f(1,1);
	glTexCoord2f(1,1);
	glVertex2f(1,-1);
	glTexCoord2f(0,1);
	glVertex2f(-1,-1);
	glEnd();

	glDisable(GL_TEXTURE_2D); //desactivation sampling texture
	glBindTexture(GL_TEXTURE_2D,0); //debind texture
}


GLuint loadTexture(const char* filename){
	SDL_Surface* surface;

    surface=IMG_Load(filename);
    if (surface == NULL){
      printf("Erreur\n");
      return EXIT_FAILURE;
    }

    GLuint textureID;
    glGenTextures(1,&textureID);

    //texture parameter
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);


    //Send data to the CGU
    glTexImage2D(
		 GL_TEXTURE_2D,
		 0,
		 GL_RGB,
		 surface->w,
		 surface->h,
		 0,
		 GL_RGB,
		 GL_UNSIGNED_BYTE,
		 surface->pixels);

    //Debind the texture
    glBindTexture(GL_TEXTURE_2D,0);
    SDL_FreeSurface(surface);
    return textureID;
}

GLuint loadTextureTransparency(const char* filename){
	SDL_Surface* surface;

    surface=IMG_Load(filename);
    if (surface == NULL){
      printf("Erreur\n");
      return EXIT_FAILURE;
    }



    GLuint textureID;
    glGenTextures(1,&textureID);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
    //Texture parameter

    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);


    //Send data to the CGU
    glTexImage2D(
		 GL_TEXTURE_2D,
		 0,
		 GL_RGBA8,
		 surface->w,
		 surface->h,
		 0,
		 GL_RGBA,
		 GL_UNSIGNED_BYTE,
		 surface->pixels);

    //Debind the texture
    glBindTexture(GL_TEXTURE_2D,0);
    SDL_FreeSurface(surface);
    return textureID;
}
