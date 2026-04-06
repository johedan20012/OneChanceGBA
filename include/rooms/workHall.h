#ifndef WORKHALL_H
#define WORKHALL_H

#include "bn_sprite_actions.h"

#include "bn_optional.h"

#include "npc.h"
#include "room.h"
#include "globalVariables.h"

namespace game{
class WorkHall : public Room{
private:
    GlobalVariables& global_var;

    NPC npcs[2];
    bn::optional<NPC> extra_npc;

    bn::optional<bn::sprite_ptr> walking_dude;
    bn::optional<bn::sprite_move_to_action> walk_mov;
    bn::optional<bn::sprite_animate_action<2>> walk_anim;

    void loadDay1(DIRECTION entering_from);
    void loadDay2();
public:
    WorkHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~WorkHall() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif