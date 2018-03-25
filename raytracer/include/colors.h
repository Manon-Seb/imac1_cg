typedef struct color3f{
	float r,g,b;
}Color3f;

// fonction calculant la somme de deux couleurs
Color3f addColors(Color3f c1, Color3f c2);
// fonctions pour la soutraction, la multiplication et la division de couleurs
Color3f subColors(Color3f c1, Color3f c2);
Color3f multColors(Color3f c1, Color3f c2);
Color3f divColors(Color3f c1, Color3f c2);
// fonctions de multiplication et division d'une couleur par un scalaire
Color3f multColor(Color3f c, float a);
Color3f divColor(Color3f c, float a);
