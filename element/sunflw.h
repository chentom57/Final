#ifndef SUNFLW_H_INCLUDED
#define SUNFLW_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Circle.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [sunflw object]
*/
// typedef enum SunflwType
// {
//     STOP = 0,
//     MOVE,
//     ATK
// } SunflwType;
typedef struct _Sunflw
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of sunflw
     int ptime;
       int hp;
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
    //0610

} Sunflw;
Elements *New_Sunflw(int label, int x, int y);
void Sunflw_placing(int x, int y);
void _Sunflw_update_position(Elements *self, int dx, int dy);
void Sunflw_update(Elements *self);
void Sunflw_interact(Elements *self, Elements *target);
void Sunflw_draw(Elements *self);
void Sunflw_destory(Elements *self);

#endif
