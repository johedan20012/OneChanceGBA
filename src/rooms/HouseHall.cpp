#include "houseHall.h"

namespace game{
HouseHall::HouseHall(Player& _player):
    Room(bn::regular_bg_items::bg_house_2.create_bg(8,48),bn::regular_bg_items::bg_paper_2.create_bg(8,48),_player){

    player.setPos(-20,26);
    exits.push_back(bn::fixed_rect(-120,26,10,64));
    exitsName.push_back("house_bedroom");
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
