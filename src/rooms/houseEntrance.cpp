#include "houseEntrance.h"

namespace game{
HouseEntrance::HouseEntrance(Player& _player,DIRECTION _entering_from):
    Room(bn::regular_bg_items::bg_house_5.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player){

    switch(_entering_from){
        case DIRECTION::LEFT:
            player.setPos(-92,53);
            break;
        default:
            player.setPos(0,0);
            break;
    }
}

HouseEntrance::~HouseEntrance(){
    Room::~Room();
}

void HouseEntrance::update(){
    player.update();

    Room::update();
}

}