#ifndef potato_button_H_INCLUDED
#define potato_button_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [potato_button object]
*/
typedef struct _potato_button
{
    int potato_button;
    int x, y; // the position of image
    int width,height;    // the width 
    int in;
    
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img2;
} potato_button;

Elements *New_potato_button(int label);
void potato_button_update(Elements *self);
void potato_button_interact(Elements *self, Elements *tar);
void potato_button_draw(Elements *self);
void potato_button_destory(Elements *self);

#endif