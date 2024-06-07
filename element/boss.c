
//Bruce add timer
#include <time.h>
time_t start_time, current_time;
#include <stdlib.h> /* 亂數相關函數 */

#include "Boss.h"
#include "../shapes/Circle.h"
int boss_speed = 1;
//0601:random: used for create zombie's y-axis
int ranflag_boss = 1;
/*
   [Boss function]
*/
Elements *New_Boss(int label)
{   
    if(ranflag_boss == 1){
        srand( time(NULL) );
        ranflag_boss = 0;
    }    
    
    //Bruce add timer define& start
    time(&start_time);

    Boss *pDerivedObj = (Boss *)malloc(sizeof(Boss));
    Elements *pObj = New_Elements(label);
    
    //0601:used for random create y-axis for zombie spawning
    double ran_num = ((double)rand()/RAND_MAX);
    
    // setting derived object member

    pDerivedObj->img = al_load_bitmap("assets/image/Boss.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->gameover = 0;
    pDerivedObj->x = 800;
    pDerivedObj->hp = 5; //0607 add: boss hp

    //printf("rand: %f\n", ran_num);
    pDerivedObj->y =  ran_num * (HEIGHT-300) ;
    pDerivedObj->v = 0.5; //速度
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2 - 40,
                                     pDerivedObj->y + pDerivedObj->height / 2 - 40,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2 - 40);
    // setting the interact object
    
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    
   // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Boss_update;
    pObj->Interact = Boss_interact;
    pObj->Draw = Boss_draw;
    pObj->Destroy = Boss_destory;

    return pObj;
}
void Boss_update(Elements *self)
{

    Boss *Obj = ((Boss *)(self->pDerivedObj));
    _Boss_update_position(self, Obj->v, Obj->v);
    if(Obj-> x <0){
        //Bruce add: if x<0, then game over 
        printf("game over!\n");
        Obj->gameover = 1;
        
    }

}
void _Boss_update_position(Elements *self, float dx, float dy)
{
    Boss *Obj = ((Boss *)(self->pDerivedObj));

    //Bruce add timer
    time(&current_time);

    Obj->x -=  1* dx;
    Obj->y -=  boss_speed * dy;
    
    if((Obj ->y < 50 )){
        boss_speed = -1;
    }
    else if (Obj -> y > 530)
    {
         boss_speed = 1;
    }

    if(difftime(current_time, start_time) > 1.0){
         boss_speed=  boss_speed  * -1;
        start_time = current_time;
    }
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Boss_interact(Elements *self, Elements *tar)
{
    Boss *Obj = ((Boss *)(self->pDerivedObj));
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
            printf("Boss: ahh!");
            Obj-> hp -= 1;
            if(Obj -> hp < 1){
                Gold+=100;
                Score+=100;
                self->dele=true;                
            }                
        }
    }
}
void Boss_draw(Elements *self)
{
    Boss *Obj = ((Boss *)(self->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Boss_destory(Elements *self)
{
    Boss *Obj = ((Boss *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
