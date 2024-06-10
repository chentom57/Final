#include "Lottery.h"
#include "../global.h"
#include "time.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro_primitives.h>
#include "Ball2.h"
int count=0;
time_t start_time_lt,current_time_lt,start_time_dn,current_time_dn; 
Elements *New_Lottery(int label)
{
    Lottery *pDerivedObj = (Lottery *)malloc(sizeof(Lottery));
    Elements *pObj = New_Elements(label);
    pDerivedObj->img = al_load_bitmap("assets/image/lottery.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj-> img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj-> img);
    pDerivedObj->x =500;  
    pDerivedObj->y =520;
    pDerivedObj->done = 0;
    pDerivedObj->output = 0;
    pDerivedObj->sound_played=0;
    pDerivedObj->in = -1;
    pDerivedObj->color = al_map_rgb(255, 255, 50);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     pDerivedObj->width/2);
    pDerivedObj->font=al_load_ttf_font("assets/font/pirulen.ttf", 18, 0);
    pDerivedObj->font2=al_load_ttf_font("assets/font/pirulen.ttf", 36, 0);
     ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/lottery_win.mp3");
     pDerivedObj->win_Sound = al_create_sample_instance(sample);
    ALLEGRO_SAMPLE *sample2 = al_load_sample("assets/sound/lottery_failed.mp3");
     pDerivedObj->lose_Sound = al_create_sample_instance(sample2);
     
    al_set_sample_instance_playmode(pDerivedObj->win_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->win_Sound, al_get_default_mixer());
     al_set_sample_instance_playmode(pDerivedObj->lose_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->lose_Sound, al_get_default_mixer());
    start_time_lt=time(NULL);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Ball2_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Lottery_draw;
    pObj->Update = Lottery_update;
    pObj->Interact = Lottery_interact;
    pObj->Destroy = Lottery_destory;
    return pObj;
}
void Lottery_update(Elements *self)
{
    Lottery *Obj = ((Lottery *)(self->pDerivedObj));
    
    if(Obj->done==1){
        current_time_dn=time(NULL);
        if(current_time_dn-start_time_dn>=3)
                self->dele=true;
    }
    else{
        current_time_lt=time(NULL);
         if(current_time_lt-start_time_lt>=6)
                self->dele=true;
    }
    if(count==6)
        count=1;
    else
        count++;
}
void Lottery_interact(Elements *self, Elements *tar)
{
    Lottery *Obj = ((Lottery *)(self->pDerivedObj));
    if (tar->label == Ball2_L)
    {
       Ball2 *Obj2 = ((Ball2 *)(tar->pDerivedObj));
       if(mouse_state[1]==1&&Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&Obj->done==0){
            Obj->done=1;
            Obj->output=count;
            if(Obj->output>=4){
              Gold+=Obj->output*100;
              Score+=Obj->output*100;
            }
            else{
              Gold-=(3-Obj->output)*100;
              if(Gold<0)
                Gold=0;
            }
            start_time_dn=time(NULL);       

       }
       else if(mouse_state[2]==1&&Obj->hitbox->overlap(Obj->hitbox,Obj2->hitbox)&&Obj->done==0) {
            self->dele=true;
        }
    }

}
void Lottery_draw(Elements *self)
{
   Lottery *Obj = ((Lottery *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img,Obj->x,Obj->y,0);
    if(Obj->done==0){
        sprintf(Obj->text, "%d",count);
        al_draw_text(Obj->font, Obj->color, Obj->x+Obj->width/2, Obj->y+Obj->height/4+50, ALLEGRO_ALIGN_CENTRE, "lottery");
    }
    else{
        sprintf(Obj->text, "%d",Obj->output);
        if(Obj->output>3){
            Obj->color=al_map_rgb(0,255,0);
           al_draw_text(Obj->font, Obj->color, Obj->x+Obj->width/2, Obj->y+Obj->height/4+50, ALLEGRO_ALIGN_CENTRE, "lucky");
           if(Obj->sound_played==0){
            al_play_sample_instance(Obj->win_Sound);
            Obj->sound_played=1;
            }
        }
        else{
            Obj->color=al_map_rgb(255,0,0);
            al_draw_text(Obj->font, Obj->color, Obj->x+Obj->width/2, Obj->y+Obj->height/4+50, ALLEGRO_ALIGN_CENTRE, "failed");
            if(Obj->sound_played==0){
            al_play_sample_instance(Obj->lose_Sound);
            Obj->sound_played=1;
            }
        }
    }
    al_draw_text(Obj->font2, Obj->color, Obj->x+Obj->width/2, Obj->y+Obj->height/4, ALLEGRO_ALIGN_CENTRE,Obj->text);
    // al_draw_text(Obj->font, Obj->color, Obj->x+Obj->width/2, Obj->y+Obj->height/2+40, ALLEGRO_ALIGN_CENTRE, "200");
}
void Lottery_destory(Elements *self)
{
    Lottery *Obj = ((Lottery *)(self->pDerivedObj));
     al_destroy_sample_instance(Obj->win_Sound);
      al_destroy_sample_instance(Obj->lose_Sound);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}