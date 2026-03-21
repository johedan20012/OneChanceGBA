#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_blending.h"
#include "bn_log.h"

#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg_paper.h"
#include "bn_regular_bg_items_bg_paper_2.h"
#include "bn_regular_bg_items_bg_house_1.h"
#include "bn_regular_bg_items_bg_house_2.h"
#include "bn_regular_bg_items_bg_paper_w.h"
#include "bn_regular_bg_items_bg_paper_g.h"

#include "player.h"
#include "roomLoader.h"
#include "timer.h"

int main(){
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));

    game::Player character;

    bn::unique_ptr<game::Room> current_room = game::RoomLoader::loadRoom(game::RoomExit("work_lab_door",game::DIRECTION::DOOR1),character);
    bn::optional<game::RoomExit> next_room = bn::nullopt;

    while(true){ 
        next_room = current_room.get()->update();
        if(next_room.has_value()){
            current_room.reset();
            current_room = game::RoomLoader::loadRoom(next_room.value(), character);
        }

        game::Timer::update();
        bn::core::update();
    }
}
