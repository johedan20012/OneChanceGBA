#ifndef HOUSEBEDROOM1_H
#define HOUSEBEDROOM1_H

#include "bn_sprite_ptr.h"

#include "room.h"
#include "moveable.h"
#include "globalVariables.h"

namespace game{
class HouseBedroom1 : public Room{
private:
    GlobalVariables& global_var;
    bn::sprite_ptr player_reflexion;

    bn::sprite_ptr white_lab_coat;

    void loadDay1();
    void loadDay2();

public:
    HouseBedroom1(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseBedroom1() override {}

    bn::optional<RoomExit> update() override;
};
}
#endif