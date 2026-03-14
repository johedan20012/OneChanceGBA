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

int main(){
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));


    //bn::regular_bg_ptr bg_house_1 = bn::regular_bg_items::bg_house_2.create_bg(8, 48);
    game::Player character;
    //bn::regular_bg_ptr bg_paper = bn::regular_bg_items::bg_paper_2.create_bg(8, 48);


    bn::unique_ptr<game::Room> current_room = game::RoomLoader::loadRoom("house_bedroom",character);
    bn::optional<bn::string<15>> next_room = bn::nullopt;

    while(true){ 

        current_room.get()->update();

        next_room = current_room.get()->checkExits();
        if(next_room.has_value()){
            BN_LOG("Changing room");
            auto new_room = game::RoomLoader::loadRoom(*next_room.get(), character);
            if(new_room) current_room = std::move(new_room);
            else BN_LOG("Error loading room: ",next_room.get());
        }

        bn::core::update();
    }
}
