#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_blending.h"
#include "bn_log.h"

#include "bn_bg_palettes.h"

#include "globalVariables.h"
#include "player.h"
#include "roomLoader.h"
#include "timer.h"

int main(){
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));

    game::Player character;
    game::GlobalVariables global_var;

    bn::unique_ptr<game::Room> current_room;
    
    #ifdef DEBUG_GAME
    global_var.goNextDay();global_var.goNextDay();global_var.goNextDay();global_var.goNextDay();
    global_var.setDayChoice(1,game::CHOICE::SKIP_WORK);
    global_var.setDayChoice(2,game::CHOICE::WORK);
    global_var.setDayChoice(3,game::CHOICE::GO_HOME);

    current_room = game::RoomLoader::loadRoom(game::RoomExit("house_entrance",game::DIRECTION::LEFT),character,global_var);
    #else
    if(global_var.endType().has_value()) current_room = game::RoomLoader::loadRoom(game::RoomExit("end",game::DIRECTION::DOOR1),character,global_var);
    else current_room = game::RoomLoader::loadRoom(game::RoomExit("day_change",game::DIRECTION::DOOR1),character,global_var);
    #endif

    bn::optional<game::RoomExit> next_room = bn::nullopt;

    while(true){ 
        next_room = current_room.get()->update();
        if(next_room.has_value()){
            current_room.reset();
            current_room = game::RoomLoader::loadRoom(next_room.value(), character,global_var);
        }

        if(bn::keypad::select_held() && bn::keypad::a_pressed()){
            global_var.goNextDay();
            BN_LOG("Current day:",global_var.currentDay());
        }

        if(bn::keypad::select_held() && bn::keypad::b_pressed()){
            global_var.setRoofCheckedDay3(true);
            BN_LOG("Roof checked on day 3");
            BN_LOG("Work skipped on day 4A");
            BN_LOG("Defended on day 5A");
            global_var.setDayChoice(4,game::CHOICE::SKIP_WORK);
            global_var.setDayChoice(5,game::CHOICE::DEFEND);
            character.useNightColors(true);
        }

        if(bn::keypad::select_held()){
            BN_LOG("CPU:",int(bn::core::last_cpu_usage()*100),"%");
        }
        

        global_var.getDialogManager().update();
        game::Timer::update();
        bn::core::update();
    }
}
