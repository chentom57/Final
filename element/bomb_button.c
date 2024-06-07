#include "bomb_button.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include "Ball2.h"
Elements *New_bomb_button(int label)
{
    bomb_button *pDerivedObj = (bomb_button *)malloc(sizeof(bomb_button));
    Elements *pObj = New_Elements(label);
    pDerivedObj->img = al_load_bitmap("assets/image/canva.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->x =340;  
    pDerivedObj->y = 560;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 255, 255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->x+pDerivedObj->width,pDerivedObj->y+pDerivedObj->height);
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
        if(Gold>=50){
        if(Obj2->selflw==3)
            Obj->color=al_map_rgb(255,255,255);
        else
            Obj->color=al_map_rgb(0,255,255);
        }
        else
            Obj->color=al_map_rgb(255,0,0);
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
    al_draw_bitmap(Obj->img,Obj->x,Obj->y,0);
    al_draw_text(Obj->font, Obj->color, Obj->x+Obj->width/2, Obj->y+Obj->height, ALLEGRO_ALIGN_CENTRE, "Bomb");
    //  al_draw_text(Obj->font, Obj->color, Obj->x+Obj->width/2, Obj->y+Obj->height/4+30, ALLEGRO_ALIGN_CENTRE, "50");
}
void bomb_button_destory(Elements *self)
{
    bomb_button *Obj = ((bomb_button *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}