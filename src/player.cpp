#include "player.h"

#include "bn_sprite_items_character.h"

#include "bn_log.h"

namespace game{

Player::Player():
    sprite(bn::sprite_items::character.create_sprite(0,0)),
    walking(bn::create_sprite_animate_action_forever(
        sprite,6,bn::sprite_items::character.tiles_item(),2,1)),
    state(STATE::NORMAL),movement_box(0,0,280,180){

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

bn::sprite_tiles_ptr Player::getTilesItem(){
    return sprite.tiles();
}

bool Player::getHorizontalFlip(){
    return sprite.horizontal_flip();
}

bn::fixed_rect Player::boundaries(){
    return bn::fixed_rect(sprite.position(),bn::fixed_size(14,45));
}

void Player::setMovementBox(bn::fixed_rect _movement_box){
    movement_box = _movement_box;
}

bool Player::hasNormalState(){
    return (state == STATE::NORMAL);
}

bool Player::isBended(){
    return (state == STATE::END_BENDING);
}

void Player::bend(){
    state = STATE::BENDING;

    sprite.set_horizontal_flip(false);
    sprite.set_position(sprite.position() + bn::fixed_point(23,11));
    sprite.set_tiles(bn::sprite_items::character.tiles_item().create_tiles(3));
    sprite.set_rotation_angle(270);

    bend_stand_timer = bn::make_unique<Timer>();
}

void Player::standUp(){
    state = STATE::STANDING_UP;

    sprite.set_tiles(bn::sprite_items::character.tiles_item().create_tiles(3));

    bend_stand_timer = bn::make_unique<Timer>();
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
    if(state == STATE::END_BENDING) return;

    if(state == STATE::BENDING){
        if(!bend_stand_timer) return;
        if(bend_stand_timer->elapsedFrames() == 14) sprite.set_tiles(bn::sprite_items::character.tiles_item().create_tiles(4));
        if(bend_stand_timer->elapsedFrames() >= 24){ state = STATE::END_BENDING; bend_stand_timer.reset();}
        return;
    }

    if(state == STATE::STANDING_UP){
        if(!bend_stand_timer) return;
        if(bend_stand_timer->elapsedFrames() == 9){
            sprite.set_tiles(bn::sprite_items::character.tiles_item().create_tiles(0));
            sprite.set_position(sprite.position() - bn::fixed_point(23,11));
            sprite.set_rotation_angle(0);
        }
        if(bend_stand_timer->elapsedFrames() >= 13){ state = STATE::NORMAL; bend_stand_timer.reset();}
        return;
    }


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
    }else{
        if(sprite.x() == movement_box.left()) sprite.set_x(movement_box.left()+1);
        if(sprite.x() == movement_box.right()) sprite.set_x(movement_box.right()-1);
    }

    if(bn::keypad::up_pressed()){
        sprite.set_y(sprite.y() - 1);
    }else if(bn::keypad::down_pressed()){
        sprite.set_y(sprite.y() + 1);
    }

    prev_mov_dir = moving_dir;
}

}