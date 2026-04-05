#ifndef HOUSEHALL_H
#define HOUSEHALL_H

#include "npc.h"
#include "room.h"
#include "dialogTrigger.h"
#include "globalVariables.h"

namespace game{
class HouseHall : public Room{
private:
    GlobalVariables& global_var;
    
    NPC penny;    

    void loadDay1(DIRECTION entering_from);
    void loadDay2(DIRECTION entering_from);
public:
    HouseHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseHall() override {}

    bn::optional<RoomExit> update() override;
};

}

#endif