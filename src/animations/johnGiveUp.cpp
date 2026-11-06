#include "johnGiveUp.h"

#include "bn_sprite_items_character_day5_b.h"
#include "bn_sprite_items_jump_sign.h"

namespace game{

JohnGiveUp::JohnGiveUp(bn::fixed_point john_pos):
AnimationFromData(giveup_animation_bin,giveup_animation_bin_size),
john(bn::sprite_items::character_day5_b.create_sprite(0,0,0)),
jump_sign(bn::sprite_items::jump_sign.create_sprite(0,0)){

    john.set_position(john_pos);

    jump_sign.set_visible(false);

    AnimationFromData::add_object(john);
}

void JohnGiveUp::update(){

    if(waiting_confirmation){
        if(bn::keypad::a_pressed()){
            waiting_confirmation = false;
            jump_sign.set_visible(false);
            john.set_tiles(bn::sprite_items::character_day5_b.tiles_item(),3);
            AnimationFromData::frame++;
        }
        return;
    }

    AnimationFromData::update();

    if(AnimationFromData::frame == 9) john.set_tiles(bn::sprite_items::character_day5_b.tiles_item(),1);
    if(AnimationFromData::frame == 21) john.set_tiles(bn::sprite_items::character_day5_b.tiles_item(),0);
    if(AnimationFromData::frame == 31) john.set_tiles(bn::sprite_items::character_day5_b.tiles_item(),2);
    if(AnimationFromData::frame == 45) john.set_tiles(bn::sprite_items::character_day5_b.tiles_item(),0);

    if(AnimationFromData::frame == 61){
        waiting_confirmation = true;
        jump_sign.set_visible(true);
        jump_sign.set_position(john.position() + JUMP_SIGN_OFFSET);
    }

    if(AnimationFromData::frame == 135) john.set_tiles(bn::sprite_items::character_day5_b.tiles_item(),4);

}

}