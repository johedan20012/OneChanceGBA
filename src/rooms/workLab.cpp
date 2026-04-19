#include "workLab.h"

#include "bn_sprite_items_pc_screen.h"
#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_work_people_b.h"

#include "bn_regular_bg_items_bg_work_lab.h"

namespace game{
WorkLab::WorkLab(Player& _player,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_work_lab.create_bg(8,48),bn::fixed_rect(0,0,240,132),_player),
    pc_screen(bn::sprite_items::pc_screen.create_sprite(-28,17)),
    global_var(_global_var){

    global_var.setDayChoice(global_var.currentDay(),CHOICE::WORK);
    global_var.getDialogManager().resetBottomText();
    global_var.getDialogManager().resetBg();

    player.resetAnim();
    player.setHflip(true);
    player.setPos(60,23);
    player.setMovementBox(bn::fixed_rect(0,0,240,160));

    switch(global_var.currentDay()){
        case 3:
            loadDay3();
            break;
        case 2:
        default:
            loadDay1_2();
            break;
    }

    setVisibility(false);
}

void WorkLab::setVisibility(bool visibility){
    bg->set_visible(visibility);
    bg_paper->set_visible(visibility);

    for(auto& npc : npcs){
        npc.setVisibility(visibility);
    }

    pc_screen.set_visible(visibility);

    player.setVisible(visibility);
}

void WorkLab::loadDay1_2(){
    npcs.push_back(bn::sprite_items::work_people.create_sprite(-92,23,2));
    npcs.push_back(bn::sprite_items::work_people.create_sprite(-8,23,6)); 
}

void WorkLab::loadDay3(){
    npcs.push_back(bn::sprite_items::work_people_b.create_sprite(-110,22));
    npcs.back().setHorizontalFlip(true);
    npcs.push_back(bn::sprite_items::work_people.create_sprite(103,23,2));
    npcs.push_back(bn::sprite_items::work_people.create_sprite(-48,23,5));
    npcs.back().setHorizontalFlip(true);
    npcs.back().getPalette().set_color(12,bn::color(6,3,2)); //Change hair color
    npcs.back().getPalette().set_color(19,bn::color(0,0,0)); //Change shirt color

    player.setPos(-13,23);
}

bn::optional<RoomExit> WorkLab::update(){

    if(initial_dark.elapsedFrames() <= 54){
        if(initial_dark.elapsedFrames() >= 54){
            setVisibility(true);
        }
    }

    if(initial_dark.elapsedFrames() >= 54){
        if(end_room.elapsedFrames() >= 240){
            return RoomExit("day_change",DIRECTION::DOOR1);
        }
    }

    Room::update();

    return bn::nullopt;
}

}