#include "sun.h"
#include "../shapes/Circle.h"
/*
   [Sun function]
*/
Elements *New_Sun(int label, int x, int y, int v)
{
    Sun *pDerivedObj = (Sun *)malloc(sizeof(Sun));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/sun.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->v = v;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     40);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Sun_update;
    pObj->Interact = Sun_interact;
    pObj->Draw = Sun_draw;
    pObj->Destroy = Sun_destory;

    return pObj;
}
void Sun_update(Elements *self)
{
    
    Sun *Obj = ((Sun *)(self->pDerivedObj));
    _Sun_update_position(self,0 , -(Obj->v));
}
void _Sun_update_position(Elements *self, int dx, int dy)
{
    Sun *Obj = ((Sun *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Sun_interact(Elements *self, Elements *tar)
{
    Sun *Obj = ((Sun *)(self->pDerivedObj));
    if (tar->label == Floor_L)
    {
        if(Obj->x < 0 - Obj->width)
            self->dele = true;
        else if(Obj->x > WIDTH + Obj->width)
            self->dele = true;
    }
    else if (tar->label == Tree_L)
    {
        Tree *tree = ((Tree *)(tar->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
}
void Sun_draw(Elements *self)
{
    Sun *Obj = ((Sun *)(self->pDerivedObj));
    al_draw_circle(Obj->x + Obj->width / 2,
                                     Obj->y + Obj->height / 2,
                                     40, al_map_rgb(255, 255, 0), 2);
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Sun_destory(Elements *self)
{
    Sun *Obj = ((Sun *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}