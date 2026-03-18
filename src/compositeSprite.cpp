#include "compositeSprite.h"

#include "bn_log.h"

namespace game{
CompositeSprite::CompositeSprite():
    pos(0,0){}

void CompositeSprite::addSprite(bn::sprite_ptr _sprite){
    _sprite.set_bg_priority(2);
    _sprite.set_z_order(2);
    sprites.push_back(_sprite);
    origOffset.push_back(_sprite.position()-pos);
    //distToCenter.push_back(bn::sqrt((_sprite.position().x()-pos.x())*(_sprite.position().x()-pos.x()) + (_sprite.position().y()-pos.y())*(_sprite.position().y()-pos.y())));
}

void CompositeSprite::setPos(bn::fixed_point _pos){
    bn::fixed_point delta = _pos - pos;
    for(auto sprite: sprites){
        sprite.set_position(sprite.position()+delta);
    }
    pos = _pos;
}

bn::fixed_point CompositeSprite::position() const{
    return pos;
}

void CompositeSprite::setRotation(bn::fixed _rotation){
    rotation = _rotation;
    
    // Calculate trig values once to avoid repeated calculations
    // Negate rotation to match clockwise sprite rotation direction
    bn::fixed neg_rotation = (-_rotation+720)%360;
    if(neg_rotation < 0) BN_LOG("LOLOO");
    bn::fixed cos_angle = bn::degrees_cos(neg_rotation);
    bn::fixed sin_angle = bn::degrees_sin(neg_rotation);
    
    // Use original offsets as reference to avoid accumulating precision errors
    for(int i = 0; i < sprites.size(); i++){
        bn::fixed_point offset = origOffset[i];
        
        // Rotate from original offset, not from current position
        bn::fixed rotated_x = offset.x() * cos_angle - offset.y() * sin_angle;
        bn::fixed rotated_y = offset.x() * sin_angle + offset.y() * cos_angle;
        
        sprites[i].set_position(pos + bn::fixed_point(rotated_x, rotated_y));
        sprites[i].set_rotation_angle((rotation+720)%360);
    }
}

bn::fixed CompositeSprite::rotationAngle() const{
    return rotation;
}
}