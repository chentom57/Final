#ifndef BALL2_H_INCLUDED
#define BALL2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include "../global.h"
/*
   [Ball2 object]
*/
typedef struct _Ball2
{
    int x, y; // the position of image
    int r;    // the radius
    int in;
    int state2;
    int selflw;
    int lap; //overlap can't place
    int ranges;
    Shape *hitbox; // the hitbox of object
    Shape *placed_range;
    ALLEGRO_COLOR color;
} Ball2;

Elements *New_Ball2(int label);
void Ball2_update(Elements *self);
void Ball2_interact(Elements *self, Elements *tar);
void Ball2_draw(Elements *self);
void Ball2_destory(Elements *self);

#endif
