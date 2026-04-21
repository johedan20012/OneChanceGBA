#ifndef HOUSEHALL_H
#define HOUSEHALL_H

#include "bn_sprite_ptr.h"

#include "bn_optional.h"

#include "npc.h"
#include "room.h"
#include "dialogTrigger.h"
#include "globalVariables.h"

namespace game{
class HouseHall : public Room{
private:
    GlobalVariables& global_var;
    
    bn::optional<NPC> npc; 
    bn::optional<bn::sprite_ptr> prop;  

    void loadDay1(DIRECTION entering_from);
    void loadDay2();
    void loadDay3();
    void loadDay4();
public:
    HouseHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseHall() override {}

    bn::optional<RoomExit> update() override;
};

}

#endif