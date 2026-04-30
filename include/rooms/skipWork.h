#ifndef SKIPWORK_H
#define SKIPWORK_H

#include "bn_sprite_ptr.h"

#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_unique_ptr.h"

#include "room.h"
#include "timer.h"
#include "compositeSprite.h"
#include "globalVariables.h"

namespace game{
class SkipWork : public Room{
private:
    GlobalVariables& global_var;
    
    bn::vector<bn::sprite_ptr,4> people;
    bn::optional<CompositeSprite> car;
    int frames_anim_car = 0;

    bn::unique_ptr<Timer> initial_dark; // 1seg  / 60frames
    bn::unique_ptr<Timer>  end_room; // 5 seg, 30 frames / 330frames

    void loadDay1();
    void loadDay4();

    bn::optional<RoomExit> updateDay1();
    bn::optional<RoomExit> updateDay4();

    void setVisibility(bool visible);
public:
    SkipWork(Player& _player,GlobalVariables& _global_var);
    ~SkipWork() override = default;

    bn::optional<RoomExit> update() override;
};
}

#endif