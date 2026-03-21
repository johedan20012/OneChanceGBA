#include "npc.h"

namespace game{
NPC::NPC(bn::sprite_ptr _sprite):
    sprite(_sprite){
    sprite.set_bg_priority(2);
    sprite.set_z_order(2);
}

NPC::~NPC(){}

void NPC::lookAt(bn::fixed_point p, bool flip){
    bn::fixed x_dif = sprite.position().x()-p.x();
    if(x_dif >= 0) sprite.set_horizontal_flip(!flip);
    else sprite.set_horizontal_flip(flip);
}

void NPC::update(){}

bn::sprite_palette_ptr NPC::getPalette(){
    return sprite.palette();
}

}