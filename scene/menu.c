#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
/*
   [Menu function]
*/
Scene *New_Menu(int label)
{
    window=0;
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);
    // Load sound
    al_reserve_samples(20);
    pDerivedObj->title_x_z =800;
    pDerivedObj->title_x_p =-240;
    pDerivedObj->background = al_load_bitmap("assets/image/menu.png");
    pDerivedObj->img = al_load_bitmap("assets/image/vs.png");
    pDerivedObj->img1 = al_load_bitmap("assets/image/plant_title.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/zombie_title.png");
    pDerivedObj->img3 = al_load_bitmap("assets/image/bar.png");
    pDerivedObj->gif_status[0] = algif_new_gif( "assets/image/zombie1_move.gif", -1);
    pDerivedObj->gif_status[1] = algif_new_gif( "assets/image/chara_attack.gif", -1);
    pDerivedObj->song = al_load_sample("assets/sound/menu_s.mp3");
    pDerivedObj->menu_Sound = al_create_sample_instance(pDerivedObj->song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->menu_Sound, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->menu_Sound, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->menu_Sound, 0.6);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    // _Register_elements(pObj, New_start(START_L));
     _Register_elements(pObj, New_Start(START_L));
     _Register_elements(pObj, New_Ball2(MOUSE_L));
    _Register_elements(pObj, New_Quit(Quit_L));
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
void menu_update(Scene *self)
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
        if(ele->label==START_L){
            Start *Obj = ((Start *)(ele->pDerivedObj));
            if(Obj->start==1){
                    self->scene_end = true;
                    window = 1;
            }

        }
        else if(ele->label==Quit_L){
            Quit *Obj = ((Quit *)(ele->pDerivedObj));
            if(Obj->Quit==1){
                    self->scene_end = true;
                    window = -1;
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
void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
     char score_text[100];
     sprintf(score_text, "%d",high_score);
    
    if(Obj->title_x_p<30)
        Obj->title_x_p+=1.3;
    if(Obj->title_x_z>530)
        Obj->title_x_z-=1.3;
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_bitmap(Obj->img3,310,255,0);
    al_draw_text(Obj->font, al_map_rgb(255,255,255),450,280, ALLEGRO_ALIGN_CENTRE,score_text );
    al_draw_bitmap(Obj->img, 360,80,0);
    al_draw_bitmap(Obj->img1, Obj->title_x_p,110,0);
    al_draw_bitmap(Obj->img2, Obj->title_x_z,100,0);
    ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->gif_status[0], al_get_time());
     ALLEGRO_BITMAP *frame2 = algif_get_bitmap(Obj->gif_status[1], al_get_time());
    al_draw_bitmap(frame, 550, 200, 0);
    al_draw_bitmap(frame2, 200, 200, 0);
    // al_draw_text(Obj->font, al_map_rgb(233, 211, 33), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Space' to start");
    // al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 50, Obj->title_x + 150, Obj->title_y + 50, al_map_rgb(255, 255, 255), 0);
    // al_play_sample_instance(Obj->sample_instance);
    al_play_sample_instance(Obj->menu_Sound);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
     al_destroy_sample_instance(Obj->menu_Sound);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    //al_destroy_sample_instance(Obj);
    // al_destroy_sample_instance(Obj->sample_instance);
    algif_destroy_animation(Obj->gif_status[0]);
     algif_destroy_animation(Obj->gif_status[1]);
     ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}