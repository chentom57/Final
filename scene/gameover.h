#ifndef gameover_H_INCLUDED
#define gameover_H_INCLUDED
#include "scene.h"
#include "../element/Ball.h"
#include "../element/element.h"
#include "../element/Back_gg.h"
#include "../element/Resume.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
   [gameover object]
*/
typedef enum gameoverEle
{
   Back_gg_L,
   Resume_gg_L,
   MOUSE_gg_L
}gameoverEle;
typedef struct _gameover
{
    ALLEGRO_FONT *font_g;
    ALLEGRO_SAMPLE *song_g;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance_g;
    int title_x_g, title_y_g;
} gameover;
Scene *New_gameover(int label);
void gameover_update(Scene *self);
void gameover_draw(Scene *self);
void gameover_destroy(Scene *self);

#endif
