#include "sunflw_button.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include "Ball2.h"
Elements *New_sunflw_button(int label)
{
    sunflw_button *pDerivedObj = (sunflw_button *)malloc(sizeof(sunflw_button));
    Elements *pObj = New_Elements(label);
    pDerivedObj->img = al_load_bitmap("assets/image/flowerbutton2.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/flowerbutton2(unable).png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->x = 180;  
    pDerivedObj->y = 530;
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
       if(Gold>=150){
        if(Obj2->selflw==2)
            Obj->color=al_map_rgb(255,255,255);
        else
            Obj->color=al_map_rgb(0,255,255);
        }
        else
            Obj->color=al_map_rgb(255,0,0);
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&mouse_state[1]&&Gold>=150){
            printf("flwoer button is clicked\n");
            Obj2->lap=1;
            Obj2 -> selflw = 2;
            // Obj->sunflw_button = 1;
        }
    }
}
void sunflw_button_draw(Elements *self)
{   
    sunflw_button *Obj = ((sunflw_button *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    // if(Gold >= 50){
    //     al_draw_bitmap(Obj->img, Obj->x - 50, Obj->y - 35,0);
    // }
    // else {
    //     al_draw_bitmap(Obj->img2, Obj->x - 50, Obj->y - 35,0);
    // }
    
    // sunflw_button *Obj = ((sunflw_button *)(self->pDerivedObj));
    // al_draw_rectangle(Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,Obj->x+(Obj->width)/2,Obj->y+(Obj->heigh)/2,Obj->color,(Obj->width)/20);
    // al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6-10, ALLEGRO_ALIGN_CENTRE, "sunflw");
    // al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6+15, ALLEGRO_ALIGN_CENTRE, "150");
}
void sunflw_button_destory(Elements *self)
{
    sunflw_button *Obj = ((sunflw_button *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}