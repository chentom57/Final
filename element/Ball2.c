#include "Ball2.h"
#include "../global.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro_primitives.h>
#include "../scene/sceneManager.h"
#include "charater.h"
#include<stdio.h>
Elements *New_Ball2(int label)
{
    Ball2 *pDerivedObj = (Ball2 *)malloc(sizeof(Ball2));
    Elements *pObj = New_Elements(label);
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->r = 10;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(255, 0, 0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->r);
    pDerivedObj->state2 = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    pObj->inter_obj[pObj->inter_len++] = Flower_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Ball2_draw;
    pObj->Update = Ball2_update;
    pObj->Interact = Ball2_interact;
    pObj->Destroy = Ball2_destory;
    return pObj;
}
void Ball2_update(Elements *self)
{     
    ALLEGRO_MOUSE_STATE msstate;
    Ball2 *Obj = ((Ball2 *)(self->pDerivedObj));
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, mouse.x - Obj->x);
    hitbox->update_center_y(hitbox, mouse.y - Obj->y);
    Obj->x = mouse.x;
    Obj->y = mouse.y;
    Ball2 *chara2 = ((Ball2 *)(self->pDerivedObj));
    Elements *flo;
    al_get_mouse_state(&msstate);
    if(chara2 -> state2 == 0){
        // // if(key_state[ALLEGRO_KEY_SPACE]){
        //     printf("entered1");
        //     // flo = New_Flower(Flower_L, 100, 100);
        //     // _Register_elements(scene, flo);
        //     chara2 -> state2 = 0;
        if(al_mouse_button_down(&msstate, 1)){//*mouse right button is clicked return 1
            printf("mouse left is clicked\n");
            flo = New_Flower(Flower_L, (Obj->x) -80, (Obj->y) -80);//*generate new flower
            _Register_elements(scene, flo);
            chara2 -> state2 = 1;
        }
        else chara2 -> state2 = 0;
        // sleep(1);
    }
    else if(chara2 -> state2 == 1){
        if(al_mouse_button_down(&msstate, 1)){
            printf("mouse left is clicked\n");
            chara2 -> state2 = 1;
        }
        else chara2 -> state2 = 0;
    }
    
}
void Ball2_interact(Elements *self, Elements *tar)
{
    // printf("hello");
    Ball2 *Obj = ((Ball2 *)(self->pDerivedObj));
    // if (tar->label == Character_L)
    // {
    //     Character *Obj2 = ((Character *)(tar->pDerivedObj));

    //     if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox))
    //     {
    //         Obj->color = al_map_rgb(0, 255, 0);
    //         Obj->in = Character_L;
    //     }
    //     else if (Obj->in == Character_L)
    //     {
    //         Obj->color = al_map_rgb(255, 0, 0);
    //         Obj->in = -1;
    //     }
    // }
    if (tar->label == Flower_L)
    {
        Flower *Obj2 = ((Flower *)(tar->pDerivedObj));
        if ((Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox))&&mouse_state[2] == 1)
        {
            printf("mouse right clicked\n");
            tar -> dele = true;
            Obj->color = al_map_rgb(0, 0, 255);
            // Obj->in = Flower_L;
        }
        // else if (Obj->in == Flower_L)
        // {
        //     Obj->color = al_map_rgb(255, 0, 0);
        //     Obj->in = -1;
        // }
    }
}
void Ball2_draw(Elements *self)
{
    Ball2 *Obj = ((Ball2 *)(self->pDerivedObj));
    al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->color, 10);
}
void Ball2_destory(Elements *self)
{
    Ball2 *Obj = ((Ball2 *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}