#include "charater.h"
#include "sunflw.h"
#include "sun.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
/*
   [Sunflw function]
*/
//hello
Elements *New_Sunflw(int label, int x, int y)
{
    Sunflw *pDerivedObj = (Sunflw *)malloc(sizeof(Sunflw));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load sunflw images
    char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara2_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound2.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of sunflw
    pDerivedObj->width = pDerivedObj->gif_status[1]->width;
    pDerivedObj->height = pDerivedObj->gif_status[1]->height;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + 100,
                                        pDerivedObj->y + 100);
    pDerivedObj->dir = true; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->ptime = 1;
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;
    // setting derived object function
    pObj->Draw = Sunflw_draw;
    pObj->Update = Sunflw_update;
    pObj->Interact = Sunflw_interact;
    pObj->Destroy = Sunflw_destory;
    return pObj;
}
void Sunflw_placing(int x, int y){
//     if(key_state[ALLEGRO_KEY_SPACE]){
//         printf("spcae is pressed");
//         New_Sunflw(Sunflw_L, 1, 1);
//     }
// }
}
void Sunflw_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Sunflw *chara = ((Sunflw *)(self->pDerivedObj));
    // if(key_state[ALLEGRO_KEY_SPACE]){
    //     printf("spcae is pressed");
    //     //New_Sunflw(Sunflw_L, 1, 1);
    //     sleep(1);
    // }
    // if(mouse_state[2] == 1){
    //     printf("mouse right clicked");
    // }
    
    // if (chara->gif_status[chara->state]->done)
    //     {
    //         chara->state = STOP;
    //         chara->new_proj = false;
    //     }
    //     if (chara->gif_status[ATK]->display_index == 20 && chara->new_proj == false)
    //     {
            
    //         Elements *pro;
    //         // Elements *pro2;
    //         if (chara->dir)
    //         {
    //             printf("entered new sun\n");
    //             pro = New_Sun(Sun_L,
    //                                  chara->x + chara->width - 100,
    //                                  chara->y + 10,
    //                                  1);
    //             // printf("enterd");
    //             // pro2 = New_Sunflw(Sunflw_L, 100, 100);
    //             // _Register_elements(scene, pro2);
    //         }
    //         else
    //         {
    //             pro = New_Sun(Sun_L,
    //                                  chara->x - 50,
    //                                  chara->y + 10,
    //                                  -1);
    //         }
    //         _Register_elements(scene, pro);
    //         chara->new_proj = true;
    //     }
    //     chara->state = ATK;
    chara->ptime += 1;
    int second = chara->ptime/60 + 1;
    if (chara->state == STOP)
    {
        
        
        printf("second = %d\n", second);
        // chara->state = ATK;
        if (second%5 == 0)
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
        // chara->state = ATK;
        if (chara->gif_status[chara->state]->done)
        {
            chara->state = STOP;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK]->display_index == 20 && chara->new_proj == false)
        {
            Elements *pro;
            if (chara->dir)
            {
                pro = New_Sun(Sun_L,
                                     chara->x -20,
                                     chara->y - 10,
                                     1);
            }
            // else
            // {
            //     pro = New_Sun(Sun_L,
            //                          chara->x + 100,
            //                          chara->y + 100,
            //                          -1);
            // }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
        // chara->state = ATK;
    }
    
}
void Sunflw_draw(Elements *self)
{
    // with the state, draw corresponding image
    Sunflw *chara = ((Sunflw *)(self->pDerivedObj));
    
    al_draw_rectangle(chara->x,chara->y,chara->x + 100,chara->y + 100, al_map_rgb(255, 255, 255), 5);//draw hitbox 
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


void _Sunflw_update_position(Elements *self, int dx, int dy)
{
    Sunflw *chara = ((Sunflw *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Sunflw_interact(Elements *self, Elements *tar) {

    Sunflw *Obj = ((Sunflw*)(self->pDerivedObj));
     if(tar->label==Ball2_L){
        Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
        if(Obj2->placed_range->overlap(Obj2->placed_range, Obj->hitbox))
            Obj2->lap=1;
        else
            Obj2->lap=0; 
     }
}
void Sunflw_destory(Elements *self)
{
    Sunflw *Obj = ((Sunflw *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
    algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}