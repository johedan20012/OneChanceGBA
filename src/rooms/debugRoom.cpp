#ifdef DEBUG_GAME
#include "debugRoom.h"

#include "bn_sprite_items_sign.h"

#include "bn_regular_bg_items_bg_house_1.h"

#include "jostFontVar8x16.h"

namespace game{

const bn::string<15> DebugRoom::roomsNames[DebugRoom::MAX_ROOMS] = {
    /* 0*/ "house_bedroom",
    /* 1*/ "house_hall",
    /* 2*/ "house_molly",
    /* 3*/ "house_bath",
    /* 4*/ "house_entrance",
    /* 5*/ "city",
    /* 6*/ "work_parking",
    /* 7*/ "work_lobby",
    /* 8*/ "work_hall",
    /* 9*/ "work_lab_door",
    /*10*/ "work_stairs",
    /*11*/ "skip_work",
    /*12*/ "work_lab",
    /*13*/ "day_change",
    /*14*/ "work_roof",
    /*15*/ "end",
    /*16*/ "decision"
};
    
DebugRoom::DebugRoom(Player& _player, GlobalVariables& _global_var):
Room(bn::regular_bg_items::bg_house_1.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
global_var(_global_var),cursor(bn::sprite_items::sign.create_sprite(-116,-70)),
info_gen(JostFontVar8x16){

    bg->set_visible(false);
    bg_paper->set_visible(false);

    info_gen.set_left_alignment();
    info_gen.set_bg_priority(2);
    info_gen.set_z_order(0);

    display_info();
}

DebugRoom::~DebugRoom(){
    if(!player_lab_coat) player.takeOffLabCoat();
    if(player_night_colors) player.useNightColors(player_night_colors);
}

bn::optional<RoomExit> DebugRoom::update(){

    if(bn::keypad::down_pressed() || bn::keypad::up_pressed()){
        if(bn::keypad::down_pressed()) option_selected = (option_selected+1) % MAX_OPTIONS;
        else option_selected--;
        if(option_selected < 0) option_selected = MAX_OPTIONS-1;

        cursor.set_y(bn::fixed{-70 + option_selected*10});
    }

    if(bn::keypad::a_pressed()){
        switch (option_selected){
        case 6:
            room_selected = (room_selected+1)%MAX_ROOMS;
            break;
        case 7:
            global_var.setDay(global_var.currentDay()+1);
            break;
        case 8:
            global_var.setVisitedLabDoor(!global_var.hasVisitedLabDoor());
            break;
        case 9:
            global_var.setVisitedWorkHall(!global_var.hasVisitedWorkHall());
            break;
        case 10:
            global_var.setRoofCheckedDay3(!global_var.roofCheckedDay3());
            break;
        case 11:
            player_lab_coat = !player_lab_coat;
            break;
        case 12:
            player_night_colors = !player_night_colors;
            break;
        case 13:
            molly_on_players_back = !molly_on_players_back;
            player.carryMolly(molly_on_players_back);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        default: // day 1-6
            {
            CHOICE new_choice = to_choice(static_cast<int>(global_var.dayChoice(option_selected+1))+1);
            global_var.setDayChoice(option_selected+1,new_choice);
            break;
            }
        }

        display_info();
    }

    if(bn::keypad::start_pressed()) return RoomExit(roomsNames[room_selected%MAX_ROOMS],DIRECTION::LEFT);

    return bn::nullopt;
}

void DebugRoom::display_info(){
    text_sprs.clear();
    info_gen.generate(bn::fixed_point{-110,-70},"Day 1",text_sprs);
    info_gen.generate(bn::fixed_point{-110,-60},"Day 2",text_sprs);
    info_gen.generate(bn::fixed_point{-110,-50},"Day 3",text_sprs);
    info_gen.generate(bn::fixed_point{-110,-40},"Day 4",text_sprs);
    info_gen.generate(bn::fixed_point{-110,-30},"Day 5",text_sprs);
    info_gen.generate(bn::fixed_point{-110,-20},"Day 6",text_sprs);
    info_gen.generate(bn::fixed_point{-110,-10},"room",text_sprs);
    info_gen.generate(bn::fixed_point{-110,0},"day",text_sprs);
    info_gen.generate(bn::fixed_point{-110,10},"VWLD",text_sprs);
    info_gen.generate(bn::fixed_point{-110,20},"VWH",text_sprs);
    info_gen.generate(bn::fixed_point{-110,30},"RCD3",text_sprs);
    info_gen.generate(bn::fixed_point{-110,40},"PLC",text_sprs);
    info_gen.generate(bn::fixed_point{-110,50},"PNC",text_sprs);
    info_gen.generate(bn::fixed_point{-110,60},"MoPB",text_sprs);

    info_gen.generate(bn::fixed_point{-80,-70},choice_to_string(global_var.dayChoice(1)),text_sprs);
    info_gen.generate(bn::fixed_point{-80,-60},choice_to_string(global_var.dayChoice(2)),text_sprs);
    info_gen.generate(bn::fixed_point{-80,-50},choice_to_string(global_var.dayChoice(3)),text_sprs);
    info_gen.generate(bn::fixed_point{-80,-40},choice_to_string(global_var.dayChoice(4)),text_sprs);
    info_gen.generate(bn::fixed_point{-80,-30},choice_to_string(global_var.dayChoice(5)),text_sprs);
    info_gen.generate(bn::fixed_point{-80,-20},choice_to_string(global_var.dayChoice(6)),text_sprs);
    
    room_selected %= MAX_ROOMS;
    info_gen.generate(bn::fixed_point{-80,-10},roomsNames[room_selected],text_sprs);

    bn::string<11> aux_str = bn::to_string<11>(global_var.currentDay());
    info_gen.generate(bn::fixed_point{-80,0},aux_str,text_sprs);
    
    aux_str = bn::to_string<11>(global_var.hasVisitedLabDoor());
    info_gen.generate(bn::fixed_point{-80,10},aux_str,text_sprs);

    aux_str = bn::to_string<11>(global_var.hasVisitedWorkHall());
    info_gen.generate(bn::fixed_point{-80,20},aux_str,text_sprs);

    aux_str = bn::to_string<11>(global_var.roofCheckedDay3());
    info_gen.generate(bn::fixed_point{-80,30},aux_str,text_sprs);

    aux_str = bn::to_string<11>(player_lab_coat);
    info_gen.generate(bn::fixed_point{-80,40},aux_str,text_sprs);

    aux_str = bn::to_string<11>(player_night_colors);
    info_gen.generate(bn::fixed_point{-80,50},aux_str,text_sprs);

    aux_str = bn::to_string<11>(molly_on_players_back);
    info_gen.generate(bn::fixed_point{-80,60},aux_str,text_sprs);
}

}
#endif