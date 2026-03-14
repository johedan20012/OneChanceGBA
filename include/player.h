#ifndef PLAYER_H
#define PLAYER_H

#include "bn_keypad.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_character.h"

#include "bn_fixed_rect.h"

namespace game{
class Player{
private:
    bn::sprite_ptr sprite;
    bn::sprite_animate_action<2> walking;
public:
    Player();

    void setPos(bn::fixed x, bn::fixed y);
    bn::fixed_point getPos();

    bn::fixed_rect boundaries();

    void update();
};
}


#endif