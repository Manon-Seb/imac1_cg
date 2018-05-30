#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "collision.h"

BoundingBox calculateBoundingBox(){
  BoundingBox playerBB;
  /* On crée la bounding box en fonction des coordonnées min/max du player*/
  if(playerBB.pMinX < -0.5) playerBB.pMinX = -0.5;
  if(playerBB.pMinY < -0.5) playerBB.pMinY = -0.5;
  if(playerBB.pMaxX > 0.5) playerBB.pMaxX = 0.5;
  if(playerBB.pMaxY > 0.5) playerBB.pMaxY = 0.5;

  return playerBB;
}

void drawBoundingBox(BoundingBox box){
	glColor3ub(255,255,255);
	/* On dessine seulement le contour */
	glBegin(GL_LINE_LOOP);
	    glVertex2f(box.pMinX, box.pMaxY);
	    glVertex2f(box.pMaxX, box.pMaxY);
	    glVertex2f(box.pMaxX, box.pMinY);
	    glVertex2f(box.pMinX, box.pMinY);
	glEnd();
}

int collision(BoundingBox vaisseau, BoundingBox decor){
	if((vaisseau.pMinX >= decor.pMaxX)
		|| (vaisseau.pMaxX <= decor.pMinX)
		|| (vaisseau.pMinY >= decor.pMaxY)
		|| (vaisseau.pMaxY <= decor.pMinY)){
		return 0;
	}
	/* Renvoie 1 si les éléments se chevauchent */
	return 1;
}
