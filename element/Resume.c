#include "Resume.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
Elements *New_Resume(int label)
{
    Resume *pDerivedObj = (Resume *)malloc(sizeof(Resume));
    Elements *pObj = New_Elements(label);
    pDerivedObj->Resume=0;
     pDerivedObj->x = 670;  
    pDerivedObj->y = 500;
    pDerivedObj->img = al_load_bitmap("assets/image/fi_b.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 0, 139);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->x+pDerivedObj->width ,pDerivedObj->y+pDerivedObj->height);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf",18, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;

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
    if (tar->label == Ball2_L)
    {
       Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
       if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)){
            Obj->color=al_map_rgb(0,0,139);
            if(mouse_state[1]){
                Obj->Resume=1;
                self->dele=true;
            }
        }
        else{
             Obj->color=al_map_rgb(255,255,255);
        }
    }

}
void Resume_draw(Elements *self)
{
    Resume *Obj = ((Resume *)(self->pDerivedObj));
   al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    al_draw_text(Obj->font, Obj->color, Obj->x+(Obj->width)/2, Obj->y+(Obj->height)/3, ALLEGRO_ALIGN_CENTRE, "again");
}
void Resume_destory(Elements *self)
{
    Resume *Obj = ((Resume *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}