#ifndef HOUSEHALL_H
#define HOUSEHALL_H

#include "bn_regular_bg_items_bg_house_2.h"
#include "bn_regular_bg_items_bg_paper_2.h"

#include "room.h"

namespace game{
class HouseHall : public Room{
public:
    HouseHall(Player& _player);
    virtual ~HouseHall() override;

    void update() override;
};

}

#endif