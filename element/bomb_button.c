#include "bomb_button.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include "Ball2.h"
Elements *New_bomb_button(int label)
{
    bomb_button *pDerivedObj = (bomb_button *)malloc(sizeof(bomb_button));
    Elements *pObj = New_Elements(label);
    pDerivedObj->bomb_button=0;
    pDerivedObj->x =340;  
    pDerivedObj->y = 620;
    pDerivedObj->width =100;
    pDerivedObj->heigh=70;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 255, 255);
    pDerivedObj->img = al_load_bitmap("assets/image/bombbutton.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/bombbutton(unable).png");
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                     pDerivedObj->y-pDerivedObj->heigh/2,
                                     pDerivedObj->x+pDerivedObj->width/2,pDerivedObj->y+pDerivedObj->heigh/2);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf", 18, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = bomb_button_draw;
    pObj->Update = bomb_button_update;
    pObj->Interact = bomb_button_interact;
    pObj->Destroy = bomb_button_destory;
    return pObj;
}
void bomb_button_update(Elements *self)
{
    
}
void bomb_button_interact(Elements *self, Elements *tar)
{
    bomb_button *Obj = ((bomb_button *)(self->pDerivedObj));
    if (tar->label == Ball2_L)
    {
        Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
        if(Obj2->selflw==3)
            Obj->color=al_map_rgb(255,255,255);
        else
            Obj->color=al_map_rgb(0,255,255);
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&mouse_state[1]&&Gold>=50){
            printf("flwoer button is clicked\n");
            Obj2->lap=1;
            Obj2 -> selflw = 3;
            // Obj->bomb_button = 1;
        }
    }

}
void bomb_button_draw(Elements *self)
{
    bomb_button *Obj = ((bomb_button *)(self->pDerivedObj));
    if(Gold >= 5000){
        al_draw_bitmap(Obj->img, Obj->x - 50, Obj->y - 35,0);
    }
    else al_draw_bitmap(Obj->img2, Obj->x - 50, Obj->y - 35,0);
    // bomb_button *Obj = ((bomb_button *)(self->pDerivedObj));
    // al_draw_rectangle(Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,Obj->x+(Obj->width)/2,Obj->y+(Obj->heigh)/2,Obj->color,(Obj->width)/20);
    // al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6-10, ALLEGRO_ALIGN_CENTRE, "Bomb");
    //  al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6+15, ALLEGRO_ALIGN_CENTRE, "50");
}
void bomb_button_destory(Elements *self)
{
    bomb_button *Obj = ((bomb_button *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}