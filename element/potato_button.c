#include "potato_button.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
#include "Ball2.h"
Elements *New_potato_button(int label)
{
    potato_button *pDerivedObj = (potato_button *)malloc(sizeof(potato_button));
    Elements *pObj = New_Elements(label);
    pDerivedObj->img = al_load_bitmap("assets/image/flowerbutton3.png");
     pDerivedObj->img2 = al_load_bitmap("assets/image/flowerbutton3(unable).png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->x =420;  
    pDerivedObj->y = 500;
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
    pObj->Draw = potato_button_draw;
    pObj->Update = potato_button_update;
    pObj->Interact = potato_button_interact;
    pObj->Destroy = potato_button_destory;
    return pObj;
}
void potato_button_update(Elements *self)
{
    
}
void potato_button_interact(Elements *self, Elements *tar)
{
    potato_button *Obj = ((potato_button *)(self->pDerivedObj));
    if (tar->label == Ball2_L)
    {
        Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&mouse_state[1]&&Gold>=50){
            printf("flwoerbutton3 button is clicked\n");
            Obj2 -> selflw = 4;
            // Obj->potato_button = 1;
        }
    }

}
void potato_button_draw(Elements *self)
{
    potato_button *Obj = ((potato_button *)(self->pDerivedObj));
      if(Gold>=50)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    else
        al_draw_bitmap(Obj->img2, Obj->x, Obj->y,0);
    // potato_button *Obj = ((potato_button *)(self->pDerivedObj));
    // al_draw_rectangle(Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,Obj->x+(Obj->width)/2,Obj->y+(Obj->heigh)/2,Obj->color,(Obj->width)/20);
    // al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6-10, ALLEGRO_ALIGN_CENTRE, "Flower");
    //  al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6+15, ALLEGRO_ALIGN_CENTRE, "200");
}
void potato_button_destory(Elements *self)
{
    potato_button *Obj = ((potato_button *)(self->pDerivedObj));
     al_destroy_bitmap(Obj->img);
    al_destroy_bitmap(Obj->img2);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}