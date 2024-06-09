#ifndef Zombie1_H_INCLUDED
#define Zombie1_H_INCLUDED
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
   [Zombie1 object]
*/
typedef struct _Zombie1
{
    float x, y;          // the position of image
    int width, height; // the width and height of image
    float v;             // the velocity of Zombie1
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
} Zombie1;
Elements *New_Zombie1(int label);
void Zombie1_update(Elements *self);
void Zombie1_interact(Elements *self, Elements *tar);
void Zombie1_draw(Elements *self);
void Zombie1_destory(Elements *self);
void _Zombie1_update_position(Elements *self, float dx, float dy);
#endif
