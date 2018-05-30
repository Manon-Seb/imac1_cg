#ifndef COLORS_H
#define COLORS_H

typedef struct Color3f {
    float r;
    float g;
    float b;
} Color3f;

Color3f createColor(float r, float g, float b);

Color3f AddColors(Color3f c1, Color3f c2);
Color3f SubColors(Color3f c1, Color3f c2);
Color3f MultColors(Color3f c1, Color3f c2);
Color3f DivColors(Color3f c1, Color3f c2);

Color3f MultColor(Color3f c, float a);
Color3f DivColor(Color3f c, float a);

#endif