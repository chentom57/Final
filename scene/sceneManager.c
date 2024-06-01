#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "gameover.h"
#include "endgame.h"
Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
    case Gameover_L:
        scene=New_gameover(Gameover_L);
        break;
    case Endgame_L:
        scene=New_endgame(Endgame_L);
        break;
    default:
        break;
    }
}