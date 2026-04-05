#ifndef HOUSEBEDROOM2_H
#define HOUSEDEBROOM2_H

#include "bn_sprite_ptr.h"

#include "npc.h"
#include "room.h"
#include "moveable.h"
#include "globalVariables.h"

namespace game{
class HouseBedroom2 : public Room{
private:
    GlobalVariables& global_var;

    NPC molly;
    bn::sprite_ptr teddy_bear;

    void loadDay1();
    void loadDay2();
public:
    HouseBedroom2(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseBedroom2() override {}

    bn::optional<RoomExit> update() override;
};
}
#endif