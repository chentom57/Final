#include "Back.h"

Elements *New_Back(int label)
{
    Back *pDerivedObj = (Back *)malloc(sizeof(Back));
    Elements *pObj = New_Elements(label);
    pDerivedObj->back=0;
    pDerivedObj->x = 790;  
    pDerivedObj->y = 500;
    pDerivedObj->img = al_load_bitmap("assets/image/fi_b.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 0, 139);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->x+pDerivedObj->width ,pDerivedObj->y+pDerivedObj->height);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf", 18, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Back_draw;
    pObj->Update = Back_update;
    pObj->Interact = Back_interact;
    pObj->Destroy = Back_destory;
    return pObj;
}
void Back_update(Elements *self)
{
    
}
void Back_interact(Elements *self, Elements *tar)
{
    Back *Obj = ((Back *)(self->pDerivedObj));
    if (tar->label == Ball2_L)
    {
       Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
       if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)){
            Obj->color=al_map_rgb(0,0,139);
            if(mouse_state[1]){
                Obj->back=1;
                self->dele=true;
            }
        }
        else{
             Obj->color=al_map_rgb(135,51,0);
        }
    }

}
void Back_draw(Elements *self)
{
    Back *Obj = ((Back *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    al_draw_text(Obj->font, Obj->color, Obj->x+(Obj->width)/2, Obj->y+(Obj->height)/3, ALLEGRO_ALIGN_CENTRE, "BACK");
}
void Back_destory(Elements *self)
{
    Back *Obj = ((Back *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}