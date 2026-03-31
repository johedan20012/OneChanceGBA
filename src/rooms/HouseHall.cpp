#include "houseHall.h"

#include "dialogs.h"

namespace game{

HouseHall::HouseHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_2.create_bg(8,48),bn::fixed_rect(0,9,239,113),_player),
    penny(bn::sprite_items::penny.create_sprite(54,23)),global_var(_global_var){

    player.setMovementBox(bn::fixed_rect(-10.5,0,239,160));

    switch(entering_from){
        case DIRECTION::LEFT:
            player.setPos(-108,29);
            global_var.getDialogManager().setBottomText(0,120);
            break;
        case DIRECTION::DOOR1:
            player.setPos(-92,29);
            break;
        case DIRECTION::DOOR2:
            player.setPos(-8,29);
            break;
        default:
            player.setPos(0,29);
            break;
    }

    penny.lookAt(player.getPos());
    {
    DialogTrigger* penny_dialog = new DialogTrigger(_global_var,bn::fixed_rect(0,0,30,64),false);
    penny_dialog->addDialog({1,90});
    penny.addDialog(penny_dialog);
    }
    exits.push_back(RoomExit("house_bedroom",bn::fixed_rect(-120,26,4,64),DIRECTION::RIGHT,false));
    exits.push_back(RoomExit("house_molly",bn::fixed_rect(-84,26,20,64),DIRECTION::RIGHT,true)); 
    exits[1].info = "Molly's Room";
    exits.push_back(RoomExit("house_bath",bn::fixed_rect(-16,26,20,64),DIRECTION::RIGHT,true));
    exits[2].info = "Bathroom";
    exits.push_back(RoomExit("house_entrance",bn::fixed_rect(100,26,25,64),DIRECTION::LEFT,true));
    exits[3].info = "Outside";

    #ifdef DEBUG_GAME
    createExitsDebug();
    #endif
}

bn::optional<RoomExit> HouseHall::update(){
    player.update();

    penny.lookAt(player.getPos());
    penny.checkDialog(player.boundaries());

    Room::updateExitsInfo();
    Room::update();

    return checkExits();
}
}
