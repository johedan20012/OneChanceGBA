#ifndef HOUSEBEDROOM2_H
#define HOUSEDEBROOM2_H

#include "bn_sprite_ptr.h"

#include "bn_unique_ptr.h"

#include "npc.h"
#include "room.h"
#include "timer.h"
#include "globalVariables.h"

namespace game{
class HouseBedroom2 : public Room{
private:
    GlobalVariables& global_var;

    NPC molly;
    bn::sprite_ptr teddy_bear;

    bool showing_go_home_option = false;
    bn::unique_ptr<Timer> timer;

    void loadDay1();
    void loadDay2();
    void loadDay3();
    void loadDay4();
    void loadDay5();

    bn::optional<RoomExit> updateDay3_4A();
public:
    HouseBedroom2(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseBedroom2() override {}

    bn::optional<RoomExit> update() override;
};
}
#endif