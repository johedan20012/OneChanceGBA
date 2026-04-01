#include "HouseBedroom1.h"

namespace game{

HouseBedroom1::HouseBedroom1(Player& _player,DIRECTION entering_from):
    Room(bn::regular_bg_items::bg_house_1.create_bg(8,48),bn::fixed_rect(0,0,240,131),_player),
    player_reflexion(bn::sprite_items::character.create_sprite(0,0)){

    player_reflexion.set_bg_priority(3);
    bg.set_priority(2);

    player.setMovementBox(bn::fixed_rect(14.5,0,231,160));

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,29);
            break;
        default:
            player.setPos(0,29);
            break;
    }

    exits.push_back(RoomExit(
        "house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::LEFT,false));
}

bn::optional<RoomExit> HouseBedroom1::update(){
    player.update();
    player_reflexion.set_position(player.getPos() + bn::fixed_point(13,-10));
    player_reflexion.set_tiles(player.getTilesItem());
    player_reflexion.set_horizontal_flip(player.getHorizontalFlip());

    Room::update();

    return checkExits();
}

}