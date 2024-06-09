
//Bruce add timer
#include <time.h>
time_t start_time, current_time;
#include <stdlib.h> /* 亂數相關函數 */
#include "potato.h"
#include "Zombie1.h"
#include "../shapes/Circle.h"
int a = 1;
//0601:random: used for create zombie's y-axis
int ranflag = 1;
/*
   [Zombie1 function]
*/
Elements *New_Zombie1(int label)
{   
    if(ranflag == 1){
        srand( time(NULL) );
        ranflag = 0;
    }    
    
    //Bruce add timer define& start
    time(&start_time);

    Zombie1 *pDerivedObj = (Zombie1 *)malloc(sizeof(Zombie1));
    Elements *pObj = New_Elements(label);
    
    //0601:used for random create y-axis for zombie spawning
    int ran_num = (rand() % 5);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/zombie1.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->gameover = 0;
    pDerivedObj->x = 800;
    pDerivedObj->hp=5;
    //printf("rand: %f\n", ran_num);
    pDerivedObj->y =  ran_num * 100 ;
    pDerivedObj->v = 1; //速度
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2.5 + 30,
                                     pDerivedObj->y + pDerivedObj->height / 2.5 + 20 ,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2.5 );
    // setting the interact object
    
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    pObj->inter_obj[pObj->inter_len++] = Potato_L;
    
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
    _Zombie1_update_position(self, Obj->v, 0);
    if(Obj-> x <0){
        //Bruce add: if x<0, then game over 
        printf("game over!\n");
        Obj->gameover = 1;
    }
}
void _Zombie1_update_position(Elements *self, float dx, float dy)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));

    //Bruce add timer
    time(&current_time);
    
    Obj->x -=  1* dx;
    Obj->y -= a * dy;
    
    if((Obj ->y < 50 )){
       a = -1;
    }
    else if (Obj -> y > 530)
    {
        a = 1;
    }

    if(difftime(current_time, start_time) > 1.0){
        a= a*-1;
        start_time = current_time;
    }
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, -1*dx);
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
            Obj->hp--;
            printf("Hit! hp: %d\n", Obj->hp);
            if(Obj->hp <= 0){
                Gold+=100;
                Score+=100;
                self->dele=true;
            }
        }
    }
    else if (tar->label == Potato_L)
    {
        potato *Obj2 = ((potato *)(tar->pDerivedObj));
        if (Obj2->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
        {
            Obj -> v = 0;
            printf("hit potato");
            // if(Obj->hp <= 0){
            //     Gold+=100;
            //     Score+=100;
            //     self->dele=true;
            // }
        }
    }
}
void Zombie1_draw(Elements *self)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));
    al_draw_circle(Obj->x + Obj->width / 2.5 + 30,
                                     Obj->y + Obj->height / 2.5 + 20 ,
                                     min(Obj->width,Obj->height) / 2.5 , al_map_rgb(255, 255, 255), 3);
    
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