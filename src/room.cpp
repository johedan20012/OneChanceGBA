#include "room.h"

namespace game{

Room::Room(const bn::regular_bg_ptr _bg, bn::fixed_rect _paper_boundaries,Player& _player):
    bg(_bg),bg_paper(bn::regular_bg_items::bg_paper_full.create_bg(8,48)),player(_player){
    
    bg.set_priority(3);
    bg_paper.set_priority(1);
    bg_paper.set_blending_enabled(true);
    bn::window::outside().set_show_bg(bg_paper,false);

    bn::rect_window::internal().set_boundaries(_paper_boundaries);
    bn::rect_window::internal().set_visible(true);

    background_weight = 0.64843; // Best values manually calculated
    foreground_weight = 0.20507; 
    bn::blending::set_transparency_weights(foreground_weight, background_weight);
}

Room::~Room() = default;

bn::optional<RoomExit> Room::checkExits(){
    for(int i = 0; i < exits.size(); i++){
        if(exits[i].needs_action && !bn::keypad::a_pressed()) continue;
        if(exits[i].trigger.intersects(player.boundaries())) return exits[i];
    }
    return bn::nullopt;
}

void Room::update(){
    if(bn::keypad::l_held() && !change_intensity){
        background_weight = bn::max(background_weight - 0.01, bn::fixed(0));
        bn::blending::set_transparency_weights(foreground_weight, background_weight);
        
    }else if(bn::keypad::r_held() && !change_intensity){
        background_weight = bn::min(background_weight + 0.01, bn::fixed(1));
        bn::blending::set_transparency_weights(foreground_weight, background_weight);
    }

    if(bn::keypad::l_held() && change_intensity){
        foreground_weight = bn::max(foreground_weight - 0.01, bn::fixed(0));
        bn::blending::set_transparency_weights(foreground_weight, background_weight);
        
    }else if(bn::keypad::r_held() && change_intensity){
        foreground_weight = bn::min(foreground_weight + 0.01, bn::fixed(1));
        bn::blending::set_transparency_weights(foreground_weight, background_weight);
    }

    if(bn::keypad::b_pressed()){
        change_intensity = !change_intensity;
    }

    if(bn::keypad::select_held()){
        auto x = bn::rect_window::internal().boundaries().x();
        auto y = bn::rect_window::internal().boundaries().y();
        if(bn::keypad::left_pressed()){
            x -= 1.0;
        }else if(bn::keypad::right_pressed()){
            x += 1.0;
        }else if(bn::keypad::up_pressed()){
            y -= 1.0;
        }else if(bn::keypad::down_pressed()){
            y += 1.0;
        }
        bn::rect_window::internal().set_boundaries(bn::fixed_rect(x,y,bn::rect_window::internal().boundaries().width(),bn::rect_window::internal().boundaries().height()));
    }

    if(bn::keypad::start_pressed()){
        BN_LOG("Background weight: ", background_weight);
        BN_LOG("Foreground weight: ", foreground_weight);
        BN_LOG("Position: (", player.getPos().x(), ", ", player.getPos().y(), ")");

        BN_LOG("Position InnnerWindow: ",bn::rect_window::internal().boundaries().x()," ",bn::rect_window::internal().boundaries().y());
    }
}
}