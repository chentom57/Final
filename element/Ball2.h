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
    int ranges;
    int block_x,block_y;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_BITMAP *img_r;
    ALLEGRO_BITMAP *img_g;
    ALLEGRO_BITMAP *img_y;
    ALLEGRO_SAMPLE_INSTANCE *Planting_Sound;
    ALLEGRO_SAMPLE *sample;
} Ball2;

Elements *New_Ball2(int label);
void Ball2_update(Elements *self);
void Ball2_interact(Elements *self, Elements *tar);
void Ball2_draw(Elements *self);
void Ball2_destory(Elements *self);

#endif
