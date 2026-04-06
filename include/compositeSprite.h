#ifndef COMPOSITESPRITE_H
#define COMPOSITESPRITE_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_palette_ptr.h"

#include "bn_math.h"
#include "bn_vector.h"
#include "bn_optional.h"
#include "bn_value_template_actions.h"

namespace game{
class CompositeSprite{
private:
    bn::fixed_point pos;
    bn::fixed rotation;
    bn::vector<bn::sprite_ptr,10> sprites; 
    bn::vector<bn::fixed_point,10> origOffset;

public:
    CompositeSprite();

    void addSprite(bn::sprite_ptr _sprite);

    void set_position(bn::fixed_point _pos);
    bn::fixed_point position() const;

    void setRotation(bn::fixed _rotation);
    bn::fixed rotationAngle() const;

    bn::optional<bn::sprite_palette_ptr> palette();
};

class CompositeSpritePosManager{
public:
    [[nodiscard]] static bn::fixed_point get(const CompositeSprite& sprite) {return sprite.position();}
    static void set(bn::fixed_point _pos,CompositeSprite& sprite) {sprite.set_position(_pos);}
};

class CompositeSpritePosToAction : public bn::to_value_template_action<CompositeSprite,bn::fixed_point, CompositeSpritePosManager>{
public:
    CompositeSpritePosToAction(const CompositeSprite& cmbSprite,int duration_updates,const bn::fixed_point& final_pos):
        bn::to_value_template_action<CompositeSprite,bn::fixed_point, CompositeSpritePosManager>(cmbSprite,duration_updates,final_pos){}
};

class CompositeSpriteRotManager{
public:
    [[nodiscard]] static bn::fixed get(const CompositeSprite& sprite) {return sprite.rotationAngle();}
    static void set(bn::fixed _rot, CompositeSprite& sprite) {sprite.setRotation(_rot);}
};

class CompositeSpriteRotToAction : public bn::to_value_template_action<CompositeSprite,bn::fixed, CompositeSpriteRotManager>{
public:
    CompositeSpriteRotToAction(const CompositeSprite& cmbSprite,int duration_updates,const bn::fixed& final_rot):
        bn::to_value_template_action<CompositeSprite,bn::fixed, CompositeSpriteRotManager>(cmbSprite,duration_updates,final_rot){}
};

}

#endif 