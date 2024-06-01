#ifndef Start_H_INCLUDED
#define Start_H_INCLUDED
#include "element.h"
#include "../scene/menu.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [Start object]
*/
typedef struct _Start
{
    int start;
    int x, y; // the position of image
    int width,heigh;    // the width 
    int in;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
} Start;

Elements *New_Start(int label);
void Start_update(Elements *self);
void Start_interact(Elements *self, Elements *tar);
void Start_draw(Elements *self);
void Start_destory(Elements *self);

#endif
