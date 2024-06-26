
//Bruce add timer
#include <time.h>
time_t start_time, current_time;
#include <stdlib.h> /* 亂數相關函數 */

#include "Zomboni.h"
#include "../shapes/Circle.h"

//0601:random: used for create zombie's y-axis

#include "potato.h"
#include "flower.h"
#include "sunflw.h"
/*
   [Zomboni function]
*/
Elements *New_Zomboni(int label)
{   
    /*
    if(ranflag == 1){
        srand( time(NULL) );
        ranflag = 0;
    }    
    */
    //Bruce add timer define& start
    time(&start_time);

    Zomboni *pDerivedObj = (Zomboni *)malloc(sizeof(Zomboni));
    
    Elements *pObj = New_Elements(label);
    /*
     char state_string[3][10] = {"stop", "move", "attack"}; //0 stop ; 1 move ; 2 attack
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/zomboni_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    */
    // load effective sound
    /*
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound2.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());
    */
    //0601:used for random create y-axis for zombie spawning
    int ran_num = (rand() % 5);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/zomboni.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->height =200;
    pDerivedObj->width = 200;
    pDerivedObj->gameover = 0;
    pDerivedObj->x = 800;
    pDerivedObj->hp=3;
    pDerivedObj->stop=0;
    //printf("rand: %f\n", ran_num);
    pDerivedObj->y =  ran_num * 100 -20;
    pDerivedObj->v = 2; //速度
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2.5 - 25 ,
                                     pDerivedObj->y + pDerivedObj->height /2.5-12 ,
                                     40 );
    // setting the interact object
    
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;
    pObj->inter_obj[pObj->inter_len++] = Potato_L;
    pObj->inter_obj[pObj->inter_len++] = Flower_L;
    pObj->inter_obj[pObj->inter_len++] = Sunflw_L;
    
   // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Zomboni_update;
    pObj->Interact = Zomboni_interact;
    pObj->Draw = Zomboni_draw;
    pObj->Destroy = Zomboni_destory;
    return pObj;
}
void Zomboni_update(Elements *self)
{

    Zomboni *Obj = ((Zomboni *)(self->pDerivedObj));
    if(Obj->hp <= 0){
        Gold+=100;
        Score+=100;
        self->dele=true;
    }
    if(Obj->stop==0){
        _Zomboni_update_position(self, Obj->v, 0);
    }
     if(placed[(int)(Obj->x + 100)/ 100][(int)Obj->y / 100] == 1){
        
        
    }
    
    if(Obj-> x <0){
        //Bruce add: if x<0, then game over 
        printf("game over!\n");
        Obj->gameover = 1;
    }
}
void _Zomboni_update_position(Elements *self, float dx, float dy)
{
    Zomboni *Obj = ((Zomboni *)(self->pDerivedObj));

    //Bruce add timer
    time(&current_time);
    
    //Obj->x -=  1* dx;
    /*
    if(difftime(current_time, start_time) > 1.0){
        a= a*-1;
        start_time = current_time;
    }
    */
    
    Obj->x -= dx;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, -1*dx);
    hitbox->update_center_y(hitbox, dy);
    
    /*
    else{
        Obj->x += 0;
        Shape *hitbox = Obj->hitbox;
        hitbox->update_center_x(hitbox,0);
        hitbox->update_center_y(hitbox, dy);
    }*/

    Obj->y += dy;
}
void Zomboni_interact(Elements *self, Elements *tar)
{
    Zomboni *Obj = ((Zomboni *)(self->pDerivedObj));
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
            //Obj->hp--;
            //printf("Hit! hp: %d\n", Obj->hp);
                                    
        }
    }
    //0610
    else if (tar->label == Flower_L)
    {
        Flower *Obj2 = ((Flower *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox3, Obj->hitbox) &&!Invincible)
        {
            Obj2->hp = 0; //hp record in the one who attack
            //printf("flower hited! hp: %d\n", Obj2->hp);
                                    
        }
    }

    else if (tar->label == Sunflw_L)
    {
        Sunflw *Obj2 = ((Sunflw *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox)&&!Invincible )
        {
            Obj2->hp = 0; //hp record in the one who attack
            //printf("sunflower hited! hp: %d\n", Obj2->hp);
                                    
        }
    }
    else if (tar->label == Potato_L)
    {
        potato *Obj2 = ((potato *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox) )
        {
            Obj->stop=1;
           if(!Invincible)
                Obj2->hp-=2; //hp record in the one who attack
            //printf("sunflower hited! hp: %d\n", Obj2->hp);

        }
        else if(placed[Obj->x/100][(Obj->y+20)/100]!=2){
                Obj->stop=0;
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
void Zomboni_draw(Elements *self)
{
    Zomboni *Obj = ((Zomboni *)(self->pDerivedObj));
  
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y,0);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
        /*
      al_draw_circle(Obj->x +Obj->width / 2.5 - 25 ,
                                   Obj->y +Obj->height /2.5-12 ,
                                     40 , al_map_rgb(100, 100, 255), 5);
    */
    /*
   ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->gif_status[Obj->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, Obj->x, Obj->y, 0);
    }
    if (Obj->state == ATK && Obj->gif_status[Obj->state]->display_index == 2)
    {
        al_play_sample_instance(Obj->atk_Sound);
    }
    */
}
void Zomboni_destory(Elements *self)
{
    Zomboni *Obj = ((Zomboni *)(self->pDerivedObj));
    
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);

    /*
     al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
    */
}