#include "city.h"

#include "bn_regular_bg_items_bg_city.h"

#include "bn_sprite_items_sign.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_sprite_items_car_small.h"
#include "bn_sprite_items_city_people.h"

#include "bn_log.h"

namespace game{
City::City(Player& _player, DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_city.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
    global_var(_global_var),
    car(bn::sprite_items::car_small.create_sprite(0,0)){

    player.setVisible(false);
    player.setMovementBox(bn::fixed_rect(0,0,280,160));
    
    car.set_z_order(-1);
    switch (entering_from){
    case DIRECTION::LEFT:
        car.set_position(bn::fixed_point(-97,67));
        player.setPos(-97,67);
        break;    
    default:
        car.set_position(bn::fixed_point(0,0));
        player.setPos(0,0);
        break;
    }

    exits.push_back(RoomExit("work_parking",bn::fixed_rect(160,20,10,64),DIRECTION::LEFT,false));

    switch (global_var.currentDay()){
    case 3:
        loadDay3();
        break;
    case 2:
    default: // Day 1
        loadDay1_2();
        break;
    }
}

void City::loadDay1_2(){
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(4,33,3));
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(-100,0,7));
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(93,0,5));
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(15,0,4));
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(-110,0,6));
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(124,40,1));
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(78,41,0));
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(-36,42,2));

    // 0, + 74, +59 for cars pos  
    npc_cars.push_back(bn::sprite_items::car_small.create_sprite(148,56));
    npc_cars.push_back(bn::sprite_items::car_small.create_sprite(222,56));
    npc_cars.push_back(bn::sprite_items::car_small.create_sprite(-55,56));

    npc_cars[0].set_palette(bn::sprite_palette_item(pal1,bn::bpp_mode::BPP_4));
    npc_cars[0].set_horizontal_flip(true);
    npc_cars[1].set_palette(bn::sprite_palette_item(pal2,bn::bpp_mode::BPP_4));
    npc_cars[1].set_horizontal_flip(true);
    npc_cars[2].set_palette(bn::sprite_palette_item(pal2,bn::bpp_mode::BPP_4));
    npc_cars[2].set_horizontal_flip(true);
}

void City::loadDay3(){
    // Wow a lot of text (mucho texto)
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(-71,33,4)); //Goes left
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-92,33,7));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(5,34,1)); // this has a sign
    npc_signs.push_back(bn::sprite_items::sign.create_sprite(9,33));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-85,35,6));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-47,35,2));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(50,35,1));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(96,38,1));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-14,38,0)); // this has a sign
    npc_signs.push_back(bn::sprite_items::sign.create_sprite(-10,37));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-25,38,3));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-37,39,5));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-57,39,7));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-4,40,4));
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(16,40,7)); //Goes left
    small_npc.push_back(bn::sprite_items::city_people.create_sprite(-100,41,6)); //Goes right
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(43,41,4));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-49,41,6)); // this has a sign
    npc_signs.push_back(bn::sprite_items::sign.create_sprite(-45,40));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(79,41,0));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(59,42,3));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(-17,42,1));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(24,43,3));// this has a sign
    npc_signs.push_back(bn::sprite_items::sign.create_sprite(28,42));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(89,44,4));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(7,44,6));
    small_npc_nmov.push_back(bn::sprite_items::city_people.create_sprite(76,45,1));// this has a sign
    npc_signs.push_back(bn::sprite_items::sign.create_sprite(80,44));
    // 0, + 74, +59 for cars pos  
    npc_cars.push_back(bn::sprite_items::car_small.create_sprite(148,56));
    npc_cars.push_back(bn::sprite_items::car_small.create_sprite(-55,56));

    npc_cars[0].set_palette(bn::sprite_palette_item(pal1,bn::bpp_mode::BPP_4));
    npc_cars[0].set_horizontal_flip(true);
    npc_cars[1].set_palette(bn::sprite_palette_item(pal2,bn::bpp_mode::BPP_4));
    npc_cars[1].set_horizontal_flip(true);
}

void City::updateDay1_2(){
    for(int i = 0; i<8; i++){
        auto& lil_npc = small_npc[i];
        lil_npc.set_x(lil_npc.x() + dir_npc[i]);
        if(dir_npc[i] > 0 && lil_npc.x() > 130) lil_npc.set_x(-130);
        if(dir_npc[i] < 0  && lil_npc.x() < -130) lil_npc.set_x(130);
        lil_npc.set_y(y_level_npc[i][y_level_indx]);
    }
}

void City::updateDay3(){
    bn::fixed y_diff = 0;
    if(y_level_indx % 8 == 0) y_diff = 1;
    if(y_level_indx % 8 == 4) y_diff = -1;
    if(y_diff != 0){
        for(auto& npc: small_npc_nmov){
            npc.set_y(npc.y()+ y_diff);
        }
        for(auto& npc: small_npc){
            npc.set_y(npc.y()+ y_diff);
        }
    }

    small_npc[0].set_x(small_npc[0].x() - 0.7);
    if(small_npc[0].x() <= -130) small_npc[0].set_x(130);
    small_npc[1].set_x(small_npc[1].x() - 0.7);
    if(small_npc[1].x() <= -130) small_npc[1].set_x(130);
    if(small_npc.size() > 2){
        small_npc[2].set_x(small_npc[2].x() + 0.7);
        if(small_npc[2].x() > 140.0) small_npc.pop_back();
    }
}

bn::optional<RoomExit> City::update(){
    for(auto& npc_car: npc_cars){
        npc_car.set_x(npc_car.x()-0.70);
        if(npc_car.x() < -168) npc_car.set_x(168);
    }

    if(bn::keypad::right_held()){
        car.set_position(car.position().x()+1,car.position().y());
        player.setPos(player.getPos().x()+1,player.getPos().y());
    }
    
    Room::update();    

    switch (global_var.currentDay()){
    case 3:
        updateDay3();
        break;
    case 2:
    default: // Day 1
        updateDay1_2();
        break;
    }

    y_level_indx = (y_level_indx+1)%8;
    bn::optional<RoomExit> exit = checkExits();
    if(exit){
        player.setVisible(true);
    }
    return exit;
}
}