#include "workLabDoor.h"

namespace game{
WorkLabDoor::WorkLabDoor(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_work_lab_door.create_bg(8,48),bn::fixed_rect(0,1,240,118),_player),
    npc(bn::sprite_items::work_people.create_sprite(-32,15,10)){

    player.setMovementBox(bn::fixed_rect(0,0,260,160));

    switch (entering_from){
        case DIRECTION::LEFT:
            player.setPos(-106,28);
            break;
        case DIRECTION::RIGHT:
            player.setPos(106,28);
            break;
        default:
            break;
    }

    exits.push_back(RoomExit("work_hall",bn::fixed_rect(-128,20,7,64),DIRECTION::RIGHT,false));
    exits.push_back(RoomExit("work_lab",bn::fixed_rect(20,20,10,64),DIRECTION::RIGHT,true));
    exits.push_back(RoomExit("work_stairs",bn::fixed_rect(128,20,7,64),DIRECTION::LEFT,false));
}

WorkLabDoor::~WorkLabDoor(){
    Room::~Room();
}

bn::optional<RoomExit> WorkLabDoor::update(){

    player.update();

    Room::update();

    return checkExits();
}
}