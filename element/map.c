#include "map.h"
#include "../global.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>
Elements *New_map(int label)
{
    map *pDerivedObj = (map *)malloc(sizeof(map));
    Elements *pObj = New_Elements(label);
    memset(pDerivedObj->placed,0,50);
    pDerivedObj->map=0;
    pDerivedObj->img = al_load_bitmap("assets/image/map4.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->x = 0;  
    pDerivedObj->y = 0;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(0, 0, 255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->x+pDerivedObj->width,pDerivedObj->y+pDerivedObj->height);

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = map_draw;
    pObj->Update = map_update;
    pObj->Interact = map_interact;
    pObj->Destroy = map_destory;
    return pObj;
}
void map_update(Elements *self)
{
    
}
void map_interact(Elements *self, Elements *tar)
{
   

}
void map_draw(Elements *self)
{
    map *Obj = ((map *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x,Obj->y,0);
    
}
void map_destory(Elements *self)
{
    map *Obj = ((map *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}