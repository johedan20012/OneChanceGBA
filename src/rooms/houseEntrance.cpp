#include "houseEntrance.h"

namespace game{
HouseEntrance::HouseEntrance(Player& _player,DIRECTION _entering_from):
    Room(bn::regular_bg_items::bg_house_5.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
    car(),isExiting(false){

    car.addSprite(bn::sprite_items::car.create_sprite(-31,0,0));
    car.addSprite(bn::sprite_items::car.create_sprite(0,0,1));
    car.addSprite(bn::sprite_items::car.create_sprite(31,0,2));

    car.setPos(bn::fixed_point(72,67));

    switch(_entering_from){
        case DIRECTION::LEFT:
            player.setPos(-92,53);
            break;
        default:
            player.setPos(0,0);
            break;
    }

    exits.push_back(RoomExit("house_hall",bn::fixed_rect(60,53,21,64),DIRECTION::LEFT,true));
}

HouseEntrance::~HouseEntrance(){
    Room::~Room();
}

bn::optional<RoomExit> HouseEntrance::update(){
    if(isExiting){
        for(auto &action : carRotations){
            if(action){
                action->update();
                if(action->done()) action.reset();
                return bn::nullopt;
            }
        }

        carMovement->update();

        Room::update();

        if(carMovement->done()){ 
            player.setVisible(true);
            return exits[0];
        }

        return bn::nullopt;
    }

    player.update();
    Room::update();

    auto exit = checkExits();
    if(exit.has_value() && exit.get()->name == bn::string<15>("house_hall")){
        isExiting = true;
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