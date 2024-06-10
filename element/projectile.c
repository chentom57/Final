#include "projectile.h"
#include "../shapes/Circle.h"
/*
   [Projectile function]
*/
Elements *New_Projectile(int label, int x, int y, int v)
{
    Projectile *pDerivedObj = (Projectile *)malloc(sizeof(Projectile));
    Elements *pObj = New_Elements(label);
    pDerivedObj->hp = 1;//0607 add
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/projectile.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->v = v;
    pDerivedObj->hp = 1;//0607 add
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     10);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Zombie1_L;
    pObj->inter_obj[pObj->inter_len++] = Zomboni_L; //0610
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Projectile_update;
    pObj->Interact = Projectile_interact;
    pObj->Draw = Projectile_draw;
    pObj->Destroy = Projectile_destory;
    return pObj;
}
void Projectile_update(Elements *self)
{
    
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    self->label=Projectile_L;
    if(Obj -> x > 850){
        self -> dele = true;
    }
    _Projectile_update_position(self, Obj->v, 0);
}
void _Projectile_update_position(Elements *self, int dx, int dy)
{
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Projectile_interact(Elements *self, Elements *tar)
{
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    // if (tar->label == Zombie1_L)
    // {
    //     Zombie1 *zomb = ((Zombie1*)(tar->pDerivedObj));
    //     if (zomb->hitbox->overlap(zomb->hitbox, Obj->hitbox))
    //     {
    //         printf("zombie hitted\n");
    //         self->dele = true;
    //     }
    //     // if(Obj->x < 0 - Obj->width)
    //     //     self->dele = true;
    //     // else if(Obj->x > WIDTH + Obj->width)
    //     //     self->dele = true;
    // }
    //0607 add: boss and zombie -hpS
    if (tar->label == Boss_L)
    {
        Boss *Obj2 = ((Boss *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
        {
            printf("bullet: ahh!");
            Obj-> hp -= 1;
            if(Obj -> hp < 1){
                //Gold+=100;
                //Score+=100;
                self->dele=true;                
            }                
        }
    }
    else if (tar->label == Zombie1_L)
    {
        Zombie1 *Obj2 = ((Zombie1 *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
        {
            printf("projt hitted zombie\n");
            Obj2-> hp -= 1;
            
            // if(Obj -> hp < 1){
            //     //Gold+=100;
            //     //Score+=100;
                                
            // }
            self->dele=true;                
        }
    }
    else if (tar->label == Zomboni_L)
    {
        Zomboni *Obj2 = ((Zomboni *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
        {
            printf("Zomboni hitted zombie\n");
            Obj2-> hp -= 1;
            
            // if(Obj -> hp < 1){
            //     //Gold+=100;
            //     //Score+=100;
                                
            // }
            self->dele=true;                
        }
    }

}
void Projectile_draw(Elements *self)
{
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    al_draw_circle(Obj->x + Obj->width / 2,
                                     Obj->y + Obj->height / 2,
                                     10, al_map_rgb(255, 0, 0), 2);
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Projectile_destory(Elements *self)
{
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
