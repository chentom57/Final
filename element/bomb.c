#include "charater.h"
#include "bomb.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
/*
   [bomb function]
*/
//hello
time_t start_time_bo,current_time_bo; 
Elements *New_bomb(int label, int x, int y)
{
    bomb *pDerivedObj = (bomb *)malloc(sizeof(bomb));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load bomb images
    // char state_string[3][10] = {"stop", "move", "attack"};
    // for (int i = 0; i < 3; i++)
    // {
    //     char buffer[50];
    //     sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
    //     pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    // }
    // load effective sound
    //ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.mp3");
    pDerivedObj->img = al_load_bitmap("assets/image/bomb.png");
      pDerivedObj->img2= al_load_bitmap("assets/image/bang.png");
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/bang_sound.mp3");
     pDerivedObj->bang_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->bang_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->bang_Sound, al_get_default_mixer());

    // initial the geometric information of bomb
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height =al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->color = al_map_rgb(255, 0, 0);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf",24, 0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x+50,
                                        pDerivedObj->y+50,150);
    pDerivedObj->dir = true; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->sound_played = 0;
    pObj->pDerivedObj = pDerivedObj;
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;
    pObj->inter_obj[pObj->inter_len++] = Zombie1_L;
      pObj->inter_obj[pObj->inter_len++] =Zombie1_L;
    // setting derived object function
    pObj->Draw = bomb_draw;
    pObj->Update = bomb_update;
    pObj->Interact = bomb_interact;
    pObj->Destroy = bomb_destory;
    start_time_bo=time(NULL);
    pDerivedObj->start_local=(long)start_time_bo;
    return pObj;
}
void bomb_placing(int x, int y){
//     if(key_state[ALLEGRO_KEY_SPACE]){
//         printf("spcae is pressed");
//         New_bomb(bomb_L, 1, 1);
//     }
// }
}
void bomb_update(Elements *self)
{
    //bomb *Obj = ((bomb *)(self->pDerivedObj));
    // use the idea of finite state machine to deal with different state
    // if(key_state[ALLEGRO_KEY_SPACE]){
    //     printf("spcae is pressed");
    //     //New_bomb(bomb_L, 1, 1);
    //     sleep(1);
    // }
    // if(mouse_state[2] == 1){
    //     printf("mouse right clicked");
    // }
    // chara->state = ATK;
    // if (chara->gif_status[chara->state]->done)
    //     {
    //         chara->state = STOP;
    //         chara->new_proj = false;
    //     }
    //     if (chara->gif_status[ATK]->display_index == 1 && chara->new_proj == false)
    //     {
    //         Elements *pro;
    //         // Elements *pro2;
    //         if (chara->dir)
    //         {
    //             pro = New_Projectile(Projectile_L,
    //                                  chara->x + chara->width - 100,
    //                                  chara->y - 10,
    //                                  5);
    //             // printf("enterd");
    //             // pro2 = New_bomb(bomb_L, 100, 100);
    //             // _Register_elements(scene, pro2);
    //         }
    //         else
    //         {
    //             pro = New_Projectile(Projectile_L,
    //                                  chara->x - 50,
    //                                  chara->y - 10,
    //                                  -5);
    //         }
    //         _Register_elements(scene, pro);
    //         chara->new_proj = true;
    //     }
    //     chara->state = ATK;
    // if (chara->state == STOP)
    // {
    //     // chara->state = ATK;
    //     if (key_state[ALLEGRO_KEY_SPACE])
    //     {
            
    //         chara->state = ATK;
    //     }
    //     else if (key_state[ALLEGRO_KEY_A])
    //     {
    //         // Elements *flo;
    //         // flo = New_bomb(bomb_L, 100, 100);
    //         // _Register_elements(scene, flo);
        
    //         printf("A");
    //         chara->dir = false;
    //         chara->state = MOVE;
    //     }
    //     else if (key_state[ALLEGRO_KEY_D])
    //     {
    //         chara->dir = true;
    //         chara->state = MOVE;
    //     }
    //     else
    //     {
    //         chara->state = STOP;
    //     }
    // }
    // else if (chara->state == MOVE)
    // {
    //     // chara->state = ATK;
    //     if (key_state[ALLEGRO_KEY_SPACE])
    //     {
    //         chara->state = ATK;
    //     }
    //     else if (key_state[ALLEGRO_KEY_A])
    //     {
    //         chara->dir = false;
    //         _bomb_update_position(self, -5, 0);
    //         chara->state = MOVE;
    //     }
    //     else if (key_state[ALLEGRO_KEY_D])
    //     {
    //         chara->dir = true;
    //         _bomb_update_position(self, 5, 0);
    //         chara->state = MOVE;
    //     }
    //     if (chara->gif_status[chara->state]->done)
    //         chara->state = STOP;
    // }
    // else if (chara->state == ATK)
    // {
    //     // chara->state = ATK;
    //     if (chara->gif_status[chara->state]->done)
    //     {
    //         chara->state = STOP;
    //         chara->new_proj = false;
    //     }
    //     if (chara->gif_status[ATK]->display_index == 2 && chara->new_proj == false)
    //     {
    //         Elements *pro;
    //         if (chara->dir)
    //         {
    //             pro = New_Projectile(Projectile_L,
    //                                  chara->x + chara->width - 100,
    //                                  chara->y + 10,
    //                                  5);
    //         }
    //         else
    //         {
    //             pro = New_Projectile(Projectile_L,
    //                                  chara->x - 50,
    //                                  chara->y + 10,
    //                                  -5);
    //         }
    //         _Register_elements(scene, pro);
    //         chara->new_proj = true;
    //     }
    //     // chara->state = ATK;
    // }
}
void bomb_draw(Elements *self)
{
    // with the state, draw corresponding image
     bomb *Obj = ((bomb *)(self->pDerivedObj));
    current_time_bo=time(NULL);
    al_draw_circle(Obj->x+50,Obj->y+50,150,Obj->color,5);//draw hitbox
    sprintf(Obj->text_b, "%ld",(long)(4-(current_time_bo-Obj->start_local)));
    if((long)(current_time_bo-Obj->start_local-1)>3){
        al_draw_bitmap(Obj->img2,Obj->x-100,Obj->y-100,0);
        if(Obj->sound_played==0){
        al_play_sample_instance(Obj->bang_Sound);
            Obj->sound_played=1;
        }
    }
    else
        al_draw_bitmap(Obj->img,Obj->x,Obj->y,0);
    al_draw_text(Obj->font, Obj->color, Obj->x+50, Obj->y, ALLEGRO_ALIGN_CENTRE, Obj->text_b);
}
void bomb_destory(Elements *self)
{
    bomb *Obj = ((bomb *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->bang_Sound);
    // for (int i = 0; i < 3; i++)
    //     algif_destroy_animation(Obj->gif_status[i]);
    al_destroy_bitmap(Obj->img2);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _bomb_update_position(Elements *self, int dx, int dy)
{
    bomb *chara = ((bomb *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void bomb_interact(Elements *self, Elements *tar) {
     bomb *Obj = ((bomb*)(self->pDerivedObj));
     current_time_bo=time(NULL);
    if(tar->label == Zombie1_L)
    {
        if((long)(current_time_bo-Obj->start_local-1)>4){
        printf("a");
        
        Zombie1 *Obj2 = ((Zombie1 *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
        {
            Obj2->behitted = 1;
            printf("Zombie1: ahh!");
            Obj2-> hp -= 3;
        }
        placed[Obj->x/100][Obj->y/100] = 0;
        self->dele=true;
        }
    }
    else if(tar->label == Zomboni_L)
    {
        if((long)(current_time_bo-Obj->start_local-1)>4){
        printf("a");
        
        Zomboni *Obj2 = ((Zomboni *)(tar->pDerivedObj));
        if (Obj->hitbox->overlap(Obj2->hitbox, Obj->hitbox))
        {
            printf("Zomboni: ahh!");
            Obj2-> hp -= 3;
        }
        placed[Obj->x/100][Obj->y/100] = 0;
        self->dele=true;
        }
    }
    //  if(tar->label==Ball2_L){
    //     Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
    //     if(Obj2->placed_range->overlap(Obj2->placed_range, Obj->hitbox))
    //         Obj2->lap=1;
    //     else
    //         Obj2->lap=0; 
    //  }

     

}