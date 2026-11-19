#ifndef JOHNSITPARK_H
#define JOHNSITPARK_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_palette_ptr.h"

#include "timer.h"
#include "animation.h"

namespace game{
class JohnSitPark : public Animation{
private:
    Timer timer;

    bn::sprite_ptr john_spr;
    bn::sprite_ptr john_eyes;
    bn::sprite_palette_ptr john_eyes_pal;
public:
    JohnSitPark(bn::fixed_point init_pos);
    ~JohnSitPark() = default;

    void update() override;

    bool isFinished() override;
};
}
#endif