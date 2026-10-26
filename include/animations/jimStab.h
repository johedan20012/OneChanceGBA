#ifndef JIMSTAB_H
#define JIMSTAB_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_palette_ptr.h"

#include "bn_point.h"
#include "bn_array.h"
#include "bn_unique_ptr.h"

#include "timer.h"
#include "animation.h"

namespace game{
class JimStab : public Animation{
private:
    static constexpr int BLOOD_PIXELS_ROWS = 6;
    static constexpr int BLOOD_PIXELS_COLUMNS = 31;
    static constexpr bn::fixed_point BLOOD_OFFSET = {7,6}; // Relative to John laying on the ground
    static const bn::point (&BLOOD_PUDDLE_PIXELS)[BLOOD_PIXELS_ROWS][BLOOD_PIXELS_COLUMNS];

    static constexpr bn::fixed_point JIM_OFFSETS[1] = {
        {-15,0} // Right in front of John
    };

    static constexpr bn::fixed_point JOHN_OFFSETS[2] = {
        {0,6}, // Relative to John's first position
        {2,16} // Relative to John's second position
    };

    static constexpr bn::fixed_point JOHN_EYES_OFFSET = {21,3};

    static constexpr bn::fixed_point KNIFE_OFFSETS[3] = {
        {-23,-6}, //270° Holding with right arm lifted and pointed towards Jim
        {0,6}, // Relative to it's first position with John
        {10,30} // Relative to it's first position with John
    };

    bn::sprite_ptr blood_puddle;
    bn::sprite_palette_ptr blood_puddle_palette;
    bn::sprite_ptr jim; 
    bn::sprite_ptr knife;
    bn::sprite_ptr john;
    bn::sprite_ptr john_eyes;
    bn::sprite_palette_ptr john_eyes_palette;

    Timer timer;
public:
    JimStab(bn::fixed_point jim_pos);
    ~JimStab() = default;

    void update() override;

    bool isFinished() override;
};

}

#endif