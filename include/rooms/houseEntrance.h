#ifndef HOUSEENTRANCE_H
#define HOUSEENTRANCE_H

#include "bn_regular_bg_items_bg_house_5.h"

#include "room.h"

namespace game{
class HouseEntrance : public Room{
public:
    HouseEntrance(Player& _player, DIRECTION _entering_from);
    virtual ~HouseEntrance() override;

    void update() override;
};
}

#endif