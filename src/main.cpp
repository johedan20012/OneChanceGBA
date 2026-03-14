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

int main(){
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));


    bn::regular_bg_ptr bg_house_1 = bn::regular_bg_items::bg_house_2.create_bg(8, 48);
    game::Player character;
    bn::regular_bg_ptr bg_paper = bn::regular_bg_items::bg_paper_2.create_bg(8, 48);

    bg_house_1.set_priority(3);
    bg_paper.set_priority(1);

    bg_paper.set_blending_enabled(true);

    bn::fixed background_weight = 0.49804; // Best values manually calculated
    bn::fixed foreground_weight = 0.35546; 
    bn::blending::set_transparency_weights(foreground_weight, background_weight);
    bool change_intensity = false;

    int white_grad = 0;

    while(true){ 

        character.update();

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

        if(bn::keypad::a_pressed()){
            switch (white_grad){
            case 0:
                bg_paper.set_item(bn::regular_bg_items::bg_paper_g);
                break;
            
            case 1:
                bg_paper.set_item(bn::regular_bg_items::bg_paper_w);
                break;

            default: // 2
                bg_paper.set_item(bn::regular_bg_items::bg_paper);
                break;
            }

            white_grad = (white_grad + 1) % 3;
        }

        if(bn::keypad::start_pressed()){
            BN_LOG("Background alpha: ", background_weight);
            BN_LOG("Foreground alpha: ", foreground_weight);
            BN_LOG("Position: (", character.getPos().x(), ", ", character.getPos().y(), ")");
        }

        bn::core::update();
    }
}
