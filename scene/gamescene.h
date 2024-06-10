// #ifndef GAMESCENE_H_INCLUDED
// #define GAMESCENE_H_INCLUDED
// #include "scene.h"
// #include "time.h"
// #include "../element/element.h"
// #include "../element/charater.h"
// #include "../element/floor.h"
// #include "../element/teleport.h"
// #include "../element/tree.h"
// #include "../element/projectile.h"
// #include "../element/Ball.h"
// #include "../element/Back.h"
// #include "../element/Resume.h"
// #include "../element/map.h"
// #include "../element/flower.h"
// #include "../element/Boss.h"
// #include "../element/bomb.h"
// #include "../element/Ball2.h"
// #include "../element/flower_button.h"
// #include "../element/sunflw_button.h"
// #include "../element/bomb_button.h"
// #include "../element/potato_button.h"
// #include "../element/Zombie1.h"
// #include "../element/Lottery.h"
// #include <allegro5/allegro_audio.h>
// #include <allegro5/allegro_acodec.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>
// #include "../element/Boss.h"

// /*
//    [game scene object]
// */
// typedef enum EleType
// {
//     Map_L,
//     Floor_L,
//     Teleport_L,
//     Tree_L,
    
//     Character_L,
//     Projectile_L,
//     Back_L,
//     Resume_L,
//     FlowerB_L,
//     Flower_L,
//     BombB_L,
  
//     Sun_L,
//     Sunflw_L,
//     Zombie1_L,
//     Bomb_L,
//     Potato_L,
//     PotatoB_L,

//     SunflwB_L,
//     Lottery_L,
//     Ball_L,
//     Ball2_L,
//     Boss_L
    
// } EleType;
// typedef struct _GameScene
// {
//     int lottery_created;
//     //ALLEGRO_BITMAP *background;
//     ALLEGRO_FONT *font;
//     ALLEGRO_FONT *font2;
//     ALLEGRO_SAMPLE *song;
//     ALLEGRO_BITMAP *background_gs;
//     ALLEGRO_BITMAP *sun_t;
//      ALLEGRO_BITMAP *Gold_score;
//     ALLEGRO_SAMPLE_INSTANCE *gs_Sound;
//     ALLEGRO_SAMPLE_INSTANCE *sample_instance;
//     char text[100];
// } GameScene;
// Scene *New_GameScene(int label);
// void game_scene_update(Scene *self);
// void game_scene_draw(Scene *self);
// void game_scene_destroy(Scene *self);
// void game_scene_zombie(Scene *self); //zombie creating schedule
// void game_scene_lottery(Scene *self);
// #endif

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
#include "../element/Boss.h"
#include "../element/bomb.h"
#include "../element/Ball2.h"
#include "../element/zomboni.h"
#include "../element/flower_button.h"
#include "../element/sunflw_button.h"
#include "../element/bomb_button.h"
#include "../element/potato_button.h"
#include "../element/Trueboss.h"
#include "../element/Zombie1.h"
#include "../element/Lottery.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../element/Boss.h"

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
    BombB_L,
  
    Sun_L,
    Sunflw_L,
    Bomb_L,
    Potato_L,
    PotatoB_L,

    Zombie1_L,
    Trueboss_L,
    Zomboni_L,
    SunflwB_L,
    Lottery_L,
    Ball2_L
  
    
} EleType;
typedef struct _GameScene
{
    int lottery_created;
    //ALLEGRO_BITMAP *background;
      int end_time;
    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font2;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_BITMAP *background_gs;
     ALLEGRO_BITMAP *timer_bar;
      ALLEGRO_BITMAP *time_spot;
    ALLEGRO_BITMAP *sun_t;
     ALLEGRO_BITMAP *coin;
     ALLEGRO_BITMAP *Gold_score;
      ALLEGRO_BITMAP *vvc;
    ALLEGRO_SAMPLE_INSTANCE *gs_Sound;
    char text[100];
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);
void game_scene_zombie(Scene *self); //zombie creating schedule
void game_scene_lottery(Scene *self);
#endif