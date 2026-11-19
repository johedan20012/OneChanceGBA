#include "johnSitPark.h"

#include "bn_sprite_items_john_eyes.h"
#include "bn_sprite_items_character_day6.h"

#include "bn_log.h"

namespace game{
JohnSitPark::JohnSitPark(bn::fixed_point init_pos):
john_spr(bn::sprite_items::character_day6.create_sprite(init_pos)),
john_eyes(bn::sprite_items::john_eyes.create_sprite(init_pos)),
john_eyes_pal(john_eyes.palette()){
    john_spr.set_horizontal_flip(true);

    john_eyes.set_rotation_angle(270);
    john_eyes_pal.set_color(1,bn::color(0));
    john_eyes_pal.set_color(2,bn::color(0));
    john_eyes_pal.set_color(3,bn::color(0));
    john_eyes_pal.set_color(4,bn::color(0));
    john_eyes.set_visible(false);
}   

void JohnSitPark::update(){
    if(timer.elapsedFrames() == 34){
        john_spr.set_tiles(bn::sprite_items::character_day6.tiles_item(),1);
        john_spr.set_y(john_spr.y()-bn::fixed{6});
        john_eyes.set_position(john_spr.position() + bn::fixed_point{-4,-21});
        john_eyes.set_horizontal_flip(true);
    }

    if(timer.elapsedFrames() >= 810 && timer.elapsedFrames() <= 920 && (timer.elapsedFrames() - 810)%33 == 0){
        john_eyes.set_visible(true);
        int indx = ((timer.elapsedFrames() - 810)/33) +1;
        BN_ASSERT(indx >= 1 && indx <= 4, "Invalid indx for John eyes palette", indx);
        john_eyes_pal.set_color(indx,bn::color{25,22,18});
    }
}

bool JohnSitPark::isFinished(){
    return timer.elapsedFrames() >= 920;
}

}