
//Bruce add timer
#include <time.h>
time_t start_time, current_time;
#include <stdlib.h> /* 亂數相關函數 */

#include "Zombie1.h"
#include "../shapes/Circle.h"
int a = 1;
//0601:random: used for create zombie's y-axis
int ranflag = 1;
#include "potato.h"
#include "flower.h"
#include "sunflw.h"
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
     char state_string[3][10] = {"stop", "move", "attack"}; //0 stop ; 1 move ; 2 attack
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/zombie1_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound2.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());
    //0601:used for random create y-axis for zombie spawning
    int ran_num = (rand() % 5);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/zombie1.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->gameover = 0;
    pDerivedObj->x = 800;
    pDerivedObj->hp=8;
    //printf("rand: %f\n", ran_num);
    pDerivedObj->y =  ran_num * 100 ;
    pDerivedObj->v = 1; //速度
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2.5 + 60,
                                     pDerivedObj->y + pDerivedObj->height / 2.5 + 20 ,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2.5 );
    // setting the interact object
    
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    pObj->inter_obj[pObj->inter_len++] = Potato_L;
    pObj->inter_obj[pObj->inter_len++] = Flower_L;
    pObj->inter_obj[pObj->inter_len++] = Sunflw_L;
    
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
    if(Obj->hp <= 0){
        Gold+=100;
        Score+=100;
        self->dele=true;
    }


    _Zombie1_update_position(self, Obj->v, 0);
     if(placed[(int)(Obj->x + 100)/ 100][(int)Obj->y / 100] == 1){
        Obj->state = ATK;
        
    }
    else{
        Obj->state = MOVE;
    }

    if(Obj-> x <-50){
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
    
    //Obj->x -=  1* dx;
    if(difftime(current_time, start_time) > 1.0){
        a= a*-1;
        start_time = current_time;
    }
    if(Obj->state == MOVE){
        Obj->x -=  1* dx;
        Shape *hitbox = Obj->hitbox;
        hitbox->update_center_x(hitbox, -1*dx);
        hitbox->update_center_y(hitbox, dy);
    }
    else{
        Obj->x += 0;
        Shape *hitbox = Obj->hitbox;
        hitbox->update_center_x(hitbox,0);
        hitbox->update_center_y(hitbox, dy);
    }
    Obj->y += dy;
}
void Zombie1_interact(Elements *self, Elements *tar)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));
    if (tar->label == Projectile_L)
    {
        Projectile *Obj2 = ((Projectile *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
        {
            //Obj->hp--;
            //printf("Hit! hp: %d\n", Obj->hp);
                                    
        }
    }
    //0610
    else if (tar->label == Flower_L)
    {
        Flower *Obj2 = ((Flower *)(tar->pDerivedObj));
<<<<<<< HEAD
        if (Obj->hitbox->overlap(Obj2->hitbox3, Obj->hitbox) )
=======
        if (Obj->hitbox->overlap(Obj2->hitbox3, Obj->hitbox)&&!Invincible)
>>>>>>> a4d4daca7c8813e2266b271432af1f3e5316f78c
        {
            Obj2->hp--; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);
                                    
        }
    }
    
    else if (tar->label == Sunflw_L)
    {
        Sunflw *Obj2 = ((Sunflw *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox) &&!Invincible )
        {
            Obj2->hp--; //hp record in the one who attack
            //printf("sunflower hited! hp: %d\n", Obj2->hp);

        }
    }
    else if (tar->label == Potato_L)
    {
        potato *Obj2 = ((potato *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox)&&!Invincible )
        {
            Obj2->hp--; //hp record in the one who attack
            //printf("sunflower hited! hp: %d\n", Obj2->hp);

        }
    }


    else if (tar->label == Sunflw_L)
    {
        Sunflw *Obj2 = ((Sunflw *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox)  )
        {
            Obj2->hp--; //hp record in the one who attack
            //printf("sunflower hited! hp: %d\n", Obj2->hp);
                                    
        }
    }
    else if (tar->label == Potato_L)
    {
        potato *Obj2 = ((potato *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox)  )
        {
            Obj2->hp--; //hp record in the one who attack
            printf("potato hited! hp: %d\n", Obj2->hp);
                                    
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
void Zombie1_draw(Elements *self)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));
    al_draw_circle(Obj->x + Obj->width / 2.5 + 60,
                                     Obj->y + Obj->height / 2.5 + 20 ,
                                     min(Obj->width,Obj->height) / 2.5 , al_map_rgb(255, 255, 255), 3);
    
   ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->gif_status[Obj->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, Obj->x, Obj->y, 0);
    }
    if (Obj->state == ATK && Obj->gif_status[Obj->state]->display_index == 2)
    {
        al_play_sample_instance(Obj->atk_Sound);
    }
}
void Zombie1_destory(Elements *self)
{
    Zombie1 *Obj = ((Zombie1 *)(self->pDerivedObj));
     al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}