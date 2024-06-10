#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "scene.h"
#include "../element/Ball.h"
#include "../element/Start.h"
#include "../element/Quit.h"
#include "../element/element.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
   [Menu object]
*/
typedef enum MenuEle
{
   Quit_L,
   START_L,
   MOUSE_L
}MenuEle;
typedef struct _Menu
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *img;
   ALLEGRO_BITMAP *img1;
   ALLEGRO_BITMAP *img2;
    ALLEGRO_SAMPLE_INSTANCE *menu_Sound;
    ALGIF_ANIMATION *gif_status[3];
    int title_x_z, title_x_p;
} Menu;
Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu_draw(Scene *self);
void menu_destroy(Scene *self);

#endif
