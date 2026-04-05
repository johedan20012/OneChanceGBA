#ifndef NPC_H
#define NPC_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_sprite_palette_item.h"

#include "bn_vector.h"
#include "bn_fixed_rect.h"
#include "bn_unique_ptr.h"

#include "pair.h"
#include "dialogTrigger.h"

namespace game{
class NPC{
protected:
    bn::sprite_ptr sprite;
    DialogTrigger* dialog;
public:
    NPC(bn::sprite_ptr _sprite);
    virtual ~NPC();

    void setZOrder(int order);

    void addDialog(DialogTrigger* _dialog); //eww raw pointers

    void lookAt(bn::fixed_point p,bool flip = false);
    void checkDialog(bn::fixed_rect player_boundaries);
    virtual void update();

    virtual void set_position(bn::fixed_point _pos);
    virtual bn::fixed_point position();

    void setVisibility(bool visibility);

    bn::sprite_palette_ptr getPalette();
};

}


#endif