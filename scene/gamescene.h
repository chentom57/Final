#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "time.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/Ball.h"
#include "../element/Back.h"
#include "../element/Resume.h"
#include "../element/map.h"
#include "../element/flower.h"
#include "../element/Ball2.h"
#include "../element/flower_button.h"
#include "../element/sunflw_button.h"
#include "../element/Zombie1.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [game scene object]
*/
typedef enum EleType
{
    Map_L,
    Floor_L,
    Teleport_L,
    Tree_L,
    
    Character_L,
    Projectile_L,
    Back_L,
    Resume_L,
    FlowerB_L,
    Flower_L,
    Sun_L,
    Sunflw_L,
    Zombie1_L,
    SunflwB_L,
    Ball_L,
    Ball2_L
    
} EleType;
typedef struct _GameScene
{
    //ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font2;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    char text[100];
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);
void game_scene_zombie(Scene *self); //zombie creating schedule
#endif
