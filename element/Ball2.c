#include "Ball2.h"
#include "../global.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro_primitives.h>
#include "../scene/sceneManager.h"
#include "charater.h"
#include "sun.h"
#include "sunflw.h"
#include<stdio.h>
Elements *New_Ball2(int label)
{
    Ball2 *pDerivedObj = (Ball2 *)malloc(sizeof(Ball2));
    Elements *pObj = New_Elements(label);
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->r = 5;
    pDerivedObj->in = -1;
    pDerivedObj->lap=0;
    pDerivedObj->color = al_map_rgb(255, 0, 0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,
                                     pDerivedObj->y,
                                    1);
    pDerivedObj->state2 = 0;
    pDerivedObj->selflw = 0;
    pDerivedObj->ranges=50;
    pDerivedObj->placed_range=New_Circle(pDerivedObj->x,pDerivedObj->y,pDerivedObj->ranges-20);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Flower_L;
    pObj->inter_obj[pObj->inter_len++] = Sun_L;
    pObj->inter_obj[pObj->inter_len++] = Sunflw_L;
    pObj->inter_obj[pObj->inter_len++] = Bomb_L;
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
    Shape *range = Obj->placed_range;
    hitbox->update_center_x(hitbox, mouse.x - Obj->x);
    hitbox->update_center_y(hitbox, mouse.y - Obj->y);
    range->update_center_x(range,mouse.x-Obj->x);
    range->update_center_y(range,mouse.y-Obj->y);
    Obj->x = mouse.x;
    Obj->y = mouse.y;
 
    Ball2 *chara2 = ((Ball2 *)(self->pDerivedObj));
    Elements *flo;
    Elements *flo2;
    Elements *flo3;
    //printf("%d", Obj -> selflw);
    //printf("ball2 = %d %d\n", Obj -> x, Obj -> y); 
    al_get_mouse_state(&msstate); 
    if(mouse_state[2] == 1)
        Obj->selflw=0;
    if(chara2 -> state2 == 0){
        // // if(key_state[ALLEGRO_KEY_SPACE]){
        //     printf("entered1");
        //     // flo = New_Flower(Flower_L, 100, 100);
        //     // _Register_elements(scene, flo);
        //     chara2 -> state2 = 0;
        if((al_mouse_button_down(&msstate, 1)&&(mouse.x < 700))&&(Obj -> selflw == 1)&&Gold>=200&&Obj->lap==0){
            //*mouse right button is clicked return 1
              printf("mouse left is clicked\n");
            double fx = round(((Obj->x) -80)/100)*100;
            double fy = round(((Obj->y) -80)/100)*100;

            Gold-=200;
            flo = New_Flower(Flower_L, fx + 30, fy + 30);//*generate new flower
            _Register_elements(scene, flo);
            chara2 -> state2 = 1;
            Obj -> selflw =0;
        }
        else if((al_mouse_button_down(&msstate, 1)&&(mouse.x < 700))&&(Obj -> selflw == 2)&&Gold>=150&&Obj->lap==0){//*mouse right button is clicked return 1
            printf("mouse left is clicked1\n");
            double fx = round(((Obj->x) -80)/100)*100;
            double fy = round(((Obj->y) -80)/100)*100;
            Gold-=150;
            flo2 = New_Sunflw(Sunflw_L, fx+ 30, fy+ 30);//*generate new flower
            _Register_elements(scene, flo2);
            chara2 -> state2 = 1;
            Obj -> selflw =0;
        }
        else if((al_mouse_button_down(&msstate, 1)&&(mouse.x < 700))&&(Obj -> selflw == 3)&&Gold>=50&&Obj->y<568){//*mouse right button is clicked return 1
             printf("mouse left is clicked1\n");
            double fx = round(((Obj->x) -20)/100)*100;
            double fy = round(((Obj->y) -20)/100)*100;
            Gold-=50;
            flo3 = New_bomb(Bomb_L, fx+ 30, fy+ 30);//*generate new flower
            _Register_elements(scene, flo3);
            chara2 -> state2 = 1;
            Obj -> selflw =0;
        }
        else chara2 -> state2 = 0;
        // sleep(1);
    }
    else if(chara2 -> state2 == 1){
        if(al_mouse_button_down(&msstate, 1)){
            printf("mouse left is clicked\n");
            chara2 -> state2 = 1;
        }
        else if(key_state[ALLEGRO_KEY_SPACE]){
            // printf("space is clicked\n");
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
    if(Obj->y>578-Obj->ranges||Obj->y<Obj->ranges-20||Obj->x>450)
            Obj->lap=1;
    if (tar->label == Flower_L)
    {
        Flower *Obj2 = ((Flower *)(tar->pDerivedObj));
        if(Obj->placed_range->overlap(Obj->placed_range, Obj2->hitbox))
            Obj->lap=1;
        if ((Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox))&&(mouse_state[2] == 1))
        {
            Gold+=100;
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
    else if (tar->label == Sun_L)
    {
        // printf("entered new sun");
        Sun *Obj2 = ((Sun *)(tar->pDerivedObj));
        if ((Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox))&&(mouse_state[1] == 1))
        {
            Gold+=50;
            printf("mouse right clicked2\n");
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
    else if (tar->label == Sunflw_L)
    {
        Sunflw *Obj2 = ((Sunflw *)(tar->pDerivedObj));
        if(Obj->placed_range->overlap(Obj->placed_range, Obj2->hitbox))
            Obj->lap=1;
        if ((Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox))&&(mouse_state[2] == 1))
        {
            Gold+=75;
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
    al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->color, 5);
    if((Obj->selflw==1)||(Obj->selflw==2)){
        if((Obj->lap)==1)
            al_draw_circle(Obj->x,Obj->y,Obj->ranges - 20,al_map_rgb(255,0,0),5);
        else
            al_draw_circle(Obj->x,Obj->y,Obj->ranges - 20,al_map_rgb(0,255,0),2);
    }
}
void Ball2_destory(Elements *self)
{
    Ball2 *Obj = ((Ball2 *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}