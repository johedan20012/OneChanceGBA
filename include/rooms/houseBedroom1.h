#ifndef HOUSEBEDROOM1_H
#define HOUSEBEDROOM1_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_palettes_actions.h"

#include "bn_bg_palettes_actions.h"

#include "bn_color.h"
#include "bn_optional.h"

#include "npc.h"
#include "room.h"
#include "globalVariables.h"

#ifdef DEBUG_GAME
#include "bn_unique_ptr.h"
#include "moveable.h"
#endif

namespace game{
class HouseBedroom1 : public Room{
private:
    static constexpr bn::color penny_dark_pal[16] = {
        bn::color(0,0,0),bn::color(0,0,0),
        bn::color(11,9,6),bn::color(12,5,1),bn::color(11,1,3),
        bn::color(7,0,2),bn::color(7,4,3)
    };

    GlobalVariables& global_var;
    bn::sprite_ptr player_reflexion;

    bn::sprite_ptr white_lab_coat;
    bn::optional<bn::sprite_ptr> white_lab_coat2;
    bn::optional<NPC> penny;

    bn::optional<bn::bg_palettes_fade_to_action> bg_fade_to_black;
    bn::optional<bn::sprite_palettes_fade_to_action> spr_fade_to_black;
    bool day4ADialogStarted = false;

    #ifdef DEBUG_GAME
    bn::unique_ptr<Moveable<NPC>> mov;
    #endif

    void loadDay1();
    void loadDay2();
    void loadDay3();
    void loadDay4();
public:
    HouseBedroom1(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~HouseBedroom1() override {}

    bn::optional<RoomExit> update() override;
};
}
#endif