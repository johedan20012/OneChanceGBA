#include "houseBathroom.h"

#include "bn_sprite_items_lab_coat.h"
#include "bn_sprite_items_penny_bathtub.h"

#include "bn_regular_bg_items_bg_house_4.h"

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
        default:
            break;
    }
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

bn::optional<RoomExit> HouseBathroom::update(){
    player.update();
    if(penny) penny->checkDialog(player.boundaries());
    
    Room::update();

    return checkExits();
}
}