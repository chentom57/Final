#ifndef Back_H_INCLUDED
#define Back_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [Back object]
*/
typedef struct _Back
{
    int back;
    int x, y; // the position of image
    int width,heigh;    // the width 
    int in;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
} Back;

Elements *New_Back(int label);
void Back_update(Elements *self);
void Back_interact(Elements *self, Elements *tar);
void Back_draw(Elements *self);
void Back_destory(Elements *self);

#endif
