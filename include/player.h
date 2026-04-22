#ifndef PLAYER_H
#define PLAYER_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_animate_actions.h"

#include "bn_color.h"
#include "bn_keypad.h"
#include "bn_fixed_rect.h"
#include "bn_unique_ptr.h"

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

    static constexpr bn::color NIGHT_PAL[16] = {
        bn::color(0,12,0),bn::color(0,0,0),bn::color(1,1,2),
        bn::color(2,2,3),bn::color(5,3,2),bn::color(11,9,6),
        bn::color(5,6,6),bn::color(10,13,17),bn::color(27,27,27),
    };

    bn::sprite_ptr sprite;
    bn::sprite_animate_action<2> walking;

    STATE state;

    bn::unique_ptr<Timer> bend_stand_timer;

    int prev_mov_dir = 0;
    int moving_dir = 0;

    bn::fixed_rect movement_box;

    bool lab_coat = true;
public:
    Player();

    void takeOffLabCoat();

    void resetAnim();

    void setPos(bn::fixed x, bn::fixed y);
    bn::fixed_point getPos();

    bn::sprite_tiles_ptr getTilesItem();
    bool getHorizontalFlip();

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

    void update(bool frozen = false);
};
}


#endif