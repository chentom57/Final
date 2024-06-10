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
    pDerivedObj->x =300;  
    pDerivedObj->y = 500;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 255, 255);
    pDerivedObj->img = al_load_bitmap("assets/image/bombbutton.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/bombbutton(unable).png");
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
        if(Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&mouse_state[1]&&Gold>=150){
            printf("flwoer button is clicked\n");
            Obj2 -> selflw = 3;
            // Obj->bomb_button = 1;
        }
    }
}
void bomb_button_draw(Elements *self)
{
    bomb_button *Obj = ((bomb_button *)(self->pDerivedObj));
<<<<<<< HEAD
    al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
=======
    if(Gold>=150)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    else
        al_draw_bitmap(Obj->img2, Obj->x, Obj->y,0);
>>>>>>> a4d4daca7c8813e2266b271432af1f3e5316f78c
    // bomb_button *Obj = ((bomb_button *)(self->pDerivedObj));
    // al_draw_rectangle(Obj->x-(Obj->width)/2,Obj->y-(Obj->heigh)/2,Obj->x+(Obj->width)/2,Obj->y+(Obj->heigh)/2,Obj->color,(Obj->width)/20);
    // al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6-10, ALLEGRO_ALIGN_CENTRE, "Bomb");
    //  al_draw_text(Obj->font, Obj->color, Obj->x, Obj->y-(Obj->heigh)/6+15, ALLEGRO_ALIGN_CENTRE, "50");
}
void bomb_button_destory(Elements *self)
{
    bomb_button *Obj = ((bomb_button *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}