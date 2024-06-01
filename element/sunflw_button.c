#include "sunflw_button.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include "Ball2.h"
Elements *New_sunflw_button(int label)
{
    sunflw_button *pDerivedObj = (sunflw_button *)malloc(sizeof(sunflw_button));
    Elements *pObj = New_Elements(label);
    pDerivedObj->sunflw_button=0;
    pDerivedObj->x = 850;  
    pDerivedObj->y = 250;
    pDerivedObj->width =70;
    pDerivedObj->heigh=42;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 255, 255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                     pDerivedObj->y-pDerivedObj->heigh/2,
                                     pDerivedObj->x+pDerivedObj->width/2,pDerivedObj->y+pDerivedObj->heigh/2);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = sunflw_button_draw;
    pObj->Update = sunflw_button_update;
    pObj->Interact = sunflw_button_interact;
    pObj->Destroy = sunflw_button_destory;
    return pObj;
}
void sunflw_button_update(Elements *self)
{

}
void sunflw_button_interact(Elements *self, Elements *tar)
{
    sunflw_button *Obj = ((sunflw_button *)(self->pDerivedObj));
    if (tar->label == Ball2_L)
    {
       Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&mouse_state[1]){
            printf("flwoer button is clicked\n");
            Obj->color=al_map_rgb(200,200,200);
            Obj2 -> selflw = 2;
            // Obj->sunflw_button = 1;
        }
    }
}
void sunflw_button_draw(Elements *self)
{
    sunflw_button *Obj = ((sunflw_button *)(self->pDerivedObj));
    al_draw_rectangle(Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,Obj->x+(Obj->width)/2,Obj->y+(Obj->heigh)/2,Obj->color,(Obj->width)/20);
    al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6, ALLEGRO_ALIGN_CENTRE, "sunflw");
}
void sunflw_button_destory(Elements *self)
{
    sunflw_button *Obj = ((sunflw_button *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}