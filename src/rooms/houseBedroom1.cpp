#include "HouseBedroom1.h"

namespace game{

HouseBedroom1::HouseBedroom1(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_house_1.create_bg(8,48),bn::regular_bg_items::bg_paper.create_bg(8,48),_player){

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,26);
            break;
        default:
            player.setPos(0,26);
            break;
    }

    exits.push_back(RoomExit(
        "house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::LEFT,false));
}

HouseBedroom1::~HouseBedroom1(){
    Room::~Room();
}

void HouseBedroom1::update(){
    player.update();

    if(bn::keypad::start_pressed()){
        BN_LOG("holiii");
    }

    Room::update();
}

}