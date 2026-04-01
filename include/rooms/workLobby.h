#ifndef WORKLOBBY_H
#define WORKLOBBY_H

#include "bn_regular_bg_items_bg_work_lobby.h"

#include "bn_sprite_items_work_people.h"

#include "bn_vector.h"

#include "room.h"
#include "npc.h"
#include "globalVariables.h"

namespace game{
class WorkLobby : public Room{
private:
    bn::vector<NPC,10> npcs;
public:
    WorkLobby(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~WorkLobby() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif