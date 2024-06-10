#include "Ball2.h"
#include "../global.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro_primitives.h>
#include "../scene/sceneManager.h"
#include "charater.h"
#include "sun.h"
#include "sunflw.h"
#include "potato.h"
#include<stdio.h>
#include<math.h>
Elements *New_Ball2(int label)
{
    Ball2 *pDerivedObj = (Ball2 *)malloc(sizeof(Ball2));
    Elements *pObj = New_Elements(label);
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->r = 15;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(255, 0, 0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     1);
    pDerivedObj->state2 = 0;
    pDerivedObj->selflw = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Flower_L;
    pObj->inter_obj[pObj->inter_len++] = Sun_L;
    pObj->inter_obj[pObj->inter_len++] = Sunflw_L;
    pObj->inter_obj[pObj->inter_len++] = Bomb_L;
    pObj->inter_obj[pObj->inter_len++] = Potato_L;
    pDerivedObj->img_g= al_load_bitmap("assets/image/mouse_green.png");
     pDerivedObj->img_y= al_load_bitmap("assets/image/mouse_yellow.png");
      pDerivedObj->img_r= al_load_bitmap("assets/image/mouse_red.png");
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
    Obj->block_y=(Obj->y)/100;
    Obj->block_x=(Obj->x)/100;
    Ball2 *chara2 = ((Ball2 *)(self->pDerivedObj));
    Elements *flo;//flower
    Elements *flo2;//sunflw
    Elements *flo3;//bomb'
    Elements *flo4;//potato
    //printf("%d", Obj -> selflw);
    // printf("ball2 = %d %d\n", Obj -> x, Obj -> y);
    al_get_mouse_state(&msstate); 
    if(mouse_state[2] == 1)
        Obj->selflw=0;
    if(key_state[ALLEGRO_KEY_0])
        Gold+=1000;
    if(chara2 -> state2 == 0){
     if(Obj->block_y<5){
        if((al_mouse_button_down(&msstate, 1)&&(mouse.x < 700))&&(Obj -> selflw == 1)&&Gold>=100&&placed[Obj->block_x][Obj->block_y]==0){
            //*mouse right button is clicked return 1
            printf("mouse left is clicked\n");
            Gold-=100;
            flo = New_Flower(Flower_L, Obj->block_x*100,Obj->block_y*100);//*generate new flower
            _Register_elements(scene, flo);
            placed[Obj->block_x][Obj->block_y]=1;
            chara2 -> state2 = 1;
            Obj -> selflw =0;
        }
        else if((al_mouse_button_down(&msstate, 1)&&(mouse.x < 700))&&(Obj -> selflw == 2)&&Gold>=50&&placed[Obj->block_x][Obj->block_y]==0){//*mouse right button is clicked return 1
            printf("mouse left is clicked1\n");
            Gold-=50;
            flo2 = New_Sunflw(Sunflw_L,Obj->block_x*100,Obj->block_y*100);//*generate new flower
            _Register_elements(scene, flo2);
            placed[Obj->block_x][Obj->block_y]=1;
            chara2 -> state2 = 1;
            Obj -> selflw =0;
        }
        else if((al_mouse_button_down(&msstate, 1)&&(mouse.x < 700))&&(mouse.y < 500)&&(Obj -> selflw == 3)&&Gold>=50&&placed[Obj->block_x][Obj->block_y]==0){//*mouse right button is clicked return 1
            printf("mouse left is clicked1\n");
            Gold-=50;
            flo3 = New_bomb(Bomb_L,Obj->block_x*100,Obj->block_y*100);//*generate new flower
            _Register_elements(scene, flo3);
            placed[Obj->block_x][Obj->block_y] = 1;
            chara2 -> state2 = 1;
            Obj -> selflw =0;
        }
        else if((al_mouse_button_down(&msstate, 1)&&(mouse.x < 700))&&(mouse.y < 500)&&(Obj -> selflw == 4)&&Gold>=50&&placed[Obj->block_x][Obj->block_y]==0){//*mouse right button is clicked return 1
            printf("potato is clicked1\n");
            Gold-=50;
            flo4 = New_potato(Potato_L,Obj->block_x*100,Obj->block_y*100);//*generate new potato
            _Register_elements(scene, flo4);
            placed[Obj->block_x][Obj->block_y] = 1;
            chara2 -> state2 = 1;
            Obj -> selflw =0;
        }
        else chara2 -> state2 = 0;
     }
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
    Obj->block_x=(Obj->x)/100;
    Obj->block_y=(Obj->y-30)/100;
    //printf("%d%d ",Obj->block_x,Obj->block_y);
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
        if ((Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox))&&(mouse_state[2] == 1))
        {
            Gold+=100;
            printf("mouse right clicked\n");
            tar -> dele = true;
            placed[Obj->block_x][Obj->block_y]=0;
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
             placed[Obj->block_x][Obj->block_y]=0;
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
        if ((Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox))&&(mouse_state[2] == 1))
        {
            Gold+=75;
            printf("mouse right clicked\n");
            tar -> dele = true;
            placed[Obj->block_x][Obj->block_y]=0;
            Obj->color = al_map_rgb(0, 0, 255);
            // Obj->in = Flower_L;
        }
        // else if (Obj->in == Flower_L)
        // {
        //     Obj->color = al_map_rgb(255, 0, 0);
        //     Obj->in = -1;
        // }
    }
    else if (tar->label ==Potato_L)
    {
        potato *Obj2 = ((potato *)(tar->pDerivedObj));
        if ((Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox))&&(mouse_state[2] == 1))
        {
            Gold+=75;
            printf("mouse right clicked\n");
            tar -> dele = true;
            placed[Obj->block_x][Obj->block_y]=0;
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
    if(Obj->selflw!=0){
        if(placed[Obj->block_x][Obj->block_y]==0)
             al_draw_bitmap(Obj->img_y, Obj->x-Obj->r, Obj->y-Obj->r,0);
        else
             al_draw_bitmap(Obj->img_r, Obj->x-Obj->r, Obj->y-Obj->r,0);
    }
    else
        al_draw_bitmap(Obj->img_g, Obj->x-Obj->r, Obj->y-Obj->r,0);
}

void Ball2_destory(Elements *self)
{
    Ball2 *Obj = ((Ball2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img_g);
      al_destroy_bitmap(Obj->img_r);
        al_destroy_bitmap(Obj->img_y);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}