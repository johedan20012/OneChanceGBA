#ifndef WORKLAB_H
#define WORKLAB_H

#include "bn_regular_bg_items_bg_work_lab.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_pc_screen.h"

#include "timer.h"
#include "room.h"
#include "npc.h"
#include "globalVariables.h"

namespace game{
class WorkLab : public Room{
private:
    Timer initial_dark; //0.9 seg, 54 frames
    Timer end_room; // 3.1 seg, 186 frames

    NPC npcs[2];
    bn::sprite_ptr pc_screen;

    GlobalVariables& global_var;

    void setVisibility(bool visibility);
public:
    WorkLab(Player& _player,GlobalVariables& _global_var);
    ~WorkLab() override;

    bn::optional<RoomExit> update() override;
};
}

#endif