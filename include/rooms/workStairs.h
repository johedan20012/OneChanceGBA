#ifndef WORKSTAIRS_H
#define WORKSTAIRS_H

#include "bn_regular_bg_items_bg_work_stairs.h"

#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_construction_guy.h"

#include "bn_sprite_palette_item.h"

#include "room.h"
#include "npc.h"

namespace game{
class WorkStairs : public Room{
private:
    NPC npcs[2];

public:
    WorkStairs(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~WorkStairs() override {}

    bn::optional<RoomExit> update() override;
};
}


#endif