#include "city.h"

namespace game{
City::City(Player& _player, DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_city.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
    small_npc{bn::sprite_items::city_people.create_sprite(4,33,3),bn::sprite_items::city_people.create_sprite(-100,0,7),bn::sprite_items::city_people.create_sprite(93,0,5),
    bn::sprite_items::city_people.create_sprite(15,0,4),bn::sprite_items::city_people.create_sprite(-110,0,6),bn::sprite_items::city_people.create_sprite(124,40,1),
    bn::sprite_items::city_people.create_sprite(78,41,0),bn::sprite_items::city_people.create_sprite(-36,42,2)},  // 0, + 74, +59 for cars pos 
    npc_cars{bn::sprite_items::car_small.create_sprite(148,56),bn::sprite_items::car_small.create_sprite(222,56),bn::sprite_items::car_small.create_sprite(-55,56)},
    car(bn::sprite_items::car_small.create_sprite(0,0)){

    npc_cars[0].set_palette(bn::sprite_palette_item(pal1,bn::bpp_mode::BPP_4));
    npc_cars[0].set_horizontal_flip(true);
    npc_cars[1].set_palette(bn::sprite_palette_item(pal2,bn::bpp_mode::BPP_4));
    npc_cars[1].set_horizontal_flip(true);
    npc_cars[2].set_palette(bn::sprite_palette_item(pal2,bn::bpp_mode::BPP_4));
    npc_cars[2].set_horizontal_flip(true);

    player.setVisible(false);
    player.setMovementBox(bn::fixed_rect(0,0,280,160));
    
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
}

bn::optional<RoomExit> City::update(){
    for(auto& npc_car: npc_cars){
        npc_car.set_x(npc_car.x()-0.70);
        if(npc_car.x() < -168) npc_car.set_x(168);
    }

    for(int i = 0; i<8; i++){
        auto& lil_npc = small_npc[i];
        lil_npc.set_x(lil_npc.x() + dir_npc[i]);
        if(dir_npc[i] > 0 && lil_npc.x() > 130) lil_npc.set_x(-130);
        if(dir_npc[i] < 0  && lil_npc.x() < -130) lil_npc.set_x(130);
        lil_npc.set_y(y_level_npc[i][y_level_indx]);
    }
    y_level_indx = (y_level_indx+1)%8;

    if(bn::keypad::right_held()){
        car.set_position(car.position().x()+1,car.position().y());
        player.setPos(player.getPos().x()+1,player.getPos().y());
    }

    if(bn::keypad::start_pressed()){
        BN_LOG("0:",small_npc[0].x(),"|",small_npc[0].y());
        BN_LOG("4:",small_npc[4].x(),"|",small_npc[4].y());
    }

    
    Room::update();

    auto exit = checkExits();
    if(exit){
        player.setVisible(true);
    }
    return exit;
}
}