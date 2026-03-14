#include "HouseBedroom1.h"

namespace game{

HouseBedroom1::HouseBedroom1(Player& _player):
    Room(bn::regular_bg_items::bg_house_1.create_bg(8,48),bn::regular_bg_items::bg_paper.create_bg(8,48),_player){

    player.setPos(0,26);

    exits.push_back(bn::fixed_rect(120,26,10,64));
    exitsName.push_back("house_hall");
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