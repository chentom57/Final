#ifndef Trueboss_H_INCLUDED
#define Trueboss_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include "../global.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "../algif5/src/algif.h"
#include <stdbool.h>
/*
   [Trueboss object]
*/
typedef struct _Trueboss
{
    float x, y;          // the position of image
    int width, height; // the width and height of image
    float v;             // the velocity of Trueboss
    int gameover;  // gameover flag
    int hp;     
    ALLEGRO_BITMAP *img;
    int state; 
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;

    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
} Trueboss;
Elements *New_Trueboss(int label);
void Trueboss_update(Elements *self);
void Trueboss_interact(Elements *self, Elements *tar);
void Trueboss_draw(Elements *self);
void Trueboss_destory(Elements *self);
void _Trueboss_update_position(Elements *self, float dx, float dy);
#endif
