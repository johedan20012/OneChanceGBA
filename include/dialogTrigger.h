#ifndef DIALOGTRIGGER_H
#define DIALOGTRIGGER_H

#include "bn_fixed_rect.h"

#ifdef DEBUG_GAME
#include "bn_sprite_ptr.h"
#include "bn_sprite_items_debug_corner.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_vector.h"
#endif

#include "globalVariables.h"
#include "player.h"
#include "pair.h"

namespace game{
class DialogTrigger{
private:
    GlobalVariables& global_var;

    bn::fixed_rect trigger_box;
    bn::vector<Pair<int,int>,10> dialog_sequence;
    bool hold_until_leaving;
    bool is_reuseable;

    bool player_in = false;
    bool active = true;

    #ifdef DEBUG_GAME
    bn::vector<bn::sprite_ptr,5> trigger_debug;
    void createTriggerDebug();
    #endif
public:
    DialogTrigger(GlobalVariables& _global_var,bn::fixed_rect _box,bool _hold_til_leaving,bool _reusable = false);
    ~DialogTrigger() = default;

    void setPos(bn::fixed_point _pos);
    bn::fixed_point getPos();

    void addDialog(Pair<int,int> dialog);

    void update(bn::fixed_rect player_boundaries);
};
}
#endif