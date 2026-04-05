#include "HouseBedroom1.h"

#include "bn_sprite_items_lab_coat.h"
#include "bn_sprite_items_character.h"

#include "bn_regular_bg_items_bg_house_1.h"

namespace game{

HouseBedroom1::HouseBedroom1(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_1.create_bg(8,48),bn::fixed_rect(0,0,240,131),_player),
    global_var(_global_var),
    player_reflexion(bn::sprite_items::character.create_sprite(0,0)),
    white_lab_coat(bn::sprite_items::lab_coat.create_sprite(0,0)){

    player_reflexion.set_bg_priority(3);
    bg.set_priority(2);

    white_lab_coat.set_bg_priority(2);
    white_lab_coat.set_z_order(2);

    player.setMovementBox(bn::fixed_rect(14.5,0,231,160));

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,29);
            break;
        default:
            player.setPos(0,29);
            break;
    }

    exits.push_back(RoomExit(
        "house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::LEFT,false));

    switch(global_var.currentDay()){
        case 2:
            loadDay2();
            break;
        default:
            loadDay1();
            break;
    }
}

void HouseBedroom1::loadDay1(){
    white_lab_coat.set_position(bn::fixed_point(82,11));
}

void HouseBedroom1::loadDay2(){
    white_lab_coat.set_rotation_angle(90);
    white_lab_coat.set_position(bn::fixed_point(23,48));
}

bn::optional<RoomExit> HouseBedroom1::update(){
    player.update();
    player_reflexion.set_position(player.getPos() + bn::fixed_point(13,-10));
    player_reflexion.set_tiles(player.getTilesItem());
    player_reflexion.set_horizontal_flip(player.getHorizontalFlip());

    Room::update();

    return checkExits();
}

}