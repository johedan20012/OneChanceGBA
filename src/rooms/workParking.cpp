#include "workParking.h"

#include "bn_sprite_items_jim.h"
#include "bn_sprite_items_car.h"
#include "bn_sprite_palette_ptr.h"

#include "bn_regular_bg_items_bg_bottom_text.h"
#include "bn_regular_bg_items_bg_work_parking.h"

#include "bn_optional.h"

namespace game{
WorkParking::JimNPC::JimNPC():
    NPC(bn::sprite_items::jim.create_sprite(70,40,0)){}

void WorkParking::JimNPC::update(){
    switch(smoke.elapsedFrames()){
        case 150:
            sprite.set_tiles(bn::sprite_items::jim.tiles_item(),1);
            break;
        case 220:
            sprite.set_tiles(bn::sprite_items::jim.tiles_item(),0);
            smoke.restart();
            break;
        default:
            break;
    }
}

WorkParking::WorkParking(Player& _player,DIRECTION entering_from,GlobalVariables& _global):
    Room(bn::regular_bg_items::bg_work_parking.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
    global_var(_global),car1(){

    car1.addSprite(bn::sprite_items::car.create_sprite(-31,0,0));
    car1.addSprite(bn::sprite_items::car.create_sprite(0,0,1));
    car1.addSprite(bn::sprite_items::car.create_sprite(31,0,2));

    player.setMovementBox(bn::fixed_rect(10,0,240,160));

    auto& dialog_mgr = global_var.getDialogManager();
    dialog_mgr.setBg(bn::regular_bg_items::bg_bottom_text.create_bg(8,48));

    switch (entering_from){
        case DIRECTION::LEFT:
            player.setPos(-108,49);
            break;    
        default:
            player.setPos(0,0);
            break;
    }

    exits.push_back(RoomExit("work_lobby",bn::fixed_rect(123,20,10,64),DIRECTION::LEFT,false));

    switch (global_var.currentDay()){
        case 2:
            loadDay2();
            break;
        
        default:
            loadDay1();
            break;
    }
}

void WorkParking::loadDay1(){
    car1.set_position(bn::fixed_point(-5,57));

    bn::optional<bn::sprite_palette_ptr> car1_pal = car1.palette();
    if(car1_pal) car1_pal->set_color(3,bn::color(19,0,12));

    jim = bn::make_unique<JimNPC>();
    {
        DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,30,60),false);
        dialog->addDialog({3,90});
        jim->addDialog(dialog);
    }
}

void WorkParking::loadDay2(){
    car1.set_position(bn::fixed_point(-6,57));

    bn::optional<bn::sprite_palette_ptr> car1_pal = car1.palette();
    if(car1_pal) car1_pal->set_color(3,bn::color(23,26,7));

    bn::sprite_palette_ptr new_pal = bn::sprite_items::car.palette_item().create_new_palette();
    new_pal.set_color(3,bn::color(18,12,26));
    car2 = CompositeSprite();
    
    bn::sprite_ptr car2_spr = bn::sprite_items::car.create_sprite(-31,0,0);
    car2_spr.set_palette(new_pal); 
    car2->addSprite(car2_spr);
    car2_spr = bn::sprite_items::car.create_sprite(0,0,1);
    car2_spr.set_palette(new_pal); 
    car2->addSprite(car2_spr);
    car2_spr = bn::sprite_items::car.create_sprite(31,0,2);
    car2_spr.set_palette(new_pal); 
    car2->addSprite(car2_spr);
    car2->set_position(bn::fixed_point(70,56));

}

WorkParking::~WorkParking(){
    global_var.getDialogManager().resetBg();
}

bn::optional<RoomExit> WorkParking::update(){
    if(jim){ 
        jim->update();
        jim->checkDialog(player.boundaries());
    }

    player.update();

    Room::update();

    return checkExits();
}
}