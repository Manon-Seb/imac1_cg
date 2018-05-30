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

#include "Menu.h"
#include "texture.h"


void displayMenu(GLuint textureID){


      /*** BACKGROUND ****/
    	glColor3ub(255,255,255);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glPushMatrix();
      glRectd(-1,1,1,-1);
      glPopMatrix();
      /*** ADD A TEXTURE ***/
      display(textureID);

}

void displayGameOver(){


      /*** BACKGROUND ****/
    	glColor3ub(255,255,255);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glPushMatrix();
      glRectd(-1,1,1,-1);
      glPopMatrix();
      /*** ADD A TEXTURE ***/
			const char* filename = "FLAPIMAC_GO.jpg";
	    display(loadTexture(filename));
}
