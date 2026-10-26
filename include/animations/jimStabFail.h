#ifndef JIMSTABFAIL_H
#define JIMSTABFAIL_H

#include "bn_sprite_ptr.h"

#include "bn_unique_ptr.h"

#include "timer.h"
#include "animationFromData.h"
#include "moveableCollection.h"

namespace game{
class JimStabFail : public AnimationFromData<15,5>{
private:
    static constexpr bn::fixed_point JOHN_OFFSETS[1] = {
        bn::fixed_point(-41,5), // Relative to Jim's first position
    };

    static constexpr bn::fixed_point JOHNS_ARM_OFFSETS[2] = {
       {-6,-7}, // Relative to John's first position
       {4,-9} // Relative to John's last position
    };

    static constexpr bn::fixed_point JIMS_ARM_OFFSET = {8,-5};

    static constexpr bn::fixed_point KNIFE_OFFSETS[2] = {
        {-22,-6}, //270° Holding with right arm lifted and pointed towards John
        {1,17} // Relative to John's last position
    };

    bn::sprite_ptr john;
    bn::sprite_ptr johns_arm;
    bn::sprite_ptr jim; 
    bn::sprite_ptr jims_arm;
    bn::sprite_ptr knife;

    MoveableCollection<bn::sprite_ptr,5> mov;

    Timer timer;
public:
    JimStabFail(bn::fixed_point jim_pos);
    ~JimStabFail() = default;

    void update() override;

    bool isFinished() override;
};

}

#endif