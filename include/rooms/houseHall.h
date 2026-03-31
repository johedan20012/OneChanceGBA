#ifndef HOUSEHALL_H
#define HOUSEHALL_H

#include "bn_regular_bg_items_bg_house_2.h"

#include "bn_sprite_items_penny.h"

#include "room.h"
#include "npc.h"
#include "globalVariables.h"
#include "dialogTrigger.h"

namespace game{
class HouseHall : public Room{
private:
    NPC penny;    

    GlobalVariables& global_var;
public:
    HouseHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseHall() override {}

    bn::optional<RoomExit> update() override;
};

}

#endif