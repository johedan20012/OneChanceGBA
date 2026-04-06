#ifndef WORKLOBBY_H
#define WORKLOBBY_H

#include "bn_vector.h"

#include "npc.h"
#include "room.h"
#include "bn_unique_ptr.h"
#include "moveable.h"
#include "globalVariables.h"

namespace game{
class WorkLobby : public Room{
private:
    GlobalVariables& global_var;

    bn::vector<NPC,10> npcs;

    bn::unique_ptr<Moveable<NPC>> mov;

    void loadDay1();
    void loadDay2();
public:
    WorkLobby(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~WorkLobby() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif