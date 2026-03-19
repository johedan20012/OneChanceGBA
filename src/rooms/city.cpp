#include "city.h"

namespace game{
City::City(Player& _player, DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_city.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
    car(bn::sprite_items::car_small.create_sprite(0,0)){

    player.setVisible(false);
    
    switch (entering_from){
    case DIRECTION::LEFT:
        car.set_position(bn::fixed_point(-97,67));
        player.setPos(-97,67);
        break;    
    default:
        player.setPos(0,0);
        break;
    }

    exits.push_back(RoomExit("work_parking",bn::fixed_rect(160,20,10,64),DIRECTION::LEFT,false));
}

City::~City(){
    Room::~Room();
}

bn::optional<RoomExit> City::update(){
    if(bn::keypad::right_held()){
        car.set_position(car.position().x()+1,car.position().y());
        player.setPos(player.getPos().x()+1,player.getPos().y());
    }

    Room::update();

    auto exit = checkExits();
    if(exit){
        player.setVisible(true);
    }
    return exit;
}
}