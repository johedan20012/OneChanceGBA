#include "houseBedroom2.h"

namespace game{

HouseBedroom2::HouseBedroom2(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_3.create_bg(8,48),bn::fixed_rect(6,0,228,131),_player),
    global_var(_global_var),
    molly(bn::sprite_items::molly.create_sprite(-77,39)),teddy_bear(bn::sprite_items::teddy.create_sprite(-24,43)),
    mov(teddy_bear){

    player.setMovementBox(bn::fixed_rect(22.5,0,215,160));

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,29);
            break;
        default:
            player.setPos(0,29);
            break;
    }

    exits.push_back(RoomExit("house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::DOOR1,false));

    switch(global_var.currentDay()){
        case 2:
            loadDay2();
            break;
        default:
            loadDay1();
            break;
    }
}

void HouseBedroom2::loadDay1(){
    molly.set_position(bn::fixed_point(-77,39));
    teddy_bear.set_position(bn::fixed_point(-24,43));

    {
    DialogTrigger* molly_dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,40,60),true,true);
    molly_dialog->addDialog(Pair<int,int>(2,120));  
    molly.addDialog(molly_dialog);
    }
}

void HouseBedroom2::loadDay2(){
    molly.set_position(bn::fixed_point(-27,39));
    teddy_bear.set_position(bn::fixed_point(-15,43));

    {
    DialogTrigger* molly_dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,40,60),false,false);
    molly_dialog->addDialog(Pair<int,int>(8,192));  
    molly.addDialog(molly_dialog);
    }
}

bn::optional<RoomExit> HouseBedroom2::update(){
    player.update();

    molly.checkDialog(player.boundaries());

    Room::update();

    mov.update();

    return checkExits();
}

}