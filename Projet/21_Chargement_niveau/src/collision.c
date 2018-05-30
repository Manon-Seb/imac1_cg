#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "collision.h"
#include "obstacle.h"
#include "ennemy.h"

BoundingBox calculateBoundingBox(){
  BoundingBox playerBB;
  /* On crée la bounding box en fonction des coordonnées min/max du player*/
  if(playerBB.pMinX < -0.5) playerBB.pMinX = -0.5;
  if(playerBB.pMinY < -0.5) playerBB.pMinY = -0.5;
  if(playerBB.pMaxX > 0.5) playerBB.pMaxX = 0.5;
  if(playerBB.pMaxY > 0.5) playerBB.pMaxY = 0.5;

  return playerBB;
}

BoundingBox updateBoundingBox(BoundingBox *playerBB,int transY){
  float speed = 0.05;
  if (playerBB == NULL){
    *playerBB = calculateBoundingBox();
    (*playerBB).pMinX = (*playerBB).pMinX;
    (*playerBB).pMinY = (*playerBB).pMinY;
    (*playerBB).pMaxX = (*playerBB).pMaxX;
    (*playerBB).pMaxY = (*playerBB).pMaxY;
    return *playerBB;
  }
  else{
    (*playerBB).pMinX = (*playerBB).pMinX + speed;
    (*playerBB).pMinY = (*playerBB).pMinY + transY;
    (*playerBB).pMaxX = (*playerBB).pMaxX + speed;
    (*playerBB).pMaxY = (*playerBB).pMaxY + transY;
    return *playerBB;
  }
}
BoundingBox updateBoundingBoxProjectile(BoundingBox *playerBB,int transY){
  float speed = 0.1555;// La vitesse dépends de l'échelle
  if (playerBB == NULL){
    *playerBB = calculateBoundingBox();
    (*playerBB).pMinX = (*playerBB).pMinX+speed;
    (*playerBB).pMinY = (*playerBB).pMinY+transY;
    (*playerBB).pMaxX = (*playerBB).pMaxX+speed;
    (*playerBB).pMaxY = (*playerBB).pMaxY+transY;
    return *playerBB;
  }
  else{
    (*playerBB).pMinX = (*playerBB).pMinX + speed;
    (*playerBB).pMinY = (*playerBB).pMinY + transY;
    (*playerBB).pMaxX = (*playerBB).pMaxX + speed;
    (*playerBB).pMaxY = (*playerBB).pMaxY + transY;
    return *playerBB;
  }
}
void drawBoundingBox(BoundingBox box){
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

int collision_(BoundingBox vaisseau, obsList list){
  while ((list)!=NULL){
    if (vaisseau.pMinX>(list)->x1 && vaisseau.pMaxX<(list)->x2){
        if (vaisseau.pMinY<(list)->y1 && vaisseau.pMaxY>(list)->y2){
          return 0;
        }
    }
    (list)=(list)->next;
  }
  return 1;
}