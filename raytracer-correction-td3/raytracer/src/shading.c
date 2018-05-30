#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>

#include "shading.h"
#include "geometry.h"
#include "sdl_tools.h"

Material createMaterial(Color3f colorDiff, Color3f colorSpec, float shininess){
	Material mat;
	mat.colorDiff = colorDiff;
	mat.colorSpec = colorSpec;
	mat.shininess = shininess;

	return mat;
}