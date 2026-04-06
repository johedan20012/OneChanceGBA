#include "workHall.h"

#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_walking_dude.h"

#include "bn_regular_bg_items_bg_work_hall.h"

namespace game{
WorkHall::WorkHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_work_hall.create_bg(8,48),bn::fixed_rect(0,1,240,118),_player),
    global_var(_global_var),
    npcs{NPC(bn::sprite_items::work_people.create_sprite(-63,17,8)),NPC(bn::sprite_items::work_people.create_sprite(-43,17,9))}{
    
    player.setMovementBox(bn::fixed_rect(0,0,260,160));

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

    exits.push_back(RoomExit("work_lobby",bn::fixed_rect(-128,20,7,64),DIRECTION::RIGHT,false));
    exits.push_back(RoomExit("work_lab_door",bn::fixed_rect(128,20,7,64),DIRECTION::LEFT,false));

    switch(global_var.currentDay()){
        case 2:
            loadDay2();
            break;
        default:
            loadDay1(entering_from);
            break;
    }

    #ifdef DEBUG_GAME
    Room::createExitsDebug();
    #endif
}

void WorkHall::loadDay1(DIRECTION entering_from){
    walking_dude = bn::sprite_items::walking_dude.create_sprite(140,20,0);
    walking_dude->set_bg_priority(2);
    walking_dude->set_z_order(2);

    {
        DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,30,64),false);
        dialog->addDialog(Pair<int,int>(5,180));
        npcs[1].addDialog(dialog);
    }

    if(entering_from == DIRECTION::LEFT){
        walk_mov = bn::sprite_move_to_action(walking_dude.value(),280,bn::fixed_point(-140,20));
        walk_anim = bn::create_sprite_animate_action_forever(walking_dude.value(),6,bn::sprite_items::walking_dude.tiles_item(),0,1);    
    }

    exits.push_back(RoomExit("skip_work",bn::fixed_rect(-45,20,19,64),DIRECTION::DOOR1,true));
    exits.back().info = "Skip work";
}

void WorkHall::loadDay2(){
    npcs[0].set_position(bn::fixed_point(-49,17));
    npcs[1].set_position(bn::fixed_point(-29,17));

    extra_npc = bn::sprite_items::work_people.create_sprite(-62,21,5);
    extra_npc->setHorizontalFlip(true);
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
    npcs[1].checkDialog(player.boundaries());

    if(extra_npc) extra_npc->lookAt(player.getPos(),true);

    Room::updateExitsInfo();
    Room::update();

    return checkExits();
}

}