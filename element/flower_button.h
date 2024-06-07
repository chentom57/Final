#ifndef flower_button_H_INCLUDED
#define flower_button_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [flower_button object]
*/
typedef struct _flower_button
{
    int flower_button;
    int x, y; // the position of image
    int width,heigh;    // the width 
    int in;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
} flower_button;

Elements *New_flower_button(int label);
void flower_button_update(Elements *self);
void flower_button_interact(Elements *self, Elements *tar);
void flower_button_draw(Elements *self);
void flower_button_destory(Elements *self);

#endif