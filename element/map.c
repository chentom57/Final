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
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 24, 0);
    pDerivedObj->color = al_map_rgb(0, 0, 255);
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->x+pDerivedObj->width,pDerivedObj->y+pDerivedObj->height);

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;

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
   //map *Obj = ((map*)(self->pDerivedObj));
     if(tar->label==Ball2_L){
        Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
         if(Obj2->y>578-Obj2->ranges||Obj2->y<Obj2->ranges-20||Obj2->x>450)
            Obj2->lap=1;
        else
            Obj2->lap=0; 
     }

}
void map_draw(Elements *self)
{
    char Gold_text[100],score_text[100];
    map *Obj = ((map *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x,Obj->y,0);
    al_draw_line(450,0,450,Obj->height,Obj->color,0);
    sprintf(Gold_text, "%d",Gold);
    sprintf(score_text, "%d",Score);
    //al_draw_bitmap(gs->background, 0, 0, 0);
    al_draw_text(Obj->font, al_map_rgb(0,0, 0),50,20, ALLEGRO_ALIGN_CENTRE,"Gold:");
     al_draw_text(Obj->font, al_map_rgb(0, 0, 0),150,20, ALLEGRO_ALIGN_CENTRE,Gold_text );
     al_draw_text(Obj->font, al_map_rgb(0,0,0),300,20, ALLEGRO_ALIGN_CENTRE,"Score:");
     al_draw_text(Obj->font, al_map_rgb(0,0,0),400,20, ALLEGRO_ALIGN_CENTRE,score_text );
    
}
void map_destory(Elements *self)
{
    map *Obj = ((map *)(self->pDerivedObj));
    free(Obj->hitbox);
    free(Obj);
    free(self);
}