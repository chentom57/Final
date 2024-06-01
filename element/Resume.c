#include "Resume.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
Elements *New_Resume(int label)
{
    Resume *pDerivedObj = (Resume *)malloc(sizeof(Resume));
    Elements *pObj = New_Elements(label);
    pDerivedObj->Resume=0;
    pDerivedObj->x = 850;  
    pDerivedObj->y = 120;
    pDerivedObj->width =70;
    pDerivedObj->heigh=42;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 255, 0);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                     pDerivedObj->y-pDerivedObj->heigh/2,
                                     pDerivedObj->x+pDerivedObj->width/2,pDerivedObj->y+pDerivedObj->heigh/2);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Resume_draw;
    pObj->Update = Resume_update;
    pObj->Interact = Resume_interact;
    pObj->Destroy = Resume_destory;
    return pObj;
}
void Resume_update(Elements *self)
{
    
}
void Resume_interact(Elements *self, Elements *tar)
{
    Resume *Obj = ((Resume *)(self->pDerivedObj));
    if (tar->label == Ball_L)
    {
       Ball *Obj2 = ((Ball *)(tar->pDerivedObj));
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&mouse_state[1]){
            Obj->color=al_map_rgb(200,200,200);
            Obj->Resume=1;
        }
    }

}
void Resume_draw(Elements *self)
{
    Resume *Obj = ((Resume *)(self->pDerivedObj));
    al_draw_rectangle(Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,Obj->x+(Obj->width)/2,Obj->y+(Obj->heigh)/2,Obj->color,(Obj->width)/20);
    al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6, ALLEGRO_ALIGN_CENTRE, "Resume");
}
void Resume_destory(Elements *self)
{
    Resume *Obj = ((Resume *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}