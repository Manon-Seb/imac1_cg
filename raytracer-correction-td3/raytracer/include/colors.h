#ifndef COLORS_H
#define COLORS_H

typedef struct Color3f {
    float r;
    float g;
    float b;
} Color3f;

Color3f createColor(float r, float g, float b);

Color3f addColors(Color3f c1, Color3f c2);
Color3f subColors(Color3f c1, Color3f c2);
Color3f multColors(Color3f c1, Color3f c2);
Color3f divColors(Color3f c1, Color3f c2);

Color3f multColor(Color3f c, float a);
Color3f divColor(Color3f c, float a);

Color3f clampColor(Color3f c);

#endif