#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "bn_fixed_point.h"
#include "bn_keypad.h"
#include "bn_log.h"

namespace game{
template <typename T>
class Moveable{
private:
    T& object;

public:
    Moveable(T& _object):object(_object){};
    ~Moveable() = default;

    void update(){
        if(bn::keypad::left_pressed()){
            object.set_position(object.position()+bn::fixed_point(-1,0));
        }
        if(bn::keypad::right_pressed()){
            object.set_position(object.position()+bn::fixed_point(1,0));
        }
        if(bn::keypad::up_pressed()){
            object.set_position(object.position()+bn::fixed_point(0,-1));
        }
        if(bn::keypad::down_pressed()){
            object.set_position(object.position()+bn::fixed_point(0,1));
        }
        if(bn::keypad::start_pressed()){
            BN_LOG("------------------");
            BN_LOG("Moveable object pos:",object.position().x(),",",object.position().y());
            BN_LOG("------------------");
        }
    }
};
}
#endif