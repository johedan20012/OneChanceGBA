#include "houseBathroom.h"

namespace game{

HouseBathroom::HouseBathroom(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_house_4.create_bg(8,48),bn::fixed_rect(60,0,121,131),_player){

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,33);
            break;
        default:
            player.setPos(0,33);
            break;
    }

    exits.push_back(RoomExit("house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::DOOR2,false));
}

HouseBathroom::~HouseBathroom(){
    Room::~Room();
}

bn::optional<RoomExit> HouseBathroom::update(){
    player.update();

    Room::update();

    return checkExits();
}
}