#ifndef Back_gg_H_INCLUDED
#define Back_gg_H_INCLUDED
#include "element.h"
#include "../scene/gameover.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [Back_gg object]
*/
typedef struct _Back_gg
{
    int Back_gg;
    int x, y; // the position of image
    int width,heigh;    // the width 
    int in;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
} Back_gg;

Elements *New_Back_gg(int label);
void Back_gg_update(Elements *self);
void Back_gg_interact(Elements *self, Elements *tar);
void Back_gg_draw(Elements *self);
void Back_gg_destory(Elements *self);

#endif
