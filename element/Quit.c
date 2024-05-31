#include "Quit.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
Elements *New_Quit(int label)
{
    Quit *pDerivedObj = (Quit *)malloc(sizeof(Quit));
    Elements *pObj = New_Elements(label);
    pDerivedObj->x = 450;
    pDerivedObj->y = 450;
    pDerivedObj->width =200;
    pDerivedObj->heigh=120;
    pDerivedObj->in = -1;
    pDerivedObj->Quit=0;
    pDerivedObj->color = al_map_rgb(255,236,139);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                     pDerivedObj->y-pDerivedObj->heigh/2,
                                     pDerivedObj->x+pDerivedObj->width/2,pDerivedObj->y+pDerivedObj->heigh/2);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf", 36, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = MOUSE_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Quit_draw;
    pObj->Update = Quit_update;
    pObj->Interact = Quit_interact;
    pObj->Destroy = Quit_destory;
    return pObj;
}
void Quit_update(Elements *self)
{
    
}
void Quit_interact(Elements *self, Elements *tar)
{
    Quit *Obj = ((Quit *)(self->pDerivedObj));
    if (tar->label == MOUSE_L)
    {
       Ball *Obj2 = ((Ball *)(tar->pDerivedObj));
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&mouse_state[1]){
            Obj->Quit=1;
        }
    }

}
void Quit_draw(Elements *self)
{
    Quit *Obj = ((Quit *)(self->pDerivedObj));
    al_draw_rectangle(Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,Obj->x+(Obj->width)/2,Obj->y+(Obj->heigh)/2,Obj->color,(Obj->width)/20);
    al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6, ALLEGRO_ALIGN_CENTRE, "QUIT");
}
void Quit_destory(Elements *self)
{
    Quit *Obj = ((Quit *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}