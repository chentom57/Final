#ifndef Boss_H_INCLUDED
#define Boss_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include "../global.h"
/*
   [Boss object]
*/
typedef struct _Boss
{
    float x, y;          // the position of image
    int width, height; // the width and height of image
    float v;             // the velocity of Boss
    int gameover;      // gameover flag
    int hp;             //0607 : hp for boss
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} Boss;
Elements *New_Boss(int label);
void Boss_update(Elements *self);
void Boss_interact(Elements *self, Elements *tar);
void Boss_draw(Elements *self);
void Boss_destory(Elements *self);
void _Boss_update_position(Elements *self, float dx, float dy);
#endif
