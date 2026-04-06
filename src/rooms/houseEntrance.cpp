#include "houseEntrance.h"

#include "bn_sprite_items_car.h"
#include "bn_sprite_items_cloud.h"
#include "bn_sprite_items_newspaper.h"

#include "bn_regular_bg_items_bg_house_5.h"
#include "bn_regular_bg_items_bg_newspaper1.h"
#include "bn_regular_bg_items_bg_newspaper2.h"

#include "bn_log.h"

namespace game{
HouseEntrance::HouseEntrance(Player& _player,DIRECTION _entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_5.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
    global_var(_global_var),
    car(),cloud(bn::sprite_items::cloud.create_sprite(130,-71)),
    newspaper(bn::sprite_items::newspaper.create_sprite(-43,73)),
    newspaper_item(bn::regular_bg_items::bg_newspaper1),isExiting(false){

    _global_var.getDialogManager().resetBg();
    _global_var.getDialogManager().resetBottomText();

    car.addSprite(bn::sprite_items::car.create_sprite(-31,0,0));
    car.addSprite(bn::sprite_items::car.create_sprite(0,0,1));
    car.addSprite(bn::sprite_items::car.create_sprite(31,0,2));

    car.set_position(bn::fixed_point(72,67));

    player.setMovementBox(bn::fixed_rect(2,0,200,160));

    switch(_entering_from){
        case DIRECTION::LEFT:
            player.setPos(-92,50);
            break;
        default:
            player.setPos(-92,50);
            break;
    }

    exits.push_back(RoomExit("city",bn::fixed_rect(60,53,21,64),DIRECTION::LEFT,true));
    exits.back().info = "Go to Work";

    #ifdef DEBUG_GAME
    Room::createExitsDebug();
    #endif

    switch(global_var.currentDay()){
        case 2:
            loadDay2();
            break;
        default:
            break;
    }
}

void HouseEntrance::loadDay2(){
    cloud.set_visible(false);

    newspaper_item = bn::regular_bg_items::bg_newspaper2;
}

bn::optional<RoomExit> HouseEntrance::update(){
    cloud.set_position(cloud.position().x()-0.2,cloud.position().y()+cloud_y_dir);
    if(cloud.position().x() <= -130) cloud.set_position(130,cloud.position().y());
    if(cloud.position().y() >= -63){ cloud_y_dir = -0.07; cloud.set_position(cloud.position().x(),-63); }
    if(cloud.position().y() <= -73){ cloud_y_dir = 0.07; cloud.set_position(cloud.position().x(),-73); }


    if(isExiting){
        for(auto &action : carRotations){
            if(action){
                action->update();
                if(action->done()) action.reset();
                return bn::nullopt;
            }
        }

        if(carMovement) carMovement->update();

        Room::update();

        if(carMovement && carMovement->done()){ 
            player.setVisible(true);
            return exits[0];
        }

        return bn::nullopt;
    }

    if(newspaper_bg){
        if(bn::keypad::a_pressed()) newspaper_bg.reset();
        
        return bn::nullopt;
    }

    player.update();
    if(!newspaper_picked_up){ 
        if(player.hasNormalState() && player.getPos().x() >= -61){
            player.setPos(-61,player.getPos().y());
            player.bend();
        }else if(player.isBended()){
            newspaper.set_visible(false);
            newspaper_picked_up = true;
            player.standUp();
        }
    }
    if(!newspaper_showed && newspaper_picked_up && player.hasNormalState()){
        newspaper_bg = newspaper_item.create_bg(9,55);
        newspaper_bg->set_priority(1);
        newspaper_showed = true;
    }
    
    Room::updateExitsInfo();
    Room::update();

    auto exit = checkExits();
    if(exit.has_value() && exit.get()->name == bn::string<15>("city")){
        isExiting = true;
        Room::clearExitsInfo();
        player.setVisible(false);

        //car_rotation = bn::sprite_rotate_to_action(car,)
        carMovement = CompositeSpritePosToAction(car,120, bn::fixed_point(180,67));
        carRotations.push_back(CompositeSpriteRotToAction(car,3,4));
        carRotations.push_back(CompositeSpriteRotToAction(car,6,-4));
        carRotations.push_back(CompositeSpriteRotToAction(car,3,0));
    }

    return bn::nullopt;
}

}