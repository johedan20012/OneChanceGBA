#include "npc.h"

namespace game{
NPC::NPC(bn::sprite_ptr _sprite):
    sprite(_sprite),dialog(nullptr){
    sprite.set_bg_priority(2);
    sprite.set_z_order(2);
}

NPC::~NPC(){
    if(dialog != nullptr) delete dialog;
}

void NPC::addDialog(DialogTrigger* _dialog){
    dialog = _dialog;
    dialog->setPos(sprite.position()+dialog->getPos());
}

void NPC::lookAt(bn::fixed_point p, bool flip){
    bn::fixed x_dif = sprite.position().x()-p.x();
    if(x_dif >= 0) sprite.set_horizontal_flip(!flip);
    else sprite.set_horizontal_flip(flip);
}

void NPC::checkDialog(bn::fixed_rect player_boundaries){
    dialog->update(player_boundaries);
}

void NPC::update(){}

void NPC::setVisibility(bool visibility){
    sprite.set_visible(visibility);
}

bn::sprite_palette_ptr NPC::getPalette(){
    return sprite.palette();
}

}