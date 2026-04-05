#ifndef HOUSEBATHROOM_H
#define HOUSEBATHROOM_H

#include "bn_optional.h"

#include "npc.h"
#include "room.h"
#include "globalVariables.h"

namespace game{
class HouseBathroom : public Room{
private:
    GlobalVariables& global_var;

    bn::unique_ptr<NPC> penny;

    void loadDay2();
public:
    HouseBathroom(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseBathroom() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif