#include "Start.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
Elements *New_Start(int label)
{
    Start *pDerivedObj = (Start *)malloc(sizeof(Start));
    Elements *pObj = New_Elements(label);
    pDerivedObj->img = al_load_bitmap("assets/image/button_menu.png");
    pDerivedObj->x = 450;
    pDerivedObj->y = 430;
    pDerivedObj->width =al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->heigh =al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->in = -1;
    pDerivedObj->start=0;
    pDerivedObj->color = al_map_rgb(255,255,255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x-pDerivedObj->width/2,
                                     pDerivedObj->y-pDerivedObj->heigh/2,
                                     pDerivedObj->x+pDerivedObj->width/2,pDerivedObj->y+pDerivedObj->heigh/2);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf", 36, 0);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = MOUSE_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Start_draw;
    pObj->Update = Start_update;
    pObj->Interact = Start_interact;
    pObj->Destroy = Start_destory;
    return pObj;
}
void Start_update(Elements *self)
{
    
}
void Start_interact(Elements *self, Elements *tar)
{
    Start *Obj = ((Start *)(self->pDerivedObj));
    if (tar->label == MOUSE_L)
    {
       Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)){
            Obj->color=al_map_rgb(255,193,37);
            if(mouse_state[1]){
                Obj->start = 1;
                al_rest(0.1);//避免在按鈕位置產生植物
            }
        }
        else{
            Obj->color=al_map_rgb(255,255,255);
        }
    }
}
void Start_draw(Elements *self)
{
    Start *Obj = ((Start *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,0);
    al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/5, ALLEGRO_ALIGN_CENTRE, "START");
}
void Start_destory(Elements *self)
{
    Start *Obj = ((Start *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}