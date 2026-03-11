#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_blending.h"
#include "bn_log.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_character.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg_paper.h"
#include "bn_regular_bg_items_bg_house_1.h"
#include "bn_regular_bg_items_bg_paper_w.h"
#include "bn_regular_bg_items_bg_paper_g.h"

class Aux{
public:
    Aux();
    virtual ~Aux() = 0;

    virtual void update() = 0;
};

class A : public Aux{   

public:
    A();
    ~A() = default;

    void update() final {
        BN_LOG("A");
    }
};

int main(){
    bn::core::init();


    bn::regular_bg_ptr bg_house_1 = bn::regular_bg_items::bg_house_1.create_bg(8, 48);
    bn::sprite_ptr character = bn::sprite_items::character.create_sprite(0, 16);
    bn::regular_bg_ptr bg_paper = bn::regular_bg_items::bg_paper.create_bg(8, 48);

    bg_house_1.set_priority(3);
    character.set_bg_priority(2);
    bg_paper.set_priority(1);

    bg_paper.set_blending_enabled(true);

    bn::fixed transparency_alpha = 0.75;
    bn::fixed intensity_alpha = 0.5;
    bn::blending::set_transparency_alpha(transparency_alpha);
    bn::blending::set_intensity_alpha(intensity_alpha);
    bool change_intensity = false;

    int white_grad = 0;

    while(true){ 
        if(bn::keypad::left_held()){
            character.set_x(character.x() - 1);
        }else if(bn::keypad::right_held()){
            character.set_x(character.x() + 1);
        }

        if(bn::keypad::l_held() && !change_intensity){
            transparency_alpha = bn::max(transparency_alpha - 0.01, bn::fixed(0));
            bn::blending::set_transparency_alpha(transparency_alpha);
            
        }else if(bn::keypad::r_held() && !change_intensity){
            transparency_alpha = bn::min(transparency_alpha + 0.01, bn::fixed(1));
            bn::blending::set_transparency_alpha(transparency_alpha);
        }

        if(bn::keypad::l_held() && change_intensity){
            intensity_alpha = bn::max(intensity_alpha - 0.01, bn::fixed(0));
            bn::blending::set_intensity_alpha(intensity_alpha);
            
        }else if(bn::keypad::r_held() && change_intensity){
            intensity_alpha = bn::min(intensity_alpha + 0.01, bn::fixed(1));
            bn::blending::set_intensity_alpha(intensity_alpha);
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
            BN_LOG("Transparency alpha: ", transparency_alpha);
            BN_LOG("Intensity alpha: ", intensity_alpha);
        }

        bn::core::update();
    }
}
