#ifndef SHADING_H
#define SHADING_H

#include <SDL/SDL.h>

#include "geometry.h"
#include "colors.h"

typedef struct Material{
	Color3f colorDiff;
	Color3f colorSpec;
	float shininess;
}Material;

Material createMaterial(Color3f colorDiff, Color3f colorSpec, float shininess);

#endif