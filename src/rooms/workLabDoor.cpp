#include "workLabDoor.h"

#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_walking_dude.h"

#include "bn_regular_bg_items_bg_work_lab_door.h"

namespace game{
WorkLabDoor::WorkLabDoor(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_work_lab_door.create_bg(8,48),bn::fixed_rect(0,1,240,118),_player),
    global_var(_global_var),
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
    exits.push_back(RoomExit("work_stairs",bn::fixed_rect(128,20,7,64),DIRECTION::LEFT,false));
    exits.push_back(RoomExit("work_lab",bn::fixed_rect(50,20,40,64),DIRECTION::RIGHT,true));
    exits.back().info = "Work";

    switch (global_var.currentDay()){
        case 2:
            loadDay2(entering_from);
            break;
        case 3:
            loadDay3();
            break;
        default:
            loadDay1();
            break;
    }

    #ifdef DEBUG_GAME
    Room::createExitsDebug();
    #endif
}

void WorkLabDoor::loadDay1(){
    is_door_locked = false;
}

void WorkLabDoor::loadDay2(DIRECTION entering_from){
    is_door_locked = true;

    npc = bn::sprite_items::work_people.create_sprite(-10,14,5);
    npc->set_position(bn::fixed_point(-83,13));
    npc->getPalette().set_color(12,bn::color(6,3,2)); //Change hair color
    npc->getPalette().set_color(19,bn::color(0,0,0)); //Change shirt color
    
    if(global_var.hasVisitedLabDoor()){
        global_var.getDialogManager().resetBg();
        global_var.getDialogManager().resetBottomText();
    }else{
        DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,30,64),false);
        dialog->addDialog(Pair<int,int>(13,120));
        dialog->addDialog(Pair<int,int>(14,120));
        npc->addDialog(dialog);
    }
    global_var.setVisitedLabDoor(!global_var.hasVisitedLabDoor());

    walking_dude = bn::sprite_items::walking_dude.create_sprite(140,20,0);
    walking_dude->set_bg_priority(2);
    walking_dude->set_z_order(2);
    if(entering_from == DIRECTION::LEFT){
        walk_mov = bn::sprite_move_to_action(walking_dude.value(),280,bn::fixed_point(-140,20));
        walk_anim = bn::create_sprite_animate_action_forever(walking_dude.value(),6,bn::sprite_items::walking_dude.tiles_item(),0,1);    
    }
}

void WorkLabDoor::loadDay3(){
    if(global_var.roofCheckedDay3()){
        exits.back().trigger = bn::fixed_rect(-11,12,28,64);
        
        npc = NPC(bn::sprite_items::work_people.create_sprite(-11,12,5));
        npc->getPalette().set_color(12,bn::color(6,3,2)); //Change hair color
        npc->getPalette().set_color(19,bn::color(0,0,0)); //Change shirt color
        DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,30,64),false,false);
        dialog->addDialog(Pair<int,int>(26,150));
        dialog->addDialog(Pair<int,int>(27,240));
        npc->addDialog(dialog);

        #ifdef DEBUG_GAME
        Room::createExitsDebug();
        #endif
    }else{
        is_door_locked = true;
        npc.reset();
    }
}

bn::optional<RoomExit> WorkLabDoor::update(){
    if(walk_anim) walk_anim->update();
    if(walk_mov){
        walk_mov->update();
        if(walk_mov->done()){
            walk_anim.reset();
            walk_mov.reset();
        }
    }

    player.update();

    if(npc && (global_var.currentDay() == 2 || global_var.currentDay() == 3)){
        npc->lookAt(player.getPos(),true);
        npc->checkDialog(player.boundaries());
    }

    Room::updateExitsInfo();
    Room::update();

    auto exit = checkExits();
    if(exit && is_door_locked && exit->name == bn::string_view("work_lab")){
        global_var.getDialogManager().setBottomText(15,180);
        Room::clearExitsInfo();
        exits.pop_back();
        return bn::nullopt;
    }else{ return exit;}
}
}