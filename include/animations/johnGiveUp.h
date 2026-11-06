#ifndef JOHNGIVEUP_H
#define JOHNGIVEUP_H

#include "bn_sprite_ptr.h"

#include "bn_unique_ptr.h"

#include "timer.h"
#include "animationFromData.h"
#include "giveup_animation_bin.h"

namespace game{
class JohnGiveUp : public AnimationFromData<ROMDataAccess,32,1>{
private:
    static constexpr bn::fixed_point JUMP_SIGN_OFFSET = {2,-35};

    bn::sprite_ptr john;
    bn::sprite_ptr jump_sign;

    bool waiting_confirmation = false;
public:
    JohnGiveUp(bn::fixed_point john_pos);
    ~JohnGiveUp() = default;

    void update() override;
};
}
#endif