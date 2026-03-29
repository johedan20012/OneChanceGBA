#include "room.h"

namespace game{

Room::Room(const bn::regular_bg_ptr _bg, bn::fixed_rect _paper_boundaries,Player& _player):
    info_gen(JostFontVar8x16),exit_info_displayed(-1),bg(_bg),bg_paper(bn::regular_bg_items::bg_paper_full.create_bg(8,48)),player(_player){
    
    bg.set_priority(3);
    bg_paper.set_priority(0);
    bg_paper.set_blending_enabled(true);
    bn::window::outside().set_show_bg(bg_paper,false);

    bn::rect_window::internal().set_boundaries(_paper_boundaries);
    bn::rect_window::internal().set_visible(true);

    info_gen.set_center_alignment();
    info_gen.set_bg_priority(2);
    info_gen.set_z_order(0);

    background_weight = 0.64843; // Best values manually calculated
    foreground_weight = 0.20507; 
    bn::blending::set_transparency_weights(foreground_weight, background_weight);
}

Room::~Room() = default;

#ifdef DEBUG_GAME
void Room::createExitsDebug(){
    for(int i = 0; i < exits.size(); i++){
        bn::fixed_rect box =exits[i].trigger;
        bn::sprite_ptr top_left = bn::sprite_items::debug_corner.create_sprite(box.top_left());
        top_left.set_bg_priority(2);
        top_left.set_z_order(-10);
        bn::sprite_ptr top_right = bn::sprite_items::debug_corner.create_sprite(box.top_right());
        top_right.set_bg_priority(2);
        top_right.set_z_order(-10);
        top_right.set_horizontal_flip(true);
        bn::sprite_ptr bottom_left = bn::sprite_items::debug_corner.create_sprite(box.bottom_left());
        bottom_left.set_bg_priority(2);
        bottom_left.set_z_order(-10);
        bottom_left.set_vertical_flip(true);
        bn::sprite_ptr bottom_right = bn::sprite_items::debug_corner.create_sprite(box.bottom_right());
        bottom_right.set_bg_priority(2);
        bottom_right.set_z_order(-10);
        bottom_right.set_horizontal_flip(true);
        bottom_right.set_vertical_flip(true);
        exits_debug.push_back(top_left);
        exits_debug.push_back(top_right);
        exits_debug.push_back(bottom_left);
        exits_debug.push_back(bottom_right);
    }
}
#endif

bn::optional<RoomExit> Room::checkExits(){
    for(int i = 0; i < exits.size(); i++){
        if(exits[i].needs_action && !bn::keypad::a_held()) continue;
        if(exits[i].trigger.intersects(player.boundaries())) return exits[i];
    }
    return bn::nullopt;
}

void Room::clearExitsInfo(){
    if(!exit_info.empty()) exit_info.clear();
}

void Room::updateExitsInfo(){
    if(exit_info_displayed < 0 || exit_info_displayed >= exits.size()){
        if(exit_info_displayed >= exits.size()) exit_info_displayed = -1;
        for(int i = 0; i < exits.size(); i++){
            if(exits[i].needs_action && exits[i].trigger.intersects(player.boundaries())){
                exit_info.clear();
                player_prev_pos = player.getPos()+bn::fixed_point(0,-37);
                info_gen.generate(player_prev_pos,exits[i].info,exit_info);
                exit_info_displayed = i;
                BN_LOG("Generating:",exits[i].info);
                return;
            }
        }
        return;
    }

    if(!exits[exit_info_displayed].trigger.intersects(player.boundaries())){
        exit_info_displayed = -1;
        exit_info.clear();
        return;
    }

    bn::fixed_point move_info = player.getPos()+ bn::fixed_point(0,-37) - player_prev_pos;
    if(move_info.x() != 0 || move_info.y() != 0){
        for(auto text_spr : exit_info){
            text_spr.set_position(text_spr.position() + move_info);
        }
    }
    player_prev_pos = player.getPos()+ bn::fixed_point(0,-37);
}

bn::optional<RoomExit> Room::update(){
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

    return bn::nullopt;
}
}