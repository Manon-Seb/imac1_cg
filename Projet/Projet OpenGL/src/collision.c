#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "collision.h"

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