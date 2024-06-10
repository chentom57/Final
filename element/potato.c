#include "charater.h"
#include "potato.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "zombie1.h"
/*
   [potato function]
*/
//hello
Elements *New_potato(int label, int x, int y)
{
    potato *pDerivedObj = (potato *)malloc(sizeof(potato));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load potato images
    // char state_string[3][10] = {"stop", "move", "attack"};
    // for (int i = 0; i < 3; i++)
    // {
    //     char buffer[50];
    //     sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
    //     pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    // }
    char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara3_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
     pDerivedObj->img = al_load_bitmap("assets/image/potato.png");
    // load effective sound
    // ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.mp3");
    // pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    // al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    // al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of potato
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
     pDerivedObj->hp = 2000;
     pDerivedObj->hitbox = New_Circle(pDerivedObj->x+60,
                                        pDerivedObj->y+60,
                                        30);
    pDerivedObj->dir = true; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    // pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;
    pObj->inter_obj[pObj->inter_len++] = Zombie1_L;
    // setting derived object function
    pObj->Draw = potato_draw;
    pObj->Update = potato_update;
    pObj->Interact = potato_interact;
    pObj->Destroy = potato_destory;
    return pObj;
}
void potato_placing(int x, int y){
//     if(key_state[ALLEGRO_KEY_SPACE]){
//         printf("spcae is pressed");
//         New_potato(potato_L, 1, 1);
//     }
// }
}
void potato_update(Elements *self)
{
    
    
    // use the idea of finite state machine to deal with different state
    potato *chara = ((potato *)(self->pDerivedObj));
    // printf("potato = %d %d\n", chara -> x, chara -> y);
    if(chara->hp <= 0){  
        placed[chara->x / 100][chara->y /100]=0;              
        self->dele=true;
    }
    // if(key_state[ALLEGRO_KEY_SPACE]){
    //     printf("spcae is pressed");
    //     //New_potato(potato_L, 1, 1);
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
    //     if (chara->gif_status[ATK]->display_index == 0 && chara->new_proj == false)
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
    //             // pro2 = New_potato(potato_L, 100, 100);
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
    //         // flo = New_potato(potato_L, 100, 100);
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
    //         _potato_update_position(self, -5, 0);
    //         chara->state = MOVE;
    //     }
    //     else if (key_state[ALLEGRO_KEY_D])
    //     {
    //         chara->dir = true;
    //         _potato_update_position(self, 5, 0);
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

void potato_interact(Elements *self, Elements *tar) {
    //  potato *Obj = ((potato*)(self->pDerivedObj));
    //  if(tar->label == Zombie1_L){
    //     printf("zombie ovlp potato\n");
    //     Zombie1 *zomb = ((Zombie1 *)(tar -> pDerivedObj));
    //     if(Obj->hitbox->overlap(zomb->hitbox, Obj->hitbox)){
    //         printf("zombie ovlp potato2\n");
    //         zomb -> v = 0;
    //     }
    //  }
}

void potato_draw(Elements *self)
{
    
    // with the state, draw corresponding image
    potato *Obj = ((potato *)(self->pDerivedObj));
   
    ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->gif_status[Obj->state], al_get_time());
    if(frame)
    {
        al_draw_bitmap(frame, Obj->x, Obj->y, ((Obj->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (Obj->state == ATK && Obj->gif_status[Obj->state]->display_index == 2)
    {
        al_play_sample_instance(Obj->atk_Sound);
    }
     al_draw_circle(Obj->x+60, Obj->y+60, 30, al_map_rgb(105, 105, 0), 10);
}

void potato_destory(Elements *self)
{
    potato *Obj = ((potato *)(self->pDerivedObj));
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _potato_update_position(Elements *self, int dx, int dy)
{
    potato *chara = ((potato *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}