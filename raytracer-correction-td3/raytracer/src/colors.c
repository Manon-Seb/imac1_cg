#include <math.h>
#include "colors.h"

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b)) 

Color3f createColor(float r, float g, float b) {
    Color3f color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

Color3f addColors(Color3f c1, Color3f c2) {
    c1.r += c2.r;
    c1.g += c2.g;
    c1.b += c2.b;
    return c1;
};

Color3f subColors(Color3f c1, Color3f c2) {
    c1.r -= c2.r;
    c1.g -= c2.g;
    c1.b -= c2.b;
    return c1;
}

Color3f multColors(Color3f c1, Color3f c2) {
    c1.r *= c2.r;
    c1.g *= c2.g;
    c1.b *= c2.b;
    return c1;
}

Color3f divColors(Color3f c1, Color3f c2) {
    c1.r /= c2.r;
    c1.g /= c2.g;
    c1.b /= c2.b;
    return c1;
}

Color3f multColor(Color3f c, float a) {
    c.r *= a;
    c.g *= a;
    c.b *= a;
    return c;
}

Color3f divColor(Color3f c, float a) {
    c.r /= a;
    c.g /= a;
    c.b /= a;
    return c;
}

Color3f clampColor(Color3f c) {
    c.r = min(1, max(0, c.r));
    c.g = min(1, max(0, c.g));
    c.b = min(1, max(0, c.b));
    return c;
}