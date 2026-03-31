#ifndef HOUSEBATHROOM_H
#define HOUSEBATHROOM_H

#include "bn_regular_bg_items_bg_house_4.h"

#include "room.h"

namespace game{
class HouseBathroom : public Room{
public:
    HouseBathroom(Player& _player,DIRECTION entering_from);
    ~HouseBathroom() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif