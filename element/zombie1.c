
//Bruce add timer
#include <time.h>
time_t start_time, current_time;

#include "Zombie1.h"
#include "../shapes/Circle.h"
int a = 1;

/*
   [Zombie1 function]
*/
Elements *New_Zombie1(int label)
{   
    //Bruce add timer define& start
    time(&start_time);
    
    Zombie1 *pDerivedObj = (Zombie1 *)malloc(sizeof(Zombie1));
    Elements *pObj = New_Elements(label);
    // setting derived object member

    pDerivedObj->img = al_load_bitmap("assets/image/zombie1.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->gameover = 0;
    pDerivedObj->x = 800;
    pDerivedObj->y = 200;
    pDerivedObj->v = 1; //速度
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    
   // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Zombie1_update;
    pObj->Interact = Zombie1_interact;
    pObj->Draw = Zombie1_draw;
    pObj->Destroy = Zombie1_destory;

    return pObj;
}
void Zombie1_update(Elements *self)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));
    _Zombie1_update_position(self, Obj->v, Obj->v);
    if(Obj-> x <0){
        //Bruce add: if x<0, then game over //待算hitbox!
        printf("game over!\n");
        Obj->gameover = 1;
        
    }

}
void _Zombie1_update_position(Elements *self, int dx, int dy)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));

    //Bruce add timer
    time(&current_time);
    
    Obj->x -=  1* dx;
    Obj->y -= a * dy;

    if(difftime(current_time, start_time) > 1.0){
        a= a*-1;
        start_time = current_time;
    }
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Zombie1_interact(Elements *self, Elements *tar)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));
    if (tar->label == Floor_L)
    {
        if (Obj->x < 0 - Obj->width){        

            self->dele = true;
        }
        else if (Obj->x > WIDTH + Obj->width)
            self->dele = true;
    }
    else if (tar->label == Projectile_L)
    {
        Projectile *Obj2 = ((Projectile *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
        {
          //self->dele=true;
          //printf("Hit!");
    
        }
    }
}
void Zombie1_draw(Elements *self)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Zombie1_destory(Elements *self)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}