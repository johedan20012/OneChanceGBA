#include "houseHall.h"

#include "bn_sprite_items_penny.h"
#include "bn_sprite_items_molly.h"
#include "bn_sprite_items_teddy.h"

#include "bn_regular_bg_items_bg_house_2.h"
#include "bn_regular_bg_items_bg_house_2b.h"
#include "bn_regular_bg_items_bg_house_2c.h"

namespace game{

HouseHall::HouseHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_2.create_bg(8,48),bn::fixed_rect(0,9,239,113),_player),
    global_var(_global_var),npc(bn::sprite_items::penny.create_sprite(54,23)){

    player.setMovementBox(bn::fixed_rect(-10.5,0,239,160));

    switch(entering_from){
    case DIRECTION::LEFT:
        player.setPos(-108,29);
        break;
    case DIRECTION::DOOR1:
        player.setPos(-92,29);
        break;
    case DIRECTION::DOOR2:
        player.setPos(-8,29);
        break;
    case DIRECTION::RIGHT:
        player.setPos(106,29);
        break;
    default:
        player.setPos(0,29);
        break;
    }
    
    exits.push_back(RoomExit("house_bedroom",bn::fixed_rect(-120,26,4,64),DIRECTION::RIGHT,false));
    exits.push_back(RoomExit("house_molly",bn::fixed_rect(-84,26,20,64),DIRECTION::RIGHT,true)); 
    exits[1].info = "Molly's Room";
    exits.push_back(RoomExit("house_bath",bn::fixed_rect(-16,26,20,64),DIRECTION::RIGHT,true));
    exits[2].info = "Bathroom";
    exits.push_back(RoomExit("house_entrance",bn::fixed_rect(100,26,25,64),DIRECTION::LEFT,true));
    exits[3].info = "Outside";

    switch(global_var.currentDay()){
        case 2:
            loadDay2();
            break;
        case 3:
            loadDay3();
            break;
        case 4:
            loadDay4();
            break;
        default:
            loadDay1(entering_from);
            break;
    }

    #ifdef DEBUG_GAME
    createExitsDebug();
    #endif
}

void HouseHall::loadDay1(DIRECTION entering_from){
    if(entering_from == DIRECTION::LEFT) global_var.getDialogManager().setBottomText(0,120);

    {
    DialogTrigger* penny_dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,30,64),false);
    penny_dialog->addDialog({1,90});
    npc->addDialog(penny_dialog);
    }
}

void HouseHall::loadDay2(){
    npc->setVisibility(false);
}

void HouseHall::loadDay3(){
    npc = bn::sprite_items::molly.create_sprite(-55,41);
    prop = bn::sprite_items::teddy.create_sprite(-44,44);

    DialogTrigger* molly_dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,30,64),false,false);
    molly_dialog->addDialog(Pair<int,int>(23,180));
    npc->addDialog(molly_dialog);
}

void HouseHall::loadDay4(){
    if(global_var.dayChoice(global_var.currentDay()) == CHOICE::SKIP_WORK){
        bg->set_item(bn::regular_bg_items::bg_house_2c);
        exits.pop_back(); // Delete exits "Go to Work"
    }else{
        bg->set_item(bn::regular_bg_items::bg_house_2b);
    }

    npc->setVisibility(false);
}

bn::optional<RoomExit> HouseHall::update(){
    player.update();

    if(global_var.currentDay() <= 2 && npc) npc->lookAt(player.getPos(),true);
    if(npc) npc->checkDialog(player.boundaries());

    Room::updateExitsInfo();
    Room::update();

    return checkExits();
}
}
