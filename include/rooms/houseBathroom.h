#ifndef HOUSEBATHROOM_H
#define HOUSEBATHROOM_H

#include "bn_sprite_ptr.h"

#include "bn_vector.h"
#include "bn_optional.h"

#include "npc.h"
#include "room.h"
#include "globalVariables.h"

namespace game{
class HouseBathroom : public Room{
private:
    GlobalVariables& global_var;

    bn::unique_ptr<NPC> penny;
    bn::optional<bn::sprite_ptr> coat;

    bn::vector<bn::sprite_ptr,2> light_day4A;
    void loadDay2();
    void loadDay3();
    void loadDay4();
public:
    HouseBathroom(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseBathroom();

    bn::optional<RoomExit> update() override;
};
}

#endif