#ifndef HOUSEBEDROOM2_H
#define HOUSEDEBROOM2_H

#include "bn_regular_bg_items_bg_house_3.h"
#include "bn_regular_bg_items_bg_paper_3.h"

#include "room.h"

namespace game{
class HouseBedroom2 : public Room{
public:
    HouseBedroom2(Player& _player,DIRECTION entering_from);
    virtual ~HouseBedroom2() override;

    bn::optional<RoomExit> update() override;
};
}
#endif