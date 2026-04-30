#ifndef DAYCHANGE_H
#define DAYCHANGE_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_palette_actions.h"

#include "bn_vector.h"
#include "bn_unique_ptr.h"

#include "room.h"
#include "timer.h"
#include "globalVariables.h"

#define DARK_FRAMES 60
#define BRIGHT_FRAMES 90
#define LAST_DARK_FRAMES 15

namespace game{
class DayChange : public Room{
private:
    enum STATE{
        DARK,
        LIGHT_TOP,
        HOLD_LIGHT,
        HOLD_DARK,
    };

    const bn::color palette1[16] = {bn::color(0,0,0),bn::color(31,31,31),bn::color(0,31,0)};
    const bn::color palette2[16] = {bn::color(0,0,0),bn::color(31,31,31),bn::color(31,0,0)};
    bn::vector<bn::sprite_ptr,30> text;
    bn::optional<bn::sprite_palette_ptr> pal1;
    bn::optional<bn::sprite_palette_ptr> pal2;
    bn::unique_ptr<bn::sprite_palette_fade_to_action> pal1_fade;
    bn::unique_ptr<bn::sprite_palette_fade_to_action> pal2_fade;

    bn::unique_ptr<Timer> timer;
    STATE state = STATE::DARK;

    GlobalVariables& global_var;
public:
    DayChange(Player& _player,GlobalVariables& _global_var);
    ~DayChange() override;

    bn::optional<RoomExit> update() override;
};
}

#endif