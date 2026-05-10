#include "houseBathroom.h"

#include "bn_sprite_items_lab_coat.h"
#include "bn_sprite_items_penny_bathtub.h"
#include "bn_sprite_items_light_bathroom.h"

#include "bn_regular_bg_items_bg_house_4.h"
#include "bn_regular_bg_items_bg_house_4_b.h"
#include "bn_regular_bg_items_bg_house_4_c.h"

#include "bn_log.h"

namespace game{

HouseBathroom::HouseBathroom(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_4.create_bg(8,48),bn::fixed_rect(60,0,121,131),_player),
    global_var(_global_var),penny(nullptr){

    player.setMovementBox(bn::fixed_rect(75,0,110,160));

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,29);
            break;
        default:
            player.setPos(0,29);
            break;
    }

    exits.push_back(RoomExit("house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::DOOR2,false));

    switch(global_var.currentDay()){
        case 2:
            loadDay2();
            break;
        case 3:
            loadDay3();
            break;
        case 4:
            loadDay4();
            break;
        default:
            break;
    }
}

HouseBathroom::~HouseBathroom(){
    player.setUseLightBathroomDay4(false);
}

void HouseBathroom::loadDay2(){
    penny = bn::make_unique<NPC>(bn::sprite_items::penny_bathtub.create_sprite(86,13));

    {
    DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,40,64),false,false);
    dialog->addDialog(Pair<int,int>(9,150));
    dialog->addDialog(Pair<int,int>(10,90));
    penny->addDialog(dialog);
    }
}

void HouseBathroom::loadDay3(){
    coat = bn::sprite_items::lab_coat.create_sprite(46,48);
    coat->set_rotation_angle(90);
    bn::sprite_palette_ptr pal =  coat->palette();
    pal.set_color(2,bn::color(19,6,12));
}

void HouseBathroom::loadDay4(){
    loadDay3();

    if(global_var.dayChoice(4) == CHOICE::SKIP_WORK){
        player.setUseLightBathroomDay4(true);

        if(global_var.getDayVariant(4) == 2){ // variant B
            bg->set_item(bn::regular_bg_items::bg_house_4_c);
            player.resetAnim();
            player.setHflip(true);
            player.setPos(103,29);
            player.update(); // i need to update the lights
            player.update(); // i need to update the lights so i call again hahaha
            timer = bn::make_unique<Timer>();
        }else{
            bg->set_item(bn::regular_bg_items::bg_house_4_b);
        }
        //light_day4A.push_back(bn::sprite_items::light_bathroom.create_sprite(46,-2,0));
        //light_day4A.push_back(bn::sprite_items::light_bathroom.create_sprite(82,-2,1));
        
    }
}

bn::optional<RoomExit> HouseBathroom::updateDay4(){
    if(timer && timer->elapsedFrames() >= 127){
        timer.reset();
        player.kneel();
        player.setUseLightBathroomDay4(false);
        player.setPos(102,37);
        timer2 = bn::make_unique<Timer>();
    }

    if(timer2 && timer2->elapsedFrames() >= 100){
        timer2.reset();
        bn::bg_palettes::set_fade(bn::color(0,0,0),0.0);
        bn::sprite_palettes::set_fade(bn::color(0,0,0),0.0);
        bg_fade_to_black = bn::bg_palettes_fade_to_action(290,1);
        spr_fade_to_black = bn::sprite_palettes_fade_to_action(290,1);
    }

    if(bg_fade_to_black){ 
        if(bg_fade_to_black->done() || spr_fade_to_black->done()){
            bn::bg_palettes::set_fade(bn::color(0,0,0),0.0);
            bn::sprite_palettes::set_fade(bn::color(0,0,0),0.0);
            player.useNightColors(false);
            player.resetAnim();
            return RoomExit("day_change",DIRECTION::LEFT);
        }
        bg_fade_to_black->update();
        spr_fade_to_black->update();
    }

    return bn::nullopt;
}

bn::optional<RoomExit> HouseBathroom::update(){
    Room::update();

    if(global_var.currentDay() == 4 && global_var.getDayVariant(4) == 2 && global_var.dayChoice(4) == CHOICE::SKIP_WORK) // B variant
        return updateDay4();

    player.update();
    if(penny) penny->checkDialog(player.boundaries());

    return checkExits();
}
}