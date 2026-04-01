#ifndef WORKHALL_H
#define WORKHALL_H

#include "bn_regular_bg_items_bg_work_hall.h"

#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_walking_dude.h"
#include "bn_sprite_actions.h"

#include "room.h"
#include "npc.h"
#include "globalVariables.h"

namespace game{
class WorkHall : public Room{
private:
    NPC npcs[2];
    bn::sprite_ptr walking_dude;
    bn::optional<bn::sprite_move_to_action> walk_mov;
    bn::optional<bn::sprite_animate_action<2>> walk_anim;

public:
    WorkHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~WorkHall() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif