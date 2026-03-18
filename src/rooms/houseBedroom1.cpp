#include "HouseBedroom1.h"

namespace game{

HouseBedroom1::HouseBedroom1(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_house_1.create_bg(8,48),bn::fixed_rect(0,0,240,131),_player){

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,33);
            break;
        default:
            player.setPos(0,33);
            break;
    }

    exits.push_back(RoomExit(
        "house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::LEFT,false));
}

HouseBedroom1::~HouseBedroom1(){
    Room::~Room();
}

bn::optional<RoomExit> HouseBedroom1::update(){
    player.update();

    Room::update();

    return checkExits();
}

}