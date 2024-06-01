#ifndef sunflw_button_H_INCLUDED
#define sunflw_button_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [sunflw_button object]
*/
typedef struct _sunflw_button
{
    int sunflw_button;
    int x, y; // the position of image
    int width,heigh;    // the width 
    int in;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
} sunflw_button;

Elements *New_sunflw_button(int label);
void sunflw_button_update(Elements *self);
void sunflw_button_interact(Elements *self, Elements *tar);
void sunflw_button_draw(Elements *self);
void sunflw_button_destory(Elements *self);

#endif