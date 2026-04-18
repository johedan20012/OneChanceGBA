#ifndef WORKLABDOOR_H
#define WORKLABDOOR_H

#include "bn_sprite_actions.h"

#include "bn_optional.h"

#include "npc.h"
#include "room.h"
#include "globalVariables.h"

namespace game{
class WorkLabDoor : public Room{
private:
    GlobalVariables& global_var;

    bn::optional<NPC> npc;
    bool is_door_locked = false;

    bn::optional<bn::sprite_ptr> walking_dude;
    bn::optional<bn::sprite_move_to_action> walk_mov;
    bn::optional<bn::sprite_animate_action<2>> walk_anim;

    void loadDay1();
    void loadDay2(DIRECTION entering_from);
    void loadDay3();
public:
    WorkLabDoor(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~WorkLabDoor() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif