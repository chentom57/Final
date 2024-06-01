#ifndef Zombie1_H_INCLUDED
#define Zombie1_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include "../global.h"
/*
   [Zombie1 object]
*/
typedef struct _Zombie1
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int v;             // the velocity of Zombie1
    int gameover;      // gameover flag
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Zombie1;
Elements *New_Zombie1(int label);
void Zombie1_update(Elements *self);
void Zombie1_interact(Elements *self, Elements *tar);
void Zombie1_draw(Elements *self);
void Zombie1_destory(Elements *self);
void _Zombie1_update_position(Elements *self, int dx, int dy);
#endif
