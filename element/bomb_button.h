#ifndef bomb_button_H_INCLUDED
#define bomb_button_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [bomb_button object]
*/
typedef struct _bomb_button
{
    int bomb_button;
    int x, y; // the position of image
    int width,heigh;    // the width 
    int in;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img2;
} bomb_button;

Elements *New_bomb_button(int label);
void bomb_button_update(Elements *self);
void bomb_button_interact(Elements *self, Elements *tar);
void bomb_button_draw(Elements *self);
void bomb_button_destory(Elements *self);

#endif
