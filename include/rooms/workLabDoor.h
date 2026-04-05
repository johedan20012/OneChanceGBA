#ifndef WORKLABDOOR_H
#define WORKLABDOOR_H

#include "npc.h"
#include "room.h"

namespace game{
class WorkLabDoor : public Room{
private:
    NPC npc;
public:
    WorkLabDoor(Player& _player,DIRECTION entering_from);
    ~WorkLabDoor() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif