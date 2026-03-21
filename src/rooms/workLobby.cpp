#include "workLobby.h"

namespace game{
WorkLobby::WorkLobby(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_work_lobby.create_bg(8,48),bn::fixed_rect(0,1,240,118),_player){

    player.setMovementBox(bn::fixed_rect(11.5,0,237,160));

    switch (entering_from){
        case DIRECTION::LEFT:
            player.setPos(-106,28);
            break;
        case DIRECTION::RIGHT:
            player.setPos(106,28);
            break;
        default:
            player.setPos(0,0);
            break;
    }

    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(-48,25,0)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(-24,17,1)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(-3,17,2)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(20,18,3)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(43,19,4)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(65,20,5)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(88,20,6)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(111,20,7)));

    exits.push_back(RoomExit("work_hall",bn::fixed_rect(128,20,7,64),DIRECTION::LEFT,false));
}

WorkLobby::~WorkLobby(){
    Room::~Room();
}

bn::optional<RoomExit> WorkLobby::update(){
    player.update();

    for(auto npc : npcs){
        npc.lookAt(player.getPos(),true);
    }

    Room::update();

    return checkExits();
}
}