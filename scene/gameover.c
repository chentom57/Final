#include <allegro5/allegro_primitives.h>
#include "gameover.h"

#include <stdbool.h>
/*
   [gameover function]
*/
Scene *New_gameover(int label)
{
    window=0;
    gameover *pDerivedObj = (gameover *)malloc(sizeof(gameover));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font_g = al_load_ttf_font("assets/font/pirulen.ttf", 36, 0);
    // Load sound
    pDerivedObj->song_g = al_load_sample("assets/sound/menu.mp3");
    pDerivedObj->img = al_load_bitmap("assets/image/gameover.png");
    al_reserve_samples(24);
    pDerivedObj->sample_instance_g = al_create_sample_instance(pDerivedObj->song_g);
    pDerivedObj->title_x_g = 240;
    pDerivedObj->title_y_g = 50;
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
    pObj->Update = gameover_update;
    pObj->Draw = gameover_draw;
    pObj->Destroy = gameover_destroy;
    return pObj;
}
void gameover_update(Scene *self)
{
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
void gameover_draw(Scene *self)
{
    gameover *Obj = ((gameover *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->title_x_g,Obj->title_y_g,0);
    // al_draw_text(Obj->font_g, al_map_rgb(233, 211, 33), Obj->title_x_g, Obj->title_y_g, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
    // al_draw_rectangle(Obj->title_x_g - 150, Obj->title_y_g - 40, Obj->title_x_g + 150, Obj->title_y_g + 70, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(Obj->sample_instance_g);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void gameover_destroy(Scene *self)
{
    gameover *Obj = ((gameover *)(self->pDerivedObj));
    al_destroy_font(Obj->font_g);
    al_destroy_sample(Obj->song_g);
    al_destroy_sample_instance(Obj->sample_instance_g);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
