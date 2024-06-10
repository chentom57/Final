
//Bruce add timer
#include <time.h>
time_t start_time, current_time;
#include <stdlib.h> /* 亂數相關函數 */

#include "trueboss.h"
#include "../shapes/Circle.h"

//0601:random: used for create zombie's y-axis

#include "potato.h"
#include "flower.h"
#include "sunflw.h"
/*
   [Trueboss function]
*/
Elements *New_Trueboss(int label)
{   
    /*
    if(ranflag == 1){
        srand( time(NULL) );
        ranflag = 0;
    }    
    */
    //Bruce add timer define& start
    start_time = al_get_time();

    Trueboss *pDerivedObj = (Trueboss *)malloc(sizeof(Trueboss));
    Elements *pObj = New_Elements(label);
    //  char state_string[3][10] = {"stop", "move", "attack"}; //0 stop ; 1 move ; 2 attack
    // for (int i = 0; i < 3; i++)
    // {
    //     char buffer[50];
    //     sprintf(buffer, "assets/image/Trueboss_%s.gif", state_string[i]);
    //     pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    // }
     pDerivedObj->img = al_load_bitmap("assets/image/trueboss.png");
    // load effective sound
    /*
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound2.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());
    */
    //0601:used for random create y-axis for zombie spawning
    // setting derived object member
    //pDerivedObj->img = al_load_bitmap("assets/image/Trueboss.png");
    //pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    //pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->height =200;
    pDerivedObj->width = 200;
    pDerivedObj->gameover = 0;
    pDerivedObj->x = 800;
    pDerivedObj->hp=30;
    //printf("rand: %f\n", ran_num);
    pDerivedObj->y = 0;
    pDerivedObj->v = 1; //速度
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + 60 ,
                                     pDerivedObj->y + 60  ,
                                     50 );

    pDerivedObj->hitbox2 = New_Circle(pDerivedObj->x + 60 ,
                                     pDerivedObj->y + 160  ,
                                     50 );

    pDerivedObj->hitbox3 = New_Circle(pDerivedObj->x + 60 ,
                                     pDerivedObj->y + 260  ,
                                     50 );

    pDerivedObj->hitbox4 = New_Circle(pDerivedObj->x + 60 ,
                                     pDerivedObj->y + 360  ,
                                     50 );

    pDerivedObj->hitbox5 = New_Circle(pDerivedObj->x + 60 ,
                                     pDerivedObj->y + 460  ,
                                     50 ); 
    // setting the interact object
    
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    pObj->inter_obj[pObj->inter_len++] = Potato_L;
    pObj->inter_obj[pObj->inter_len++] = Flower_L;
    pObj->inter_obj[pObj->inter_len++] = Sunflw_L;
    
   // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Trueboss_update;
    pObj->Interact = Trueboss_interact;
    pObj->Draw = Trueboss_draw;
    pObj->Destroy = Trueboss_destory;
    return pObj;
}
void Trueboss_update(Elements *self)
{
      current_time = al_get_time();

    Trueboss *Obj = ((Trueboss *)(self->pDerivedObj));
    if(Obj->hp <= 0){
        Gold+=100;
        Score+=100;
        self->dele=true;
    }

    if(((current_time - start_time)%5 )% 4== 0){
        //printf("mode 1\n");
        _Trueboss_update_position(self, Obj->v, 0);
    }
    else{ //printf("mode 2\n");
        _Trueboss_update_position(self,0, 0);
    }
    if(Obj-> x <0){
        //Bruce add: if x<0, then game over 
        printf("game over!\n");
        Obj->gameover = 1;
    }
    
}
void _Trueboss_update_position(Elements *self, float dx, float dy)
{
    Trueboss *Obj = ((Trueboss *)(self->pDerivedObj));

    //Bruce add timer
    time(&current_time);
    
    //Obj->x -=  1* dx;
    /*
    if(difftime(current_time, start_time) > 1.0){
        a= a*-1;
        start_time = current_time;
    }
    */
     Obj->x -=  1* dx;
    Shape *hitbox = Obj->hitbox;
    Shape *hitbox2 = Obj->hitbox2;
    Shape *hitbox3 = Obj->hitbox3;
    Shape *hitbox4 = Obj->hitbox4;
    Shape *hitbox5 = Obj->hitbox5;
    hitbox->update_center_x(hitbox, -1*dx);
    hitbox->update_center_y(hitbox, dy);

    hitbox2->update_center_x(hitbox2, -1*dx);
    hitbox2->update_center_y(hitbox2, dy);

    hitbox3->update_center_x(hitbox3, -1*dx);
    hitbox3->update_center_y(hitbox3, dy);

    hitbox4->update_center_x(hitbox4, -1*dx);
    hitbox4->update_center_y(hitbox4, dy);

    hitbox5->update_center_x(hitbox5, -1*dx);
    hitbox5->update_center_y(hitbox5, dy);
}
void Trueboss_interact(Elements *self, Elements *tar)
{
    Trueboss *Obj = ((Trueboss *)(self->pDerivedObj));
    if (tar->label == Floor_L)
    {
        if (Obj->x < 0 - Obj->width){        
            self->dele = true;
        }
        else if (Obj->x > WIDTH + Obj->width)
            self->dele = true;
    }
    //0610
    else if (tar->label == Flower_L)
    {
        Flower *Obj2 = ((Flower *)(tar->pDerivedObj));
        if(!Invincible){
        if (Obj->hitbox->overlap(Obj2->hitbox3, Obj->hitbox) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);
                                    
        }
         else if (Obj->hitbox2->overlap(Obj2->hitbox3, Obj->hitbox2) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox3->overlap(Obj2->hitbox3, Obj->hitbox3) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox4->overlap(Obj2->hitbox3, Obj->hitbox4) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox5->overlap(Obj2->hitbox3, Obj->hitbox5) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        }
    }

    else if (tar->label == Sunflw_L)
    {
        Sunflw *Obj2 = ((Sunflw *)(tar->pDerivedObj));
        if(!Invincible){
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox)  )
        {
            Obj2->hp = 0; //hp record in the one who attack
            //printf("sunflower hited! hp: %d\n", Obj2->hp);
                                    
        }
         else if (Obj->hitbox2->overlap(Obj2->hitbox, Obj->hitbox2) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox3->overlap(Obj2->hitbox, Obj->hitbox3) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox4->overlap(Obj2->hitbox, Obj->hitbox4) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox5->overlap(Obj2->hitbox, Obj->hitbox5) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        }
    }
    else if (tar->label == Potato_L)
    {
        potato *Obj2 = ((potato *)(tar->pDerivedObj));
        if(!Invincible){
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox)  )
        {
            Obj2->hp = 0; //hp record in the one who attack
            //printf("sunflower hited! hp: %d\n", Obj2->hp);
                                    
        }
         else if (Obj->hitbox2->overlap(Obj2->hitbox, Obj->hitbox2) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox3->overlap(Obj2->hitbox, Obj->hitbox3) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox4->overlap(Obj2->hitbox, Obj->hitbox4) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        else if (Obj->hitbox5->overlap(Obj2->hitbox, Obj->hitbox5) )
        {
            Obj2->hp = 0;; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);

        }
        }
    }


    
    // else if (tar->label == Potato_L)
    // {
    //     potato *Obj2 = ((potato *)(tar->pDerivedObj));
    //     if (Obj2->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
    //     {
    //         Obj -> v = 0;
    //         printf("hit potato");
    //         // if(Obj->hp <= 0){
    //         //     Gold+=100;
    //         //     Score+=100;
    //         //     self->dele=true;
    //         // }
    //     }
    // }
}
void Trueboss_draw(Elements *self)
{
    Trueboss *Obj = ((Trueboss *)(self->pDerivedObj));
    
  al_draw_circle(Obj->x +60 ,
                Obj->y +60  ,
                30, al_map_rgb(100, 100, 255), 10);
    al_draw_circle(Obj->x +60 ,
                Obj->y +160  ,
                30, al_map_rgb(100, 100, 255), 10);
    al_draw_circle(Obj->x +60 ,
                Obj->y +260  ,
                30, al_map_rgb(100, 100, 255), 10);
    al_draw_circle(Obj->x +60 ,
                Obj->y +360  ,
                30, al_map_rgb(100, 100, 255), 10);
    al_draw_circle(Obj->x +60 ,
                Obj->y +460  ,
                30, al_map_rgb(100, 100, 255), 10);
                 if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Trueboss_destory(Elements *self)
{
    Trueboss *Obj = ((Trueboss *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}