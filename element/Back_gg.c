#include "Back_gg.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
Elements *New_Back_gg(int label)
{
    Back_gg *pDerivedObj = (Back_gg *)malloc(sizeof(Back_gg));
    Elements *pObj = New_Elements(label);
    if(Victory==1)
        pDerivedObj->img = al_load_bitmap("assets/image/victory_b.png");
    else
        pDerivedObj->img = al_load_bitmap("assets/image/gameover_b.png");
    pDerivedObj->width =al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->heigh =al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->Back_gg=0;
    pDerivedObj->x = 450;  
    pDerivedObj->y = 400;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(255, 255, 255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                     pDerivedObj->y-pDerivedObj->heigh/2,
                                     pDerivedObj->x+pDerivedObj->width/2,pDerivedObj->y+pDerivedObj->heigh/2);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf",28, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = MOUSE_gg_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Back_gg_draw;
    pObj->Update = Back_gg_update;
    pObj->Interact = Back_gg_interact;
    pObj->Destroy = Back_gg_destory;
    return pObj;
}
void Back_gg_update(Elements *self)
{
    
}
void Back_gg_interact(Elements *self, Elements *tar)
{
    Back_gg *Obj = ((Back_gg *)(self->pDerivedObj));
    if (tar->label == MOUSE_gg_L)
    {
       Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)){
            Obj->color=al_map_rgb(255,193,37);
            if(mouse_state[1])
                Obj->Back_gg=1;
        }
        else{
             Obj->color=al_map_rgb(255,255,255);
        }
    }

}
void Back_gg_draw(Elements *self)
{
    Back_gg *Obj = ((Back_gg *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,0);
    al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6.5, ALLEGRO_ALIGN_CENTRE, "MENU");
}
void Back_gg_destory(Elements *self)
{
    Back_gg *Obj = ((Back_gg *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}