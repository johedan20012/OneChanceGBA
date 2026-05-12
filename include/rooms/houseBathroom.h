#ifndef HOUSEBATHROOM_H
#define HOUSEBATHROOM_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_palettes_actions.h"

#include "bn_bg_palettes_actions.h"

#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_unique_ptr.h"

#include "npc.h"
#include "room.h"
#include "timer.h"
#include "globalVariables.h"

namespace game{
class HouseBathroom : public Room{
private:
    GlobalVariables& global_var;

    bn::unique_ptr<NPC> penny;
    bn::optional<bn::sprite_ptr> coat;

    bn::unique_ptr<Timer> timer;
    bn::unique_ptr<Timer> timer2;
    bn::optional<bn::bg_palettes_fade_to_action> bg_fade_to_black;
    bn::optional<bn::sprite_palettes_fade_to_action> spr_fade_to_black;
    bn::vector<bn::sprite_ptr,2> light_day4A;
    void loadDay2();
    void loadDay3();
    void loadDay4();
    void loadDay5();

    bn::optional<RoomExit> updateDay4();
public:
    HouseBathroom(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseBathroom();

    bn::optional<RoomExit> update() override;
};
}

#endif