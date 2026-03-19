#ifndef NPC_H
#define NPC_H

#include "bn_sprite_ptr.h"

namespace game{
class NPC{
protected:
    bn::sprite_ptr sprite;

public:
    NPC(bn::sprite_ptr _sprite);
    virtual ~NPC();

    void lookAt(bn::fixed_point p,bool flip = false);
    virtual void update();
};

}


#endif