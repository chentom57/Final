#ifndef bomb_H_INCLUDED
#define bomb_H_INCLUDED
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
   [bomb object]
*/
// typedef enum bombType
// {
//     STOP = 0,
//     MOVE,
//     ATK
// } bombType;
typedef struct _bomb
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int sound_played;                      // the state of bomb
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *bang_Sound;
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img2;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    long long start_local;
    char text_b[10];
    ALLEGRO_COLOR color;
    ALLEGRO_FONT *font;
    Shape *hitbox; // the hitbox of object
} bomb;
Elements *New_bomb(int label, int x, int y);
void bomb_placing(int x, int y);
void _bomb_update_position(Elements *self, int dx, int dy);
void bomb_update(Elements *self);
void bomb_interact(Elements *self, Elements *target);
void bomb_draw(Elements *self);
void bomb_destory(Elements *self);

#endif
