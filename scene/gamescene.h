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
<<<<<<< HEAD
#include "../element/Ball2.h"
=======
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
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
<<<<<<< HEAD
    Ball2_L
=======
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
    
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
