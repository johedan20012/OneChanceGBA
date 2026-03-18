#include "houseBedroom2.h"

namespace game{

HouseBedroom2::HouseBedroom2(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_house_3.create_bg(8,48),bn::fixed_rect(6,0,228,131),_player){

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,33);
            break;
        default:
            player.setPos(0,33);
            break;
    }

    exits.push_back(RoomExit("house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::DOOR1,false));
}

HouseBedroom2::~HouseBedroom2(){
    Room::~Room();
}

bn::optional<RoomExit> HouseBedroom2::update(){
    player.update();

    Room::update();

    return checkExits();
}

}