#include "houseHall.h"

namespace game{
HouseHall::HouseHall(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_house_2.create_bg(8,48),bn::regular_bg_items::bg_paper_2.create_bg(8,48),_player){

    switch(entering_from){
        case DIRECTION::LEFT:
            player.setPos(-108,26);
            break;
        case DIRECTION::DOOR1:
            player.setPos(-92,26);
            break;
        default:
            player.setPos(0,26);
            break;
    }

    exits.push_back(RoomExit("house_bedroom",bn::fixed_rect(-120,26,4,64),DIRECTION::RIGHT,false));
    exits.push_back(RoomExit("house_molly",bn::fixed_rect(-84,26,20,64),DIRECTION::RIGHT,true)); 
}

HouseHall::~HouseHall(){
    Room::~Room();
}

void HouseHall::update(){
    player.update();

    if(bn::keypad::start_pressed()){
        BN_LOG("holiii2 jsjxj");
    }

    Room::update();
}
}
