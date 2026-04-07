#include "workStairs.h"

#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_construction_guy.h"

#include "bn_regular_bg_items_bg_work_stairs.h"

namespace game{
WorkStairs::WorkStairs(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_work_stairs.create_bg(8,48),bn::fixed_rect(0,1,240,118),_player),
    global_var(_global_var),
    npcs{NPC(bn::sprite_items::work_people.create_sprite(-10,14,5)),NPC(bn::sprite_items::construction_guy.create_sprite(108,26,0))}{

    player.setMovementBox(bn::fixed_rect(-20.5,0,219,160));

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

    exits.push_back(RoomExit("work_lab_door",bn::fixed_rect(-128,20,7,64),DIRECTION::RIGHT,false));

    switch (global_var.currentDay()){
    case 2:
        loadDay2();
        break;
    
    default:
        loadDay1();
        break;
    }

    #ifdef DEBUG_GAME
    Room::createExitsDebug();
    #endif
}

void WorkStairs::loadDay1(){
    npcs[0].getPalette().set_color(12,bn::color(6,3,2)); //Change hair color
    npcs[0].getPalette().set_color(19,bn::color(0,0,0)); //Change shirt color
    
    {
        DialogTrigger* dialog_ryan = new DialogTrigger(global_var,bn::fixed_rect(0,0,30,64),false);
        dialog_ryan->addDialog(Pair<int,int>(6,180));
        npcs[0].addDialog(dialog_ryan);

        DialogTrigger* dialog_cons = new DialogTrigger(global_var,bn::fixed_rect(0,0,26,64),true,true);
        dialog_cons->addDialog(Pair<int,int>(7,180));
        npcs[1].addDialog(dialog_cons);
    }
}

void WorkStairs::loadDay2(){
    player.setMovementBox(bn::fixed_rect(-17,0,226,160));

    exits.push_back(RoomExit("work_roof",bn::fixed_rect(110,20,38,64),DIRECTION::LEFT,true));
    exits.back().info = "Roof";

    npcs[0] = bn::sprite_items::work_people.create_sprite(-38,15,2);
    npcs[0].setHorizontalFlip(true);
    npcs[1] = bn::sprite_items::work_people.create_sprite(-14,15,4);
}

bn::optional<RoomExit> WorkStairs::update(){
    player.update();
    
    npcs[0].lookAt(player.getPos(),true);
    npcs[0].checkDialog(player.boundaries());
    npcs[1].checkDialog(player.boundaries());
    npcs[1].lookAt(player.getPos(),true);

    Room::update();
    Room::updateExitsInfo();

    return checkExits();
}
}