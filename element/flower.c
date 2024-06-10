#include "charater.h"
#include "flower.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
/*
   [Flower function]
*/
//hello
Elements *New_Flower(int label, int x, int y)
{
    Flower *pDerivedObj = (Flower *)malloc(sizeof(Flower));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load flower images
    char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    pDerivedObj->sample = al_load_sample("assets/sound/atk_sound.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(pDerivedObj->sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of flower
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hp = 500;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x +100,
                                        pDerivedObj->y + 100);
                                        
    
    pDerivedObj->hitbox2 = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x +700,
                                        pDerivedObj->y + 100);
    pDerivedObj->hitbox3 = New_Circle(pDerivedObj->x+60,
                                    pDerivedObj->y+60,
                                    10);


    pDerivedObj->dir = true; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;
    pObj->inter_obj[pObj->inter_len++] = Zombie1_L;
    // setting derived object function
    pObj->Draw = Flower_draw;
    pObj->Update = Flower_update;
    pObj->Interact = Flower_interact;
    pObj->Destroy = Flower_destory;
    return pObj;
}
void Flower_placing(int x, int y){
//     if(key_state[ALLEGRO_KEY_SPACE]){
//         printf("spcae is pressed");
//         New_Flower(Flower_L, 1, 1);
//     }
// }
}
void Flower_update(Elements *self)
{
    
    
    // use the idea of finite state machine to deal with different state
    // printf("flower = %d %d\n", chara -> x, chara -> y);
    
    // if(key_state[ALLEGRO_KEY_SPACE]){
    //     printf("spcae is pressed");
    //     //New_Flower(Flower_L, 1, 1);
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
    //     if (chara->gif_status[ATK]->display_index == 8 && chara->new_proj == false)
    //     {
    //         Elements *pro;
    //         // Elements *pro2;
    //         if (chara->dir)
    //         {
    //             pro = New_Projectile(Projectile_L,
    //                                  chara->x + chara->width - 100,
    //                                  chara->y - 40,
    //                                  5);
    //             // printf("enterd");
    //             // pro2 = New_Flower(Flower_L, 100, 100);
    //             // _Register_elements(scene, pro2);
    //         }
    //         else
    //         {
    //             pro = New_Projectile(Projectile_L,
    //                                  chara->x - 50,
    //                                  chara->y - 40,
    //                                  -5);
    //         }
    //         // _Register_elements(scene, pro);
    //         // al_rest(0.1);
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
    //         // flo = New_Flower(Flower_L, 100, 100);
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
    //         _Flower_update_position(self, -5, 0);
    //         chara->state = MOVE;
    //     }
    //     else if (key_state[ALLEGRO_KEY_D])
    //     {
    //         chara->dir = true;
    //         _Flower_update_position(self, 5, 0);
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
    Flower *chara = ((Flower *)(self->pDerivedObj));
    //0610
    if(chara->hp <= 0){                
        self->dele=true;
        placed[chara->x / 100][chara->y /100]=0;
    }
    //0610 end

    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == ATK)
    {
        if (chara->gif_status[chara->state]->done)
        {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 29 && chara->new_proj == false)
        {
            Elements *pro;

            pro = New_Projectile(Projectile_L,
                                     chara->x + chara->width - 100,
                                     chara->y - 50,
                                     5);
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }

}
void Flower_draw(Elements *self)
{
    
    // with the state, draw corresponding image
    Flower *chara = ((Flower *)(self->pDerivedObj));
    al_draw_circle(chara->x + 60,
                    chara->y + 60,
                    10, al_map_rgb(100, 100, 255), 10);//draw hitbox 
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
    
}
void Flower_destory(Elements *self)
{
    Flower *Obj = ((Flower *)(self->pDerivedObj));
    al_destroy_sample(Obj->sample);
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Flower_update_position(Elements *self, int dx, int dy)
{
    Flower *chara = ((Flower *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Flower_interact(Elements *self, Elements *tar) {
    Flower *Obj = ((Flower *)(self->pDerivedObj));
    if(tar->label == Zombie1_L){
        Zombie1 *Obj2 = ((Zombie1 *)(tar -> pDerivedObj));
        if(Obj2->hitbox->overlap(Obj2->hitbox, Obj->hitbox2)){
            Obj -> state = ATK;
        }
    }
    //0610
    /*
    else if (tar->label == Zombie1_L)
    {
        Zombie1 *Obj2 = ((Zombie1 *)(tar->pDerivedObj));
        if (Obj->hitbox3->overlap(Obj2->hitbox, Obj->hitbox3))
        {
            Obj->hp--;
            printf("flower injured, hp: %d\n", Obj->hp);
            if(Obj->hp <= 0){
                self->dele=true;
            }                        
        }
    }
    */
}
