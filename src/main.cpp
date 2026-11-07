#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_blending.h"
#include "bn_log.h"

#include "bn_bg_palettes.h"

#include "globalVariables.h"
#include "player.h"
#include "roomLoader.h"
#include "timer.h"

#ifdef DEBUG_GAME
#include "debugRoom.h"
#endif

int main(){
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));

    game::Player character;
    game::GlobalVariables global_var;

    bn::unique_ptr<game::Room> current_room;
    
    #ifdef DEBUG_GAME
    current_room = bn::make_unique<game::DebugRoom>(character,global_var);
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

        #ifdef DEBUG_GAME
        if(bn::keypad::select_held()){
            BN_LOG("CPU:",int(bn::core::last_cpu_usage()*100),"%");
        }
        #endif

        global_var.getDialogManager().update();
        game::Timer::update();
        bn::core::update();
    }
}
