#include "player.h"

namespace game{

Player::Player():
    // Value calculated manually for house_1 
    sprite(bn::sprite_items::character.create_sprite(0,0)),
    walking(bn::create_sprite_animate_action_forever(
        sprite,12,bn::sprite_items::character.tiles_item(),2,1))
    {

    sprite.set_bg_priority(2);
    sprite.set_z_order(1);
}

void Player::setPos(bn::fixed x,bn::fixed y){
    sprite.set_position(x,y);
}

bn::fixed_point Player::getPos(){
    return sprite.position();
}

bn::fixed_rect Player::boundaries(){
    return bn::fixed_rect(sprite.position(),bn::fixed_size(14,45));
}

void Player::setVisible(bool _visible){
    sprite.set_visible(_visible);
}

void Player::update(){
    if(bn::keypad::right_released()){
        sprite.set_tiles(bn::sprite_items::character.tiles_item().create_tiles(0));
    }

    if(bn::keypad::left_released()){
        sprite.set_tiles(bn::sprite_items::character.tiles_item().create_tiles(0));
    }

    if(bn::keypad::right_pressed()){
        sprite.set_horizontal_flip(false);
        walking.reset();
    }

    if(bn::keypad::left_pressed()){
        sprite.set_horizontal_flip(true);
        walking.reset();
    }

    if(bn::keypad::left_held()){
        sprite.set_x(sprite.x() - 1);
        walking.update();
    }else if(bn::keypad::right_held()){
        sprite.set_x(sprite.x() + 1);
        walking.update();
    }else if(bn::keypad::up_held()){
        sprite.set_y(sprite.y() - 1);
    }else if(bn::keypad::down_held()){
        sprite.set_y(sprite.y() + 1);
    }
}

}