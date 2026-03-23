#include "houseHall.h"

namespace game{
HouseHall::HouseHall(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_house_2.create_bg(8,48),bn::fixed_rect(0,9,239,113),_player),
    penny(bn::sprite_items::penny.create_sprite(54,23)){

    player.setMovementBox(bn::fixed_rect(-10.5,0,239,160));

    switch(entering_from){
        case DIRECTION::LEFT:
            player.setPos(-108,29);
            break;
        case DIRECTION::DOOR1:
            player.setPos(-92,29);
            break;
        case DIRECTION::DOOR2:
            player.setPos(-8,29);
            break;
        default:
            player.setPos(0,29);
            break;
    }

    penny.lookAt(player.getPos());

    exits.push_back(RoomExit("house_bedroom",bn::fixed_rect(-120,26,4,64),DIRECTION::RIGHT,false));
    exits.push_back(RoomExit("house_molly",bn::fixed_rect(-84,26,20,64),DIRECTION::RIGHT,true)); 
    exits[1].info = "Molly's Room";
    exits.push_back(RoomExit("house_bath",bn::fixed_rect(-16,26,20,64),DIRECTION::RIGHT,true));
    exits[2].info = "Bathroom";
    exits.push_back(RoomExit("house_entrance",bn::fixed_rect(100,26,25,64),DIRECTION::LEFT,true));
    exits[3].info = "Outside";
}

HouseHall::~HouseHall(){
    Room::~Room();
}

bn::optional<RoomExit> HouseHall::update(){
    player.update();

    penny.lookAt(player.getPos());

    Room::updateExitsInfo();
    Room::update();

    return checkExits();
}
}
