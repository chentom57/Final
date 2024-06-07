#include <allegro5/allegro_primitives.h>
#include "endgame.h"

#include <stdbool.h>
/*
   [endgame function]
*/
float dyy=0;
Scene *New_endgame(int label)
{
    Victory=1;
    endgame *pDerivedObj = (endgame *)malloc(sizeof(endgame));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font_e = al_load_ttf_font("assets/font/pirulen.ttf", 48, 0);
    // Load sound
    pDerivedObj->song_e = al_load_sample("assets/sound/menu.mp3");
    al_reserve_samples(20);
    pDerivedObj->background_e = al_load_bitmap("assets/image/victory_back.png");
    pDerivedObj->img_e = al_load_bitmap("assets/image/victory_t.png");
    pDerivedObj->img_ee = al_load_bitmap("assets/image/vvc.png");
    pDerivedObj->sample_instance_e = al_create_sample_instance(pDerivedObj->song_e);
    pDerivedObj->title_x_e = 250;
    pDerivedObj->title_y_e = -20;
    // Loop the song until the display closes
    // al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    // al_restore_default_mixer();
    // al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    // al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
     _Register_elements(pObj, New_Back_gg(Back_gg_L));
    // _Register_elements(pObj, New_Resume(Resume_gg_L));
    _Register_elements(pObj, New_Ball(MOUSE_gg_L));
    pObj->Update = endgame_update;
    pObj->Draw = endgame_draw;
    pObj->Destroy = endgame_destroy;
    return pObj;
}
void endgame_update(Scene *self)
{
    if(dyy<=140)
        dyy+=0.9;
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);

                }
            }
        }
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
       if(ele->label==Back_gg_L){
            Back_gg *Obj = ((Back_gg *)(ele->pDerivedObj));
            if(Obj->Back_gg==1){
                    mouse_state[1]=0;
                    self->scene_end = true;
                    window = 0;
            }


        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
    
    // if (ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    // {
    //     self->scene_end = true;
    //     window = 1;
    // }
}
void endgame_draw(Scene *self)
{
    endgame *Obj = ((endgame *)(self->pDerivedObj));
    char score_text[100];
     sprintf(score_text, "%d",Score);
    al_draw_bitmap(Obj->background_e, 0, 0, 0);
    //al_draw_bitmap(Obj->img_ee, Obj->title_x_e+70,190,0);
    al_draw_bitmap(Obj->img_e, Obj->title_x_e-40,Obj->title_y_e+dyy,0);
    al_draw_text(Obj->font_e, al_map_rgb(0,0,0),450,250, ALLEGRO_ALIGN_CENTRE,"Score:");
     al_draw_text(Obj->font_e, al_map_rgb(0,0,0),450,300, ALLEGRO_ALIGN_CENTRE,score_text );
    al_play_sample_instance(Obj->sample_instance_e);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void endgame_destroy(Scene *self)
{
    Victory=0;
    endgame *Obj = ((endgame *)(self->pDerivedObj));
    al_destroy_font(Obj->font_e);
    al_destroy_sample(Obj->song_e);
    al_destroy_sample_instance(Obj->sample_instance_e);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
