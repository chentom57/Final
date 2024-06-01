#ifndef Quit_H_INCLUDED
#define Quit_H_INCLUDED
#include "element.h"
#include "../scene/menu.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [Quit object]
*/
typedef struct _Quit
{
    int Quit;
    int x, y; // the position of image
    int width,heigh;    // the width 
    int in;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
} Quit;

Elements *New_Quit(int label);
void Quit_update(Elements *self);
void Quit_interact(Elements *self, Elements *tar);
void Quit_draw(Elements *self);
void Quit_destory(Elements *self);

#endif
