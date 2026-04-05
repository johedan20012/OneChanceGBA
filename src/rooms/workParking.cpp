#include "workParking.h"

#include "bn_sprite_items_jim.h"

#include "bn_regular_bg_items_bg_bottom_text.h"
#include "bn_regular_bg_items_bg_work_parking.h"

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
    global_var(_global){

    player.setMovementBox(bn::fixed_rect(10,0,240,160));

    auto& dialog_mgr = global_var.getDialogManager();
    dialog_mgr.setBg(bn::regular_bg_items::bg_bottom_text.create_bg(8,48));

    {
        DialogTrigger* dialog = new DialogTrigger(_global,bn::fixed_rect(0,0,30,60),false);
        dialog->addDialog({3,90});
        jim.addDialog(dialog);
    }

    switch (entering_from){
        case DIRECTION::LEFT:
            player.setPos(-108,49);
            break;    
        default:
            player.setPos(0,0);
            break;
    }

    exits.push_back(RoomExit("work_lobby",bn::fixed_rect(123,20,10,64),DIRECTION::LEFT,false));
}

WorkParking::~WorkParking(){
    global_var.getDialogManager().resetBg();
}

bn::optional<RoomExit> WorkParking::update(){
    jim.update();
    jim.checkDialog(player.boundaries());

    player.update();

    Room::update();

    return checkExits();
}
}