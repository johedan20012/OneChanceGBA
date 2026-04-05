#ifndef HOUSEBATHROOM_H
#define HOUSEBATHROOM_H

#include "bn_sprite_items_penny_bathtub.h"

#include "bn_regular_bg_items_bg_house_4.h"

#include "bn_optional.h"

#include "room.h"
#include "npc.h"
#include "globalVariables.h"
#include "moveable.h"

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