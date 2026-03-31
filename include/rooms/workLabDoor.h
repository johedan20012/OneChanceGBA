#ifndef WORKLABDOOR_H
#define WORKLABDOOR_H

#include "bn_regular_bg_items_bg_work_lab_door.h"

#include "bn_sprite_items_work_people.h"

#include "room.h"
#include "npc.h"

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