#include "gamescene.h"
/*
   [GameScene function]
*/
time_t start_time_gs,current_time_gs; 
int zombie1_created=0;
//0607 Bruce add
int Boss_created=0;

Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    printf("%d",pObj->label);
    // setting derived object member
    //pDerivedObj->background = al_load_bitmap("assets/image/stage.jpg");
    pObj->pDerivedObj = pDerivedObj;
    //start_time_gs=time(NULL);
    start_time_gs = al_get_time();
    Boss_created=0;
    Gold=500;
    Score=0;
    memset(placed,0,60*4);
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 24, 0);
     pDerivedObj->background_gs =al_load_bitmap("assets/image/gamescene_back.png");
    pDerivedObj->font2 = al_load_ttf_font("assets/font/pirulen.ttf", 36, 0);
    pDerivedObj->lottery_created=0;
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    al_reserve_samples(24);
    pDerivedObj->sample_instance= al_create_sample_instance(pDerivedObj->song);
    // register element
    // _Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_Back(Back_L));
    _Register_elements(pObj, New_Resume(Resume_L));
    _Register_elements(pObj, New_flower_button(FlowerB_L));
    _Register_elements(pObj, New_sunflw_button(SunflwB_L));
    _Register_elements(pObj, New_bomb_button(BombB_L));
    _Register_elements(pObj, New_potato_button(PotatoB_L));
    _Register_elements(pObj, New_Ball(Ball_L));
    _Register_elements(pObj, New_Ball2(Ball2_L));
    _Register_elements(pObj, New_map(Map_L));
    
      //_Register_elements(pObj, New_Zombie1(Zombie1_L)); //Burce add:Register Zomvie1
    //  _Register_elements(pObj, New_Flower(Flower_L));
    // setting derived object function
    
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_update(Scene *self)
{
    //current_time_gs=time(NULL);
    current_time_gs = al_get_time();
    game_scene_lottery(self);
    game_scene_zombie(self);
    if(current_time_gs-start_time_gs>9999){
                    self->scene_end = true;
                    window = 3;
            
    }
    // update every element
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
        if(ele->label==Back_L){
            Back *Obj = ((Back *)(ele->pDerivedObj));
            if(Obj->back==1){
                    self->scene_end = true;
                    window = 0;
            }
        }
        else if(ele->label==Resume_L){
            Resume *Obj = ((Resume *)(ele->pDerivedObj));
            if(Obj->Resume==1){
                    self->scene_end = true;
                    window = 1;
            }

        }
        else if(ele->label==Zombie1_L){
            Zombie1 *Obj = ((Zombie1 *)(ele->pDerivedObj));
            if(Obj->gameover==1){
                    self->scene_end = true;
                    window = 2;
            }

        }
        //0607 Bruce new add:boss
        else if(ele->label==Boss_L){
            Boss *Obj = ((Boss*)(ele->pDerivedObj));
            if(Obj->gameover==1){
                    self->scene_end = true;
                    window = 2;
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
}
void game_scene_draw(Scene *self)
{   
    char Gold_text[100],score_text[100];
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
     al_draw_bitmap(gs->background_gs, 0, 0, 0);
    current_time_gs=time(NULL);
    sprintf(gs->text, "%ld",(long)(current_time_gs-start_time_gs-1));
    //al_draw_bitmap(gs->background, 0, 0, 0);
     al_draw_text(gs->font2, al_map_rgb(233, 211, 33),750,600, ALLEGRO_ALIGN_CENTRE,"Time:");
     al_draw_text(gs->font2, al_map_rgb(233, 211, 33),850,600, ALLEGRO_ALIGN_CENTRE,gs->text );
    sprintf(Gold_text, "%d",Gold);
    sprintf(score_text, "%d",Score);
    //al_draw_bitmap(gs->background, 0, 0, 0);
    al_draw_text(gs->font, al_map_rgb(255,255, 255),50,600, ALLEGRO_ALIGN_CENTRE,"Gold:");
     al_draw_text(gs->font, al_map_rgb(255, 255, 255),150,600, ALLEGRO_ALIGN_CENTRE,Gold_text );
     al_draw_text(gs->font, al_map_rgb(255,255,255),300,600, ALLEGRO_ALIGN_CENTRE,"Score:");
     al_draw_text(gs->font, al_map_rgb(255,255,255),400,600, ALLEGRO_ALIGN_CENTRE,score_text );
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    //ALLEGRO_BITMAP *background = Obj->background;
    //al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
//Create zombie schedule
void game_scene_zombie(Scene *self){
     
     if((current_time_gs-start_time_gs)%3==1){
        zombie1_created=0;                     //reset the bool zombie been created
     }
     if(((current_time_gs-start_time_gs)%3==0)&&(zombie1_created==0)){
        _Register_elements(self, New_Zombie1(Zombie1_L));
        zombie1_created=1;
     }


    //0607 Bruce add :boss
     if((start_time_gs)%3==1){
        Boss_created=0;                     //reset the bool zombie been created
     }
     if(((current_time_gs-start_time_gs)%3==0) && (Boss_created==0)){
        // _Register_elements(self, New_Boss(Boss_L));
        Boss_created=1;
     }

}
void game_scene_lottery(Scene *self){
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    if((current_time_gs-start_time_gs)%10==1){
        Obj->lottery_created=0;                     //reset the bool zombie been created
     }
     if((current_time_gs-start_time_gs)%10==0&&(Obj->lottery_created==0)){
        Obj->lottery_created=1;
         _Register_elements(self, New_Lottery(Lottery_L));                   
     }
}