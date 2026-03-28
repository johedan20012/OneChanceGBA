#ifndef HOUSEBEDROOM2_H
#define HOUSEDEBROOM2_H

#include "bn_regular_bg_items_bg_house_3.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_molly.h"
#include "bn_sprite_items_teddy.h"

#include "npc.h"
#include "room.h"
#include "globalVariables.h"
#include "moveable.h"

namespace game{
class HouseBedroom2 : public Room{
private:
    GlobalVariables& global_var;

    NPC molly;
    bn::sprite_ptr teddy_bear;
public:
    HouseBedroom2(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    virtual ~HouseBedroom2() override;

    bn::optional<RoomExit> update() override;
};
}
#endif