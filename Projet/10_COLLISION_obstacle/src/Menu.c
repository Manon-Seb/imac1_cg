#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#ifdef __APPLE__
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>
#include <SDL_image/SDL_image.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Menu.h"

void display(GLuint textureID){
       // TODO: Code de dessin
	glEnable(GL_TEXTURE_2D); // activation texturing
	glBindTexture(GL_TEXTURE_2D,textureID); //bind la texture à utiliser

        //glClear(GL_COLOR_BUFFER_BIT);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,0);

	//glRotatef(45,0.0,0.0,1.0);

	glBegin(GL_QUADS);
	glTexCoord2f(0,0);
	glVertex2f(-0.5,0.5);
	glTexCoord2f(1,0);
	glVertex2f(0.5,0.5);
	glTexCoord2f(1,1);
	glVertex2f(0.5,-0.5);
	glTexCoord2f(0,1);
	glVertex2f(-0.5,-0.5);
	glEnd();

	glDisable(GL_TEXTURE_2D); //desactivation sampling texture
	glBindTexture(GL_TEXTURE_2D,0); //débind texture
}

GLuint loadTexture(const char* filename){
	SDL_Surface* surface;
// TODO: Chargement et traitement de la texture
    surface = SDL_LoadBMP(filename);
    //surface=IMG_Load(filename);
    if (surface == NULL){
      printf("Erreur\n");
      return EXIT_FAILURE;
    }

    GLuint textureID;
    glGenTextures(1,&textureID);

    //Configuration des paramètres de texture
    glBindTexture(GL_TEXTURE_2D,textureID);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    //Envoi des données à la carte graphique
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

    //Détacher la texture de son point de bind
    glBindTexture(GL_TEXTURE_2D,0);
 // TODO: Libération des données CPU
        SDL_FreeSurface(surface);
    // ...
    return textureID;
}

void displayMenu(){

//TODO : texturer chaque boutton avec les textes

      /*** BACKGROUND ****/
    	glColor3ub(255,255,255);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glPushMatrix();
      glRectd(-1,1,1,-1);
      glPopMatrix();

      /*** TITTLE *****/
      glColor3ub(0,0,0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0,0.3,0);
      glPushMatrix();
      glRectd(-0.5,0.6,0.5,0.2);
      glPopMatrix();

			/*const char* filename = "test.jpg";
	    display(loadTexture(filename));*/
      /*** BUTTON 1 : Start ***/
      glColor3ub(0,0,0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0,-0.1,0);
      glPushMatrix();
      glRectd(-0.3,0,0.3,0.3);
      glPopMatrix();

      /*** BUTTON 2 : Rules ***/
      glColor3ub(0,0,0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0,-0.5,0);
      glPushMatrix();
      glRectd(-0.3,0,0.3,0.3);
      glPopMatrix();

      /*** BUTTON 3 : Quit ***/
    	glColor3ub(0,0,0);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0,-0.9,0);
      glPushMatrix();
      glRectd(-0.3,0,0.3,0.3);
      glPopMatrix();




}
