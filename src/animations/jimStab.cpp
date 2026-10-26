#include "jimStab.h"

#include "bn_sprite_items_knife.h"
#include "bn_sprite_items_jim_day5.h"
#include "bn_sprite_items_john_eyes.h"
#include "bn_sprite_items_blood_puddle.h"
#include "bn_sprite_items_character_day5.h"

#include "bn_keypad.h"

#include "day5_john_blood_bin.h"

namespace game{

const bn::point (&JimStab::BLOOD_PUDDLE_PIXELS)[BLOOD_PIXELS_ROWS][BLOOD_PIXELS_COLUMNS] = *reinterpret_cast<const bn::point(*)[BLOOD_PIXELS_ROWS][BLOOD_PIXELS_COLUMNS]>(day5_john_blood_bin);

JimStab::JimStab(bn::fixed_point jim_pos): 
blood_puddle(bn::sprite_items::blood_puddle.create_sprite(0,0)),blood_puddle_palette(blood_puddle.palette()),
jim(bn::sprite_items::jim_day5.create_sprite(0,0)),knife(bn::sprite_items::knife.create_sprite(0,0)),
john(bn::sprite_items::character_day5.create_sprite(0,0)),
john_eyes(bn::sprite_items::john_eyes.create_sprite(0,0)),john_eyes_palette(john_eyes.palette()){
    static_assert(day5_john_blood_bin_size == BLOOD_PIXELS_ROWS*BLOOD_PIXELS_COLUMNS*sizeof(bn::point),"The blood puddle data has an incorrect size.");

    jim.set_position(jim_pos);
    jim.set_tiles(bn::sprite_items::jim_day5.tiles_item(),1);

    john.set_position(jim_pos+bn::fixed_point(-41,5));
    john.set_tiles(bn::sprite_items::character_day5.tiles_item(),0);

    blood_puddle.set_visible(false);

    knife.set_rotation_angle(270);
    knife.set_position(jim_pos+KNIFE_OFFSETS[0]);
    knife.set_horizontal_flip(true);

    john_eyes_palette.set_color(1,bn::color(0));
    john_eyes_palette.set_color(2,bn::color(0));
    john_eyes_palette.set_color(3,bn::color(0));
    john_eyes_palette.set_color(4,bn::color(0));
    john_eyes.set_visible(false);

    state = 0;
}

void JimStab::update(){
    BN_ASSERT(timer.elapsedFrames() <= 600000, "JimStab animation runned for more than 600,000 frames");

    switch (state){
    case 3:
        break;
    case 2:
        if(timer.elapsedFrames() == 690) state = 3;

        if(timer.elapsedFrames() >= 611 && (timer.elapsedFrames() - 611)%25 == 0){
            int indx = ((timer.elapsedFrames() - 611)/25) +1;
            BN_ASSERT(indx >= 1 && indx <= 4, "Invalid indx for John eyes palette");
            john_eyes_palette.set_color(indx,john_eyes_palette.colors()[6]);
        }

        if(timer.elapsedFrames() >= 186 && (timer.elapsedFrames() - 186)%62 == 0){
        {
            int row = (timer.elapsedFrames() - 186)/62;
            BN_ASSERT(row <= 9,"Too many rows expected for blood puddle");
            // This numbers are hard-coded for the specific color palette of blood_puddle
            int new_color_indx = 11 - bn::max(row-5,0);
            for(int i = bn::min(row+1,6); i>=1; --i){
                blood_puddle_palette.set_color(i,blood_puddle_palette.colors()[new_color_indx]);
                new_color_indx = bn::max(7,new_color_indx-1);
            }
        }
        }

        break;
    case 1:
        // Jim leaving the room animation
        // Frame 24 is frame 0
        {
        int jim_anim_fram = (timer.elapsedFrames()-24)%13;
        if(jim_anim_fram == 0) jim.set_tiles(bn::sprite_items::jim_day5.tiles_item(),0);
        else if(jim_anim_fram == 7) jim.set_tiles(bn::sprite_items::jim_day5.tiles_item(),3);
        jim.set_x(jim.x()-bn::fixed(0.9));
        }
        
        if(timer.elapsedFrames() == 116){
            john.set_tiles(bn::sprite_items::character_day5.tiles_item(),2);
            john.set_position(john.position() + JOHN_OFFSETS[0]);
            knife.set_position(knife.position()+KNIFE_OFFSETS[1]);
        }

        if(timer.elapsedFrames() == 154){
            john.set_rotation_angle(270);
            john.set_position(john.position() + JOHN_OFFSETS[1]);
            john.set_tiles(bn::sprite_items::character_day5.tiles_item(),3);
            knife.set_rotation_angle(180);
            knife.set_position(knife.position() + KNIFE_OFFSETS[2]);
            blood_puddle.set_position(john.position() + BLOOD_OFFSET);
            blood_puddle.set_visible(true);
            john_eyes.set_position(john.position() + JOHN_EYES_OFFSET);
            john_eyes.set_visible(true);
        }

        if(timer.elapsedFrames() == 185) state = 2;

        if(bn::keypad::a_pressed()) john.set_rotation_angle(270);
        else if(bn::keypad::b_pressed()) john.set_rotation_angle(0);
        break;
    
    default: // 0 
        if(timer.elapsedFrames() == 5){
            jim.set_position(jim.position()+JIM_OFFSETS[0]);
            knife.set_position(jim.position() + KNIFE_OFFSETS[0]);
        }

        if(timer.elapsedFrames() == 7) john.set_tiles(bn::sprite_items::character_day5.tiles_item(),1);
        
        if(timer.elapsedFrames() == 12) jim.set_tiles(bn::sprite_items::jim_day5.tiles_item(),0);
        
        if(timer.elapsedFrames() == 23) state = 1;
        break;
    }
}

bool JimStab::isFinished(){
    return state == 3;
}

}