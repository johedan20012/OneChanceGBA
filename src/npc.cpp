#include "npc.h"

namespace game{
NPC::NPC(bn::sprite_ptr _sprite):
    sprite(_sprite),dialog(nullptr){
    sprite.set_bg_priority(2);
    sprite.set_z_order(2);
}

NPC::~NPC(){
    if(dialog != nullptr){
        delete dialog;
        dialog = nullptr;
    }
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

void NPC::set_position(bn::fixed_point _pos){
    bn::fixed_point diff(0,0);
    if(dialog != nullptr) diff = dialog->getPos() - sprite.position();    
    sprite.set_position(_pos);
    if(dialog != nullptr) dialog->setPos(_pos + diff);
}

bn::fixed_point NPC::position(){
    return sprite.position();
}

void NPC::setVisibility(bool visibility){
    sprite.set_visible(visibility);
}

bn::sprite_palette_ptr NPC::getPalette(){
    return sprite.palette();
}

}