#ifndef endgame_H_INCLUDED
#define endgame_H_INCLUDED
#include "scene.h"
#include "../element/Ball.h"
#include "../element/element.h"
#include "../element/Back_gg.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
   [endgame object]
*/
typedef enum endgameEle
{
   Back_end_L,
   Resume_end_L,
   MOUSE_end_L
}endgameEle;
typedef struct _endgame
{
    ALLEGRO_FONT *font_e;
    ALLEGRO_SAMPLE *song_e;
     ALLEGRO_BITMAP *background_e;
    ALLEGRO_BITMAP *img_e;
     ALLEGRO_BITMAP *img_ee;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_e;
    int title_x_e, title_y_e;
} endgame;
Scene *New_endgame(int label);
void endgame_update(Scene *self);
void endgame_draw(Scene *self);
void endgame_destroy(Scene *self);

#endif
