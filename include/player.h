#ifndef PLAYER_H
#define PLAYER_H

#include "bn_keypad.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_character.h"

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

    bn::sprite_ptr sprite;
    bn::sprite_animate_action<2> walking;

    STATE state;

    bn::unique_ptr<Timer> bend_stand_timer;

    int prev_mov_dir = 0;
    int moving_dir = 0;

    bn::fixed_rect movement_box;
public:
    Player();

    void resetAnim();

    void setPos(bn::fixed x, bn::fixed y);
    bn::fixed_point getPos();

    bn::sprite_tiles_ptr getTilesItem();
    bool getHorizontalFlip();

    bn::fixed_rect boundaries();

    bool hasNormalState();
    bool isBended();
    void bend();
    void standUp();

    void setMovementBox(bn::fixed_rect _movement_box);
    bn::fixed_rect movementBox();

    void setVisible(bool _visible);

    void setHflip(bool flip);

    void update();
};
}


#endif