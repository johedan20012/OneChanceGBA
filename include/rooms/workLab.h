#ifndef WORKLAB_H
#define WORKLAB_H

#include "bn_sprite_ptr.h"

#include "bn_vector.h"
#include "bn_unique_ptr.h"

#include "npc.h"
#include "room.h"
#include "timer.h"
#include "globalVariables.h"

namespace game{
class WorkLab : public Room{
private:
    bn::unique_ptr<Timer> initial_dark; //0.9 seg, 54 frames
    bn::unique_ptr<Timer> end_room; // 3.1 seg, 186 frames

    bn::vector<NPC,3> npcs;
    bn::sprite_ptr pc_screen;

    GlobalVariables& global_var;

    int dark_frames = 54;
    int show_frames = 186;

    void setVisibility(bool visibility);
    void loadDay1_2();
    void loadDay3();
    void loadDay4();
public:
    WorkLab(Player& _player,GlobalVariables& _global_var);
    ~WorkLab() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif