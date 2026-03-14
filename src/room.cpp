#include "room.h"

namespace game{

Room::Room(const bn::regular_bg_ptr _bg, bn::optional<bn::regular_bg_ptr> _bg_paper,Player& _player):
    bg(_bg),bg_paper(_bg_paper),player(_player){
    
    bg.set_priority(3);
    if(bg_paper.has_value()){ 
        bg_paper.get()->set_priority(1);
        bg_paper.get()->set_blending_enabled(true);
    }

    background_weight = 0.49804; // Best values manually calculated
    foreground_weight = 0.35546; 
    bn::blending::set_transparency_weights(foreground_weight, background_weight);
}

Room::~Room() = default;

bn::optional<bn::string<15>> Room::checkExits(){
    for(int i = 0; i < exits.size(); i++){
        if(exits[i].intersects(player.boundaries())) return exitsName[i];
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

    if(bn::keypad::start_pressed()){
        BN_LOG("Background alpha: ", background_weight);
        BN_LOG("Foreground alpha: ", foreground_weight);
        BN_LOG("Position: (", player.getPos().x(), ", ", player.getPos().y(), ")");
    }
}
}