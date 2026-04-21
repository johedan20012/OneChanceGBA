#include "HouseBedroom1.h"

#include "bn_sprite_items_penny.h"
#include "bn_sprite_items_lab_coat.h"
#include "bn_sprite_items_character.h"

#include "bn_regular_bg_items_bg_house_1.h"
#include "bn_regular_bg_items_bg_house_1b.h"
#include "bn_regular_bg_items_bg_house_1c.h"

namespace game{

HouseBedroom1::HouseBedroom1(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_1.create_bg(8,48),bn::fixed_rect(0,0,240,131),_player),
    global_var(_global_var),
    player_reflexion(bn::sprite_items::character.create_sprite(0,0)),
    white_lab_coat(bn::sprite_items::lab_coat.create_sprite(0,0)){

    player_reflexion.set_bg_priority(3);
    bg->set_priority(2);

    white_lab_coat.set_bg_priority(2);
    white_lab_coat.set_z_order(2);

    player.setMovementBox(bn::fixed_rect(14.5,0,231,160));
    player.setHflip(true);

    switch(entering_from){
        case DIRECTION::RIGHT:
            player.setPos(108,29);
            break;
        default:
            player.setPos(-88,29);
            break;
    }

    exits.push_back(RoomExit(
        "house_hall",bn::fixed_rect(120,26,4,64),DIRECTION::LEFT,false));

    global_var.getDialogManager().resetBg();
    global_var.getDialogManager().resetBottomText();
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
            loadDay1();
            break;
    }
}

void HouseBedroom1::loadDay1(){
    white_lab_coat.set_position(bn::fixed_point(82,11));
}

void HouseBedroom1::loadDay2(){
    white_lab_coat.set_rotation_angle(90);
    white_lab_coat.set_position(bn::fixed_point(23,48));
}

void HouseBedroom1::loadDay3(){
    bg->set_item(bn::regular_bg_items::bg_house_1b);

    white_lab_coat.set_rotation_angle(90);
    white_lab_coat.set_position(bn::fixed_point(23,48));

    white_lab_coat2 = bn::sprite_items::lab_coat.create_sprite(75,60);
    white_lab_coat2->set_rotation_angle(90);
    white_lab_coat2->set_bg_priority(2);
    white_lab_coat2->set_z_order(2);
    
    penny = bn::sprite_items::penny.create_sprite(-24,32);
    DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,40,64),false,false);
    dialog->addDialog(Pair<int,int>(21,120));
    dialog->addDialog(Pair<int,int>(22,120));
    penny->addDialog(dialog);
    penny->setVisibility(false);
}

void HouseBedroom1::loadDay4(){
    bg->set_item(bn::regular_bg_items::bg_house_1c);

    white_lab_coat.set_rotation_angle(90);
    white_lab_coat.set_position(bn::fixed_point(23,48));

    white_lab_coat2 = bn::sprite_items::lab_coat.create_sprite(75,60);
    white_lab_coat2->set_rotation_angle(90);
    white_lab_coat2->set_bg_priority(2);
    white_lab_coat2->set_z_order(2);
    
    penny = bn::sprite_items::penny.create_sprite(26,25,1);
    DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(-14,0,31,64),false,false);
    dialog->addDialog(Pair<int,int>(31,148));
    dialog->addDialog(Pair<int,int>(32,208));
    dialog->addDialog(Pair<int,int>(33,340));
    penny->addDialog(dialog);
}

bn::optional<RoomExit> HouseBedroom1::update(){
    player.update(global_var.currentDay() == 4 && global_var.getDialogManager().hasADialogSequence());
    player_reflexion.set_position(player.getPos() + bn::fixed_point(13,-10));
    player_reflexion.set_tiles(player.getTilesItem());
    player_reflexion.set_horizontal_flip(player.getHorizontalFlip());

    if(penny){
        penny->checkDialog(player.boundaries());
        penny->lookAt(player.getPos(),true);
    }
    Room::update();

    return checkExits();
}

}