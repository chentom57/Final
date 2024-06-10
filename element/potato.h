#ifndef potato_H_INCLUDED
#define potato_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <stdbool.h>
#include <time.h>

/*
   [potato object]
*/
// typedef enum potatoType
// {
//     STOP = 0,
//     MOVE,
//     ATK
// } potatoType;
typedef struct _potato
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of potato
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    ALLEGRO_BITMAP *img;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    long long start_local;
    char text_b[10];
    int hp;
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    Shape *hitbox; // the hitbox of object
} potato;
Elements *New_potato(int label, int x, int y);
void potato_placing(int x, int y);
void _potato_update_position(Elements *self, int dx, int dy);
void potato_update(Elements *self);
void potato_interact(Elements *self, Elements *target);
void potato_draw(Elements *self);
void potato_destory(Elements *self);

#endif
