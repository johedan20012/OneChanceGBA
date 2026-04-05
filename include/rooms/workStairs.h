#ifndef WORKSTAIRS_H
#define WORKSTAIRS_H

#include "bn_sprite_palette_item.h"

#include "npc.h"
#include "room.h"

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