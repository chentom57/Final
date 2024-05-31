#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
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
    Flower_L,
    Ball_L,
    
} EleType;
typedef struct _GameScene
{
    //ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

#endif
