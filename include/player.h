#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_color.h"
#include "bn_keypad.h"
#include "bn_vector.h"
#include "bn_fixed_rect.h"
#include "bn_unique_ptr.h"

#include "pair.h"
#include "timer.h"

namespace game{
class Player{
private:
    enum class STATE{
        NORMAL,
        BENDING,
        END_BENDING,
        STANDING_UP,
    };

    static constexpr bn::fixed_rect LIGHT_BOX = bn::fixed_rect(63.5,0,67,20);
    static constexpr bn::fixed PLAYER_SPEED = 0.75;
    static constexpr bn::fixed_point LIGHT_POS[2] = {
        bn::fixed_point(46,-2),
        bn::fixed_point(82,-2)
    };

    int indx_spr_still = 0;
    int indx_spr_mov_1 = 2;
    int indx_spr_mov_2 = 1;
    int indx_spr_bend_1 = 3;
    int indx_spr_bend_2 = 4;

    bn::sprite_tiles_ptr spr_tiles;
    bn::sprite_ptr sprite;

    STATE state;

    bn::unique_ptr<Timer> bend_stand_timer;

    int prev_mov_dir = 0;
    int moving_dir = 0;

    bn::fixed_rect movement_box;

    bool lab_coat = true;

    // Walking animation
    int walk_indx = 0;
    int walk_elapsed_frames = 0;
    static constexpr int wait_frames = 6;
    int walk_tile_indx[2] = {2,1};

    bool use_light_bathroom_day_4 = false;
    int curr_tiles = 0;
    int y_level = 16;

    bool fliped = false;
    bool wait_frame = false;

    void resetWalk();
    void updateWalk();

    void changeTiles(int tiles_start);

    uint32_t getLightRow(int spr,int x,int row);
    uint32_t getLightRow(int spr,bn::fixed_point row_start_pos);

    void updateLightBathroomDay4(); // Very specific i know
public:
    Player();

    void takeOffLabCoat();

    void resetAnim();

    void setPos(bn::fixed x, bn::fixed y);
    bn::fixed_point getPos();

    bn::sprite_tiles_ptr getTilesItem();
    bool getHorizontalFlip();

    bn::sprite_palette_ptr getPalettePtr();
    void useNightColors(bool use_night);

    bn::fixed_rect boundaries();

    bool hasNormalState();
    bool isBended();
    void bend();
    void standUp();

    void setMovementBox(bn::fixed_rect _movement_box);
    bn::fixed_rect movementBox();

    void setVisible(bool _visible);

    void setHflip(bool flip);

    void setUseLightBathroomDay4(bool use);

    void update(bool frozen = false);
};
}


#endif