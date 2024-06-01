#include "flower_button.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
Elements *New_flower_button(int label)
{
    flower_button *pDerivedObj = (flower_button *)malloc(sizeof(flower_button));
    Elements *pObj = New_Elements(label);
    pDerivedObj->flower_button=0;
    pDerivedObj->x = 850;  
    pDerivedObj->y = 200;
    pDerivedObj->width =70;
    pDerivedObj->heigh=42;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 255, 255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                     pDerivedObj->y-pDerivedObj->heigh/2,
                                     pDerivedObj->x+pDerivedObj->width/2,pDerivedObj->y+pDerivedObj->heigh/2);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = flower_button_draw;
    pObj->Update = flower_button_update;
    pObj->Interact = flower_button_interact;
    pObj->Destroy = flower_button_destory;
    return pObj;
}
void flower_button_update(Elements *self)
{
    
}
void flower_button_interact(Elements *self, Elements *tar)
{
    flower_button *Obj = ((flower_button *)(self->pDerivedObj));
    if (tar->label == Ball_L)
    {
       Ball *Obj2 = ((Ball *)(tar->pDerivedObj));
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&mouse_state[1]){
            Obj->color=al_map_rgb(200,200,200);
            Obj->flower_button=1;
        }
    }

}
void flower_button_draw(Elements *self)
{
    flower_button *Obj = ((flower_button *)(self->pDerivedObj));
    al_draw_rectangle(Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,Obj->x+(Obj->width)/2,Obj->y+(Obj->heigh)/2,Obj->color,(Obj->width)/20);
    al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6, ALLEGRO_ALIGN_CENTRE, "flower");
}
void flower_button_destory(Elements *self)
{
    flower_button *Obj = ((flower_button *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}