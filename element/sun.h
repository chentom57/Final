#ifndef Sun_H_INCLUDED
#define Sun_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Sun object]
*/
typedef struct _Sun
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of sun
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Sun;
Elements *New_Sun(int label, int x, int y, int v);
void Sun_update(Elements *self);
void Sun_interact(Elements *self, Elements *tar);
void Sun_draw(Elements *self);
void Sun_destory(Elements *self);
void _Sun_update_position(Elements *self, int dx, int dy);
#endif
