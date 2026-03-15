#include "npc.h"

namespace game{
NPC::NPC(bn::sprite_ptr _sprite):
    sprite(_sprite){
    sprite.set_bg_priority(2);
    sprite.set_z_order(2);
}

NPC::~NPC(){}

void NPC::lookAt(bn::fixed_point p){
    bn::fixed x_dif = sprite.position().x()-p.x();
    if(x_dif >= 0) sprite.set_horizontal_flip(true);
    else sprite.set_horizontal_flip(false);
}

void NPC::update(){}

}