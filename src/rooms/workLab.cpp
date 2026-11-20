#include "workLab.h"

#include "bn_sprite_items_ball.h"
#include "bn_sprite_items_molly.h"
#include "bn_sprite_items_john_eyes.h"
#include "bn_sprite_items_pc_screen.h"
#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_work_people_b.h"

#include "bn_regular_bg_items_bg_work_lab.h"
#include "bn_regular_bg_items_bg_work_lab_b.h"

#include "bn_assert.h"

namespace game{
WorkLab::WorkLab(Player& _player,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_work_lab.create_bg(8,48),bn::fixed_rect(0,0,240,132),_player,_global_var.getDayVariant(_global_var.currentDay())),
    pc_screen(bn::sprite_items::pc_screen.create_sprite(-28,17)),
    global_var(_global_var){

    if(!(global_var.currentDay() == 5 && Room::variant == 1)) global_var.setDayChoice(global_var.currentDay(),CHOICE::WORK);
    global_var.getDialogManager().resetBottomText();
    global_var.getDialogManager().resetBg();

    player.resetAnim();
    player.setHflip(true);
    player.setPos(60,23);
    player.setMovementBox(bn::fixed_rect(0,0,240,160));

    Room::exits.push_back(RoomExit("day_change",DIRECTION::DOOR1));

    switch(global_var.currentDay()){
        case 3:
            loadDay3();
            break;
        case 4:
            loadDay4();
            break;
        case 5:
            loadDay5();
            break;
        case 6:
            loadDay6();
            break;
        case 2:
        default:
            loadDay1_2();
            break;
    }

    initial_dark = bn::make_unique<Timer>();

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

void WorkLab::loadDay4(){
    npcs.push_back(bn::sprite_items::work_people_b.create_sprite(-110,22));
    npcs.back().setHorizontalFlip(true);
    npcs.push_back(bn::sprite_items::work_people.create_sprite(103,23,2));
    npcs.push_back(bn::sprite_items::work_people.create_sprite(-48,23,5));
    npcs.back().setHorizontalFlip(true);
    npcs.back().getPalette().set_color(12,bn::color(6,3,2)); //Change hair color
    npcs.back().getPalette().set_color(19,bn::color(0,0,0)); //Change shirt color

    player.setPos(-13,23);
    dark_frames = 44;
    show_frames = 174;
}

void WorkLab::loadDay5(){
    player.setPos(-13,23);
    dark_frames = 44;
    show_frames = 174;

    switch (Room::variant){
    case 1: // A variant
        Room::exits[0] = RoomExit("house_entrance",DIRECTION::DOOR1);
        break;
    case 5:
    case 6:
    case 11:
    case 12: // E,F,K,L variant
        player.carryMolly(false);
        npcs.push_back(bn::sprite_items::molly.create_sprite(80,42));
        npcs.push_back(bn::sprite_items::ball.create_sprite(92,54));
        break;
    default:
        break;
    }
}

void WorkLab::loadDay6(){
    // A,I variant
    bg->set_item(bn::regular_bg_items::bg_work_lab_b);
    dark_frames = 44;
    john_eyes = bn::make_unique<bn::sprite_ptr>(bn::sprite_items::john_eyes.create_sprite(74,18));
    john_eyes->set_visible(false);
    john_eyes->set_rotation_angle(270);
    john_eyes->set_horizontal_flip(true);
    john_eyes_pal = bn::make_unique<bn::sprite_palette_ptr>(john_eyes->palette());
    john_eyes_pal->set_color(1,bn::color{25,22,18});
    john_eyes_pal->set_color(2,bn::color(0));
    john_eyes_pal->set_color(3,bn::color(0));
    john_eyes_pal->set_color(4,bn::color(0));
    global_var.saveEndType(2);    
}

bn::optional<RoomExit> WorkLab::update(){
    if(initial_dark && initial_dark->elapsedFrames() >= dark_frames){
        setVisibility(true);
        end_room = bn::make_unique<Timer>();
        initial_dark.reset();
        if(global_var.currentDay() == 6){
            john_eyes->set_visible(true);
            player.setVisible(false);
        }
    }

    if(global_var.currentDay() == 6){
        if(!end_room) return bn::nullopt;

        if(end_room->elapsedFrames() >= 200 && end_room->elapsedFrames() <= 320 && (end_room->elapsedFrames() - 200)%33 == 0){
            int indx = ((end_room->elapsedFrames() - 200)/33) +1;
            BN_ASSERT(indx >= 1 && indx <= 4, "Invalid indx for John eyes palette", indx);
            john_eyes_pal->set_color(indx,bn::color{25,22,18});
        }

        if(end_room->elapsedFrames() >= 320) end_room.reset();
        return bn::nullopt;
    }

    if(end_room && end_room->elapsedFrames() >= show_frames){
        BN_ASSERT(Room::exits.size() > 0, "WorkLab doesn't have a room to exit to");
        
        if(global_var.currentDay() == 4 && Room::variant == 2){ // B variant
            player.useNightColors(true);
            return RoomExit("house_entrance",DIRECTION::DOOR1);
        }

        if(global_var.currentDay() == 5 && Room::variant == 1) player.useNightColors(true); // A variant
        return Room::exits[0];
    }

    Room::update();

    return bn::nullopt;
}
}