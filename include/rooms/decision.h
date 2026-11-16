#ifndef DECISION_H
#define DECISION_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "bn_regular_bg_ptr.h"

#include "bn_vector.h"

#include "room.h"
#include "globalVariables.h"

namespace game{
class Decision : public Room{
private:
    GlobalVariables &global_var;
    bn::regular_bg_ptr black_overlay;

    bn::vector<bn::sprite_ptr,20> text_sprs;
    bn::sprite_text_generator label_gen;

    bn::sprite_ptr selector;
    int selection = 0;

public:
    Decision(Player& _player,GlobalVariables& _global_var);
    ~Decision();

    bn::optional<RoomExit> update() override;
};
}
#endif