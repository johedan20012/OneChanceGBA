#include "player.h"

#include "bn_log.h"

namespace game{

Player::Player():
    // Value calculated manually for house_1 
    sprite(bn::sprite_items::character.create_sprite(0,0)),
    walking(bn::create_sprite_animate_action_forever(
        sprite,6,bn::sprite_items::character.tiles_item(),2,1)),
    movement_box(0,0,280,180){

    sprite.set_bg_priority(2);
    sprite.set_z_order(1);
}

void Player::resetAnim(){
    sprite.set_tiles(bn::sprite_items::character.tiles_item().create_tiles(0));
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

void Player::setMovementBox(bn::fixed_rect _movement_box){
    movement_box = _movement_box;
}

bn::fixed_rect Player::movementBox(){
    return movement_box;
}

void Player::setVisible(bool _visible){
    sprite.set_visible(_visible);
}

void Player::setHflip(bool flip){
    sprite.set_horizontal_flip(flip);
}

void Player::update(){
    moving_dir = 0;
    if(bn::keypad::right_held()) moving_dir = 1;
    if(bn::keypad::left_held()) moving_dir = -1;

    if(prev_mov_dir != 0 && moving_dir == 0) sprite.set_tiles(bn::sprite_items::character.tiles_item().create_tiles(0));
    if(moving_dir != 0 && prev_mov_dir != moving_dir){
        walking.reset();
        if(moving_dir == 1) sprite.set_horizontal_flip(false);
        if(moving_dir == -1) sprite.set_horizontal_flip(true);
    }

    if(moving_dir != 0){
        sprite.set_x(sprite.x() + moving_dir);
        if(sprite.x() < movement_box.left()) sprite.set_x(movement_box.left());
        if(sprite.x() > movement_box.right()) sprite.set_x(movement_box.right());
        walking.update();
    }

    if(bn::keypad::up_pressed()){
        sprite.set_y(sprite.y() - 1);
    }else if(bn::keypad::down_pressed()){
        sprite.set_y(sprite.y() + 1);
    }



    prev_mov_dir = moving_dir;
}

}