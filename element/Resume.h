#ifndef Resume_H_INCLUDED
#define Resume_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [Resume object]
*/
typedef struct _Resume
{
    int Resume;
    int x, y; // the position of image
    int width,heigh;    // the width 
    int in;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
} Resume;

Elements *New_Resume(int label);
void Resume_update(Elements *self);
void Resume_interact(Elements *self, Elements *tar);
void Resume_draw(Elements *self);
void Resume_destory(Elements *self);

#endif
