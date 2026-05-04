#include "player.h"

#include "bn_sprite_palette_ptr.h"
#include "bn_sprite_items_character.h"
#include "bn_sprite_items_light_bathroom.h"

#include "bn_log.h"
#include "bn_assert.h"
#include "bn_memory.h"

namespace game{

Player::Player():
    spr_tiles(bn::sprite_tiles_ptr::allocate(32,bn::bpp_mode::BPP_4)),
    sprite(bn::sprite_ptr::create(0,0,bn::sprite_shape_size(32,64),spr_tiles,bn::sprite_palette_ptr::create(bn::sprite_items::character.palette_item()))),
    state(STATE::NORMAL),movement_box(0,0,280,180){

    changeTiles(0);
    sprite.set_bg_priority(2);
    sprite.set_z_order(1);
}

void Player::resetWalk(){
    walk_elapsed_frames = 0;
    walk_indx = 0;
    changeTiles(walk_tile_indx[0]*32);
}

void Player::updateWalk(){
    walk_elapsed_frames++;
    if(walk_elapsed_frames == wait_frames){
        walk_elapsed_frames = 0;
        walk_indx = (walk_indx+1) %2;
        changeTiles(walk_tile_indx[walk_indx]*32);
    }
}

void Player::changeTiles(int tiles_start){
    BN_ASSERT(tiles_start >= 0, "Can't use negative tiles_start");
    BN_ASSERT(tiles_start+31 < (character_bn_gfxTilesLen / 32), "Not enough tiles to copy for character: ",tiles_start,",",(character_bn_gfxTilesLen / 32));
    bn::memory::copy(character_bn_gfxTiles[tiles_start],32,spr_tiles.vram().value()[0]);
    curr_tiles = tiles_start/32;
    //BN_LOG("curr_tiles:",curr_tiles);
}

uint32_t Player::getLightRow(int spr,int x,int y){
    BN_ASSERT(spr<=1 && spr>=0,"There is only 2 light sprites");
    if(x < 0 || x > 31 || y < 0 || y > 31)
        return 4;

    return (light_bathroom_bn_gfxTiles[(16*spr) + ((y/8)*4) + (x/8)].data[y%8] & (0xF << ((x%8)*4))) >> ((x%8)*4);
}

uint32_t Player::getLightRow(int spr,bn::fixed_point row_start_pos){
    BN_ASSERT(spr<=1 && spr>=0,"There is only 2 light sprites");
    bn::fixed_point pixel_coord = row_start_pos - (LIGHT_POS[spr]-bn::fixed_point(16,16));

    int x = pixel_coord.x().shift_integer();
    int y = pixel_coord.y().shift_integer();

    return getLightRow(spr,x,y);
}

void Player::updateLightBathroomDay4(){
    BN_ASSERT(curr_tiles>= 5, "Bad use of light bathroom day 4");

    changeTiles(curr_tiles*32); // Clean previous mess

    // y : 0 to 16 custom ilumination
    // y : 17 to 63 rectangle ilumination, this rectangle goes from 30 in x to 99
    bn::fixed_rect spr_box(sprite.position(),bn::fixed_size(32,64));    
    int l = 0,r = 31;
    if(LIGHT_BOX.right() < spr_box.left() || LIGHT_BOX.left() > spr_box.right()){
        return;    // Entire character is in the dark
    }
    
    l = (LIGHT_BOX.left() - spr_box.left()).right_shift_integer();
    l = bn::min(bn::max(l,-1),31);

    r = (LIGHT_BOX.right() - spr_box.left()).right_shift_integer();
    r = bn::min(bn::max(r,0),32);

     // Butano doesnt update the oam until next frame after modification
    bool aux_fliped = fliped;
    if(wait_frame){
        aux_fliped = !aux_fliped;
        wait_frame = false;
    }

    if(aux_fliped){
        l = (l*-1)+31;
        r = (r*-1)+31;

        int aux = l;
        l = r;
        r = aux;
    }

    BN_ASSERT(l<=r,"Bad math in update light bathroom day 4");
    
    if(l == -1 && r == 32){ // Entire character is in the light 
        bn::memory::copy(character_bn_gfxTiles[(curr_tiles-5)*32],32,spr_tiles.vram().value()[0]);
        return;
    }
    BN_ASSERT(l != 32 && r != -1,"Really bad math cmon");// if the character is entery inside, both conditions are true

    bn::span<bn::tile> tiles_vram = spr_tiles.vram().value();
    int tile_index;
    int base_tiles = (curr_tiles-5)*32;
    int dark_base_tiles = curr_tiles*32;

    /*Handle the head*/
    bn::fixed_point pos;
    int real_x,aux;
    

    for(int y = 0; y<= 16; y++){
        for(int x = 0; x<32; x+=8){
            tile_index = (y/8)*4 + (x/8);
            tiles_vram[tile_index].data[y%8] = character_bn_gfxTiles[base_tiles+tile_index].data[y%8]; // Use the light row
        }
        
        for(int x = 0; x<32; x++){
            tile_index = (y/8)*4 + (x/8);

            real_x = x;
            
            if(aux_fliped) real_x = (real_x*-1) + 31;

            pos = sprite.position();
            pos.set_x(pos.x()+real_x-16);
            pos.set_y(pos.y()+y-32);
            
            if(((tiles_vram[tile_index].data[y%8]& (0xF << ((x%8)*4))) >> ((x%8)*4)) > 1){
                aux = getLightRow(0,pos) & getLightRow(1,pos);

                tiles_vram[tile_index].data[y%8] += aux << ((x%8)*4);
            }
        }
    }

    /*Handle the rest of the body*/
    if(l != -1){ // l is the x postion when light enters
        
        uint32_t mask_light = 0xF;
        int fs = 8 - (l%8);
        for(int i=1; i<= fs; i++){
            mask_light <<= 4;
            mask_light |= 0xF;
        }
        mask_light <<= (l%8)*4;
        uint32_t mask_dark = ~mask_light;

        for(int y = 17; y <= 63; y++){
            tile_index = (y/8)*4 + l/8;

            tiles_vram[tile_index].data[y%8] &= mask_dark;
            tiles_vram[tile_index].data[y%8] |= character_bn_gfxTiles[base_tiles+tile_index].data[y%8]&mask_light;
        }

        for(int x = ((l/8)+1)*8; x <= 31; x+= 8){
            for(int y = 17; y <= 63; y++){
                tile_index = (y/8)*4 + x/8;
                
                tiles_vram[tile_index].data[y%8] = character_bn_gfxTiles[base_tiles+tile_index].data[y%8];
            }
        }
    }else{ // r != 32, r is the x position when light dissapears
        uint32_t mask_dark = 0xF;
        int fs = 8 - (r%8);
        for(int i=1; i<= fs; i++){
            mask_dark <<= 4;
            mask_dark |= 0xF;
        }
        mask_dark <<= (r%8)*4;
        uint32_t mask_light = ~mask_dark;

        for(int y = 17; y <= 63; y++){
            tile_index = (y/8)*4 + r/8;

            tiles_vram[tile_index].data[y%8] = character_bn_gfxTiles[base_tiles+tile_index].data[y%8];
            tiles_vram[tile_index].data[y%8] &= mask_light;
            tiles_vram[tile_index].data[y%8] |= character_bn_gfxTiles[dark_base_tiles+tile_index].data[y%8]&mask_dark;
        }

        for(int x = 0; x < (r/8)*8; x+=8){
            for(int y = 17; y <= 63; y++){
                tile_index = (y/8)*4 + x/8;
                
                tiles_vram[tile_index].data[y%8] = character_bn_gfxTiles[base_tiles+tile_index].data[y%8];
            }
        }
    }
}

void Player::takeOffLabCoat(){
    indx_spr_still = 5;
    indx_spr_mov_1 = 7;
    indx_spr_mov_2 = 6;
    indx_spr_bend_1 = 8;
    indx_spr_bend_2 = 9;

    lab_coat = false;
    changeTiles(5*32); // A sprite of 32x64 uses 32 tiles   
    walk_tile_indx[0] = 7;
    walk_tile_indx[1] = 6;
}

void Player::resetAnim(){
    changeTiles(indx_spr_still*32);
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

bn::sprite_palette_ptr Player::getPalettePtr(){
    return sprite.palette();
}

void Player::useNightColors(bool use_night){
    if(lab_coat) takeOffLabCoat();

    if(use_night){ 
        indx_spr_still = 10;
        indx_spr_mov_1 = 12;
        indx_spr_mov_2 = 11;
    }else{
        indx_spr_still = 5;
        indx_spr_mov_1 = 7;
        indx_spr_mov_2 = 6;
    }

    changeTiles(indx_spr_still*32); // A sprite of 32x64 uses 32 tiles   
    walk_tile_indx[0] = indx_spr_mov_1;
    walk_tile_indx[1] = indx_spr_mov_2;
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
    changeTiles(indx_spr_bend_1*32);
    sprite.set_rotation_angle(270);

    bend_stand_timer = bn::make_unique<Timer>();
}

void Player::standUp(){
    state = STATE::STANDING_UP;

    changeTiles(indx_spr_bend_1*32);

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
    fliped = flip;
}

void Player::setUseLightBathroomDay4(bool use){
    use_light_bathroom_day_4 = use;
}

void Player::update(bool frozen){
    if(state == STATE::END_BENDING) return;

    if(state == STATE::BENDING){
        if(!bend_stand_timer) return;
        if(bend_stand_timer->elapsedFrames() == 14) changeTiles(indx_spr_bend_2*32);
        if(bend_stand_timer->elapsedFrames() >= 24){ state = STATE::END_BENDING; bend_stand_timer.reset();}
        return;
    }

    if(state == STATE::STANDING_UP){
        if(!bend_stand_timer) return;
        if(bend_stand_timer->elapsedFrames() == 9){
            changeTiles(indx_spr_still*32);
            sprite.set_position(sprite.position() - bn::fixed_point(23,11));
            sprite.set_rotation_angle(0);
        }
        if(bend_stand_timer->elapsedFrames() >= 13){ state = STATE::NORMAL; bend_stand_timer.reset();}
        return;
    }


    moving_dir = 0;
    if(bn::keypad::right_held()) moving_dir = 1;
    if(bn::keypad::left_held()) moving_dir = -1;

    if(prev_mov_dir != 0 && moving_dir == 0) changeTiles(indx_spr_still*32);
    if(moving_dir != 0 && prev_mov_dir != moving_dir){
        resetWalk();
        if(moving_dir == 1){ sprite.set_horizontal_flip(false); if(fliped){ wait_frame = true;} fliped = false;}
        if(moving_dir == -1){ sprite.set_horizontal_flip(true); if(!fliped){wait_frame = true;} fliped = true; }
    }

    if(moving_dir != 0){
        if(!frozen) sprite.set_x(sprite.x() + (moving_dir*PLAYER_SPEED));
        if(sprite.x() < movement_box.left() - 1) sprite.set_x(movement_box.left()-1);
        if(sprite.x() > movement_box.right() + 1) sprite.set_x(movement_box.right()+1);
        updateWalk();
    }else{
        if(sprite.x() <= movement_box.left()) sprite.set_x(sprite.x()+1);
        if(sprite.x() >= movement_box.right()) sprite.set_x(sprite.x()-1);
    }

    if(use_light_bathroom_day_4) updateLightBathroomDay4(); //

    prev_mov_dir = moving_dir;

    if(bn::keypad::up_pressed()){
        sprite.set_y(sprite.y() - 1);
    }else if(bn::keypad::down_pressed()){
        sprite.set_y(sprite.y() + 1);
    }
}

}