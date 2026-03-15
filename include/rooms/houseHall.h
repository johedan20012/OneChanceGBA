#ifndef HOUSEHALL_H
#define HOUSEHALL_H

#include "bn_regular_bg_items_bg_house_2.h"
#include "bn_regular_bg_items_bg_paper_2.h"

#include "bn_sprite_items_penny.h"

#include "room.h"
#include "npc.h"

namespace game{
class HouseHall : public Room{
private:
    NPC penny;    

public:
    HouseHall(Player& _player,DIRECTION entering_from);
    virtual ~HouseHall() override;

    void update() override;
};

}

#endif