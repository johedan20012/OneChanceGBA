#include "workHall.h"

namespace game{
WorkHall::WorkHall(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_work_hall.create_bg(8,48),bn::fixed_rect(0,1,240,118),_player),
    npcs{NPC(bn::sprite_items::work_people.create_sprite(-64,16,8)),NPC(bn::sprite_items::work_people.create_sprite(-44,16,9))},
    walking_dude(bn::sprite_items::walking_dude.create_sprite(140,20,0)){
    
    walking_dude.set_bg_priority(2);
    walking_dude.set_z_order(2);

    player.setMovementBox(bn::fixed_rect(0,0,260,160));

    switch (entering_from){
        case DIRECTION::LEFT:
            player.setPos(-106,28);
            walk_mov = bn::sprite_move_to_action(walking_dude,280,bn::fixed_point(-140,20));
            walk_anim = bn::create_sprite_animate_action_forever(walking_dude,6,bn::sprite_items::walking_dude.tiles_item(),0,1);
            break;
        case DIRECTION::RIGHT:
            player.setPos(106,28);
            break;
        default:
            player.setPos(0,0);
            break;
    }

    exits.push_back(RoomExit("work_lobby",bn::fixed_rect(-128,20,7,64),DIRECTION::RIGHT,false));
    exits.push_back(RoomExit("skip_work",bn::fixed_rect(-45,20,19,64),DIRECTION::DOOR1,true));
    exits.back().info = "Skip work";
    exits.push_back(RoomExit("work_lab_door",bn::fixed_rect(128,20,7,64),DIRECTION::LEFT,false));

    #ifdef DEBUG_GAME
    Room::createExitsDebug();
    #endif
}

bn::optional<RoomExit> WorkHall::update(){

    if(walk_anim) walk_anim->update();
    if(walk_mov){
        walk_mov->update();
        if(walk_mov->done()){
            walk_anim.reset();
            walk_mov.reset();
        }
    }

    player.update();

    npcs[1].lookAt(player.getPos(),true);

    Room::updateExitsInfo();
    Room::update();

    return checkExits();
}

}