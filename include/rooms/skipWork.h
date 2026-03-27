#ifndef SKIPWORK_H
#define SKIPWORK_H

#include "bn_regular_bg_items_bg_skip_work_1.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_work_people.h"

#include "room.h"
#include "timer.h"
#include "globalVariables.h"

namespace game{
class SkipWork : public Room{
private:
    bn::sprite_ptr people[4];

    Timer initial_dark; // 1seg  / 60frames
    Timer end_room; // 5 seg, 30 frames / 330frames

    GlobalVariables& global_var;

    void setVisibility(bool visible);
public:
    SkipWork(Player& _player,GlobalVariables& _global_var);
    ~SkipWork() override;

    bn::optional<RoomExit> update() override;
};
}

#endif