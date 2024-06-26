#ifndef FLOWER_H_INCLUDED
#define FLOWER_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [flower object]
*/
// typedef enum FlowerType
// {
//     STOP = 0,
//     MOVE,
//     ATK
// } FlowerType;
typedef struct _Flower
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;       
    int behitted;               // the state of flower
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *behitted_Sound;
    ALLEGRO_SAMPLE *sample2;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    int hp;
    bool new_proj;
    Shape *hitbox; // the hitbox of object
    Shape *hitbox2; 
    Shape *hitbox3;  //for zombie interacting
} Flower;
Elements *New_Flower(int label, int x, int y);
void Flower_placing(int x, int y);
void _Flower_update_position(Elements *self, int dx, int dy);
void Flower_update(Elements *self);
void Flower_interact(Elements *self, Elements *target);
void Flower_draw(Elements *self);
void Flower_destory(Elements *self);

#endif
