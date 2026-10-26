#include "jimStabFail.h"

#include "bn_sprite_items_knife.h"
#include "bn_sprite_items_jim_day5.h"
#include "bn_sprite_items_jim_john_arms.h"
#include "bn_sprite_items_character_day5.h"

#include "day5_stabfail_animation_bin.h"

namespace game{

JimStabFail::JimStabFail(bn::fixed_point jim_pos): AnimationFromData(day5_stabfail_animation_bin,day5_stabfail_animation_bin_size),
john(bn::sprite_items::character_day5.create_sprite(0,0,0)),johns_arm(bn::sprite_items::jim_john_arms.create_sprite(0,0,0)),
jim(bn::sprite_items::jim_day5.create_sprite(0,0,4)),jims_arm(bn::sprite_items::jim_john_arms.create_sprite(0,0,1)),
knife(bn::sprite_items::knife.create_sprite(0,0)){

    john.set_z_order(0);
    jim.set_z_order(0);
    knife.set_z_order(-2);
    jims_arm.set_z_order(-1);
    johns_arm.set_z_order(-3);

    jim.set_position(jim_pos);

    john.set_position(jim.position() + JOHN_OFFSETS[0]);

    johns_arm.set_visible(false);
    johns_arm.set_position(john.position() + JOHNS_ARM_OFFSETS[0]);

    knife.set_rotation_angle(270);
    knife.set_horizontal_flip(true);
    knife.set_position(jim.position() + KNIFE_OFFSETS[0]);

    jims_arm.set_vertical_flip(true);
    jims_arm.set_horizontal_flip(true);
    jims_arm.set_position(jim.position() + JIMS_ARM_OFFSET);

    mov.addElement(john);
    mov.addElement(johns_arm);
    mov.addElement(knife);
    mov.addElement(jim);
    mov.addElement(jims_arm);

    AnimationFromData::add_object(john);
    AnimationFromData::add_object(johns_arm);
    AnimationFromData::add_object(knife);
    AnimationFromData::add_object(jim);
    AnimationFromData::add_object(jims_arm);
}

void JimStabFail::update(){
    mov.update();

    switch (state){
    case 3: break; // The animation ended
    case 2: // Frame 43 is 0
        {
        int jim_anim_fram = (timer.elapsedFrames()-43)%13;
        if(jim_anim_fram == 0) jim.set_tiles(bn::sprite_items::jim_day5.tiles_item(),0);
        else if(jim_anim_fram == 6) jim.set_tiles(bn::sprite_items::jim_day5.tiles_item(),3);
        }

        if(timer.elapsedFrames() >= 52){jim.set_x(jim.x()-bn::fixed(0.9));}

        if(timer.elapsedFrames() == 110){ // Flip John to the left
            john.set_horizontal_flip(true);
            johns_arm.set_horizontal_flip(true);
            johns_arm.set_position(john.position() + JOHNS_ARM_OFFSETS[1]);
            johns_arm.set_rotation_angle(95);
            knife.set_horizontal_flip(false);
            knife.set_position(john.position() + KNIFE_OFFSETS[1]);
            knife.set_rotation_angle(330);
        }

        if(timer.elapsedFrames() >= 308) state = 3;
        break;
    case 1:
        AnimationFromData::update();

        if(AnimationFromData::isFinished()){
            state = 2;
            john.set_z_order(-1);
            johns_arm.set_z_order(-2);
            knife.set_z_order(-1);
            jim.set_z_order(0);
            jim.set_tiles(bn::sprite_items::jim_day5.tiles_item(),0);
            jims_arm.set_visible(false);
        }
        break;
    default:
        if(timer.elapsedFrames() == 1){
            john.set_tiles(bn::sprite_items::character_day5.tiles_item(),4);
            johns_arm.set_visible(true);

            jim.set_position(jim.position() + bn::fixed_point(-2,0));
            jims_arm.set_position(jim.position() + JIMS_ARM_OFFSET);

            knife.set_position(jim.position() + KNIFE_OFFSETS[0]);
        }

        if(timer.elapsedFrames() == 3){
            jim.set_position(jim.position() + bn::fixed_point(-4,0));
            jims_arm.set_position(jim.position() + JIMS_ARM_OFFSET);

            knife.set_position(jim.position() + KNIFE_OFFSETS[0]);
        }

        if(timer.elapsedFrames() == 5){
            state = 1;
            frame = 6;
        }

        break;
    }
}

bool JimStabFail::isFinished(){
    return state == 3;
}

}