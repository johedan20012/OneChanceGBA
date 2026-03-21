#include "workParking.h"

namespace game{
WorkParking::JimNPC::JimNPC():
    NPC(bn::sprite_items::jim.create_sprite(70,40,0)){}

WorkParking::JimNPC::~JimNPC(){
    NPC::~NPC();
}

void WorkParking::JimNPC::update(){
    switch(smoke.elapsedFrames()){
        case 150:
            sprite.set_tiles(bn::sprite_items::jim.tiles_item(),1);
            break;
        case 220:
            sprite.set_tiles(bn::sprite_items::jim.tiles_item(),0);
            smoke.restart();
            break;
        default:
            break;
    }
}


WorkParking::WorkParking(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_work_parking.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player){

    player.setMovementBox(bn::fixed_rect(10,0,240,160));

    switch (entering_from){
        case DIRECTION::LEFT:
            player.setPos(-108,49);
            break;    
        default:
            player.setPos(0,0);
            break;
    }

    exits.push_back(RoomExit("work_lobby",bn::fixed_rect(123,20,10,64),DIRECTION::LEFT,false));
}

WorkParking::~WorkParking(){
    Room::~Room();
}

bn::optional<RoomExit> WorkParking::update(){
    jim.update();

    player.update();

    Room::update();

    return checkExits();
}
}