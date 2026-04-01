#ifndef HOUSEBEDROOM1_H
#define HOUSEBEDROOM1_H

#include "bn_regular_bg_items_bg_house_1.h"

#include "bn_sprite_items_character.h"

#include "room.h"

namespace game{
class HouseBedroom1 : public Room{
private:
    bn::sprite_ptr player_reflexion;

public:
    HouseBedroom1(Player& _player,DIRECTION entering_from);
    ~HouseBedroom1() override {}

    bn::optional<RoomExit> update() override;
};
}
#endif