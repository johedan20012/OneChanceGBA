#include "decision.h"

#include "bn_sprite_items_selector.h"

#include "bn_regular_bg_items_bg_decision_black.h"
#include "bn_regular_bg_items_bg_decision_options.h"

#include "bn_keypad.h"

#include "jostFontVar8x16.h"

namespace game{
Decision::Decision(Player& _player):
Room(bn::regular_bg_items::bg_decision_options.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
black_overlay(bn::regular_bg_items::bg_decision_black.create_bg(8,48)),
label_gen(JostFontVar8x16),selector(bn::sprite_items::selector.create_sprite(0,0)){
    bg_paper->set_priority(1);
    black_overlay.set_priority(0);

    player.setVisible(false);

    selector.set_visible(false);
    selector.set_bg_priority(0);

    label_gen.set_center_alignment();
    label_gen.set_bg_priority(0);

    label_gen.generate(bn::fixed_point{0,-70},"Take Molly to...",text_sprs);
    label_gen.generate(bn::fixed_point{-75,60},"The Park",text_sprs);
    label_gen.generate(bn::fixed_point{75,60},"Work",text_sprs);
}

Decision::~Decision(){
    player.setVisible(true);
}

bn::optional<RoomExit> Decision::update(){
    Room::update();

    if(bn::keypad::left_pressed()){
        selection = -1;
        selector.set_visible(true);
        selector.set_position(-75,66);
    }
    if(bn::keypad::right_pressed()){
        selection = 1;
        selector.set_visible(true);
        selector.set_position(75,66);
    }

    if(selection != 0 && bn::keypad::a_pressed()){
        if(selection == -1) return RoomExit("park",DIRECTION::LEFT);
        else return RoomExit("work_lobby",DIRECTION::LEFT);
    }

    return bn::nullopt;
}
}