#include "charater.h"
#include "flower.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
<<<<<<< HEAD
#include <unistd.h>
=======
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
/*
   [Flower function]
*/
//hello
<<<<<<< HEAD
Elements *New_Flower(int label, int x, int y)
=======
Elements *New_Flower(int label)
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
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
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of flower
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
<<<<<<< HEAD
    pDerivedObj->x = x;
    pDerivedObj->y = y;
=======
    pDerivedObj->x = 400;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
<<<<<<< HEAD
    pDerivedObj->dir = true; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = ATK;
=======
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Flower_draw;
    pObj->Update = Flower_update;
    pObj->Interact = Flower_interact;
    pObj->Destroy = Flower_destory;
    return pObj;
}
<<<<<<< HEAD
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
    Flower *chara = ((Flower *)(self->pDerivedObj));
    // if(key_state[ALLEGRO_KEY_SPACE]){
    //     printf("spcae is pressed");
    //     //New_Flower(Flower_L, 1, 1);
    //     sleep(1);
    // }
    
    chara->state = ATK;
    
    if (chara->gif_status[chara->state]->done)
=======
void Flower_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Flower *chara = ((Flower *)(self->pDerivedObj));
    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->state = MOVE;
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Flower_update_position(self, -5, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Flower_update_position(self, 5, 0);
            chara->state = MOVE;
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }
    else if (chara->state == ATK)
    {
        if (chara->gif_status[chara->state]->done)
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
        {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 2 && chara->new_proj == false)
        {
            Elements *pro;
<<<<<<< HEAD
            // Elements *pro2;
=======
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
            if (chara->dir)
            {
                pro = New_Projectile(Projectile_L,
                                     chara->x + chara->width - 100,
                                     chara->y + 10,
                                     5);
<<<<<<< HEAD
                // printf("enterd");
                // pro2 = New_Flower(Flower_L, 100, 100);
                // _Register_elements(scene, pro2);
=======
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
            }
            else
            {
                pro = New_Projectile(Projectile_L,
                                     chara->x - 50,
                                     chara->y + 10,
                                     -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
<<<<<<< HEAD
        chara->state = ATK;
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
=======
    }
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
}
void Flower_draw(Elements *self)
{
    // with the state, draw corresponding image
    Flower *chara = ((Flower *)(self->pDerivedObj));
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
<<<<<<< HEAD
void Flower_interact(Elements *self, Elements *tar) {}
=======

void Flower_interact(Elements *self, Elements *tar) {}
>>>>>>> 1785477cdfb8bf61fd8b6055c8662ff6945aedff
