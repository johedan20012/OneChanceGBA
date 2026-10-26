#ifndef MOVEABLECOLLECTION_H
#define MOVEABLECOLLECTION_H

#include "bn_log.h"
#include "bn_array.h"
#include "bn_assert.h"
#include "bn_keypad.h"
#include "bn_unique_ptr.h"

#include "moveable.h"

namespace game{
template <typename T,int MAX_SIZE>
class MoveableCollection{
private:
    bn::array<bn::unique_ptr<Moveable<T>>,MAX_SIZE> objects;
    int num_objects = 0;
    bool rotation_mode = false;
    bn::fixed rotation = {0};
    int indx = 0;
public: 
    MoveableCollection() = default;

    void addElement(T& object){
        BN_ASSERT(num_objects < MAX_SIZE,"Can't put more elements into the moveable collection");
        objects[num_objects++] = bn::make_unique<Moveable<T>>(object);
    }

    void update(){
        if(num_objects == 0) return;

        if(bn::keypad::l_held() || bn::keypad::r_held()) return;

        if(bn::keypad::select_pressed()){
            indx = (indx+1)%num_objects;
            BN_LOG("Moveable object indx:",indx);
        }

        if(bn::keypad::start_pressed()){
            BN_LOG("-----");
            BN_LOG("Mov obj rotation:",rotation);
            BN_LOG("-----");
        }

        if(bn::keypad::b_pressed()){
            rotation_mode = !rotation_mode;
            if(rotation_mode) rotation = objects[indx]->get().rotation_angle();
        }

        if(objects[indx]){
            if(rotation_mode && bn::keypad::up_pressed()){
                rotation = (rotation+bn::fixed(5))%360;
                objects[indx]->get().set_rotation_angle(rotation);
            }else if(rotation_mode && bn::keypad::down_pressed()){
                rotation -= bn::fixed(5);
                if(rotation < bn::fixed(0)) rotation += bn::fixed(360);
                objects[indx]->get().set_rotation_angle(rotation);
            }
            else if(!rotation_mode) objects[indx]->update();
        }else BN_LOG("LOL");
    }
};
}

#endif