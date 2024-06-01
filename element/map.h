#ifndef map_H_INCLUDED
#define map_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [map object]
*/
typedef struct _map
{
    int map;
    int x, y; // the position of image
    int width,height;    // the width 
    int in;
    int placed[5][10];
    Shape *hitbox;// the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img;
} map;

Elements *New_map(int label);
void map_update(Elements *self);
void map_interact(Elements *self, Elements *tar);
void map_draw(Elements *self);
void map_destory(Elements *self);

#endif
