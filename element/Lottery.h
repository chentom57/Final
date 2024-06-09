#ifndef Lottery_H_INCLUDED
#define Lottery_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
/*
   [Lottery object]
*/
typedef struct _Lottery
{
    int x, y; // the position of image
    int width,height;    // the width
    int done,output; 
    int sound_played;
    int in;
    char text[10];
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font2;
     ALLEGRO_SAMPLE_INSTANCE *win_Sound;
      ALLEGRO_SAMPLE_INSTANCE *lose_Sound;
} Lottery;

Elements *New_Lottery(int label);
void Lottery_update(Elements *self);
void Lottery_interact(Elements *self, Elements *tar);
void Lottery_draw(Elements *self);
void Lottery_destory(Elements *self);

#endif
