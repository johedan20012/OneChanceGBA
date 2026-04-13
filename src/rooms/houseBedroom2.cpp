#include "houseBedroom2.h"

#include "bn_sprite_items_molly.h"
#include "bn_sprite_items_teddy.h"

#include "bn_regular_bg_items_bg_house_3.h"
#include "bn_regular_bg_items_bg_house_3_b.h"

namespace game{

HouseBedroom2::HouseBedroom2(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_3.create_bg(8,48),bn::fixed_rect(6,0,228,131),_player),
    global_var(_global_var),
    molly(bn::sprite_items::molly.create_sprite(-77,39)),teddy_bear(bn::sprite_items::teddy.create_sprite(-24,43)){

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
        case 3:
            loadDay3();
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

void HouseBedroom2::loadDay3(){
    molly.setVisibility(false);
    teddy_bear.set_visible(false);

    if(global_var.roofCheckedDay3()){
        showing_go_home_option = true;
        global_var.getDialogManager().resetBg();
        global_var.getDialogManager().resetBottomText();
        global_var.setDayChoice(global_var.currentDay(),CHOICE::GO_HOME);
        bg->set_item(bn::regular_bg_items::bg_house_3_b);
        bg->set_visible(false);
        bg_paper->set_visible(false);
        player.setVisible(false);
        timer = bn::make_unique<Timer>();
    }
}

bn::optional<RoomExit> HouseBedroom2::update(){
    player.update();

    molly.checkDialog(player.boundaries());

    Room::update();

    if(global_var.currentDay() == 3){
        return updateDay3();
    }

    return checkExits();
}

bn::optional<RoomExit> HouseBedroom2::updateDay3(){
    if(showing_go_home_option){
        if(timer && timer->elapsedFrames() == 92){
            bg->set_visible(true);
            bg_paper->set_visible(true);
        }

        if(timer && timer->elapsedFrames() >= 308){
            return RoomExit("day_change",DIRECTION::RIGHT);
        }

        return bn::nullopt;
    }

    return checkExits();
}

}