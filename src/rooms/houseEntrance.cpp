#include "houseEntrance.h"

#include "bn_sprite_items_car.h"
#include "bn_sprite_items_cloud.h"
#include "bn_sprite_items_newspaper.h"
#include "bn_sprite_items_work_people.h"

#include "bn_regular_bg_items_bg_house_5.h"
#include "bn_regular_bg_items_bg_house_5_b.h"
#include "bn_regular_bg_items_bg_house_5_c.h"
#include "bn_regular_bg_items_bg_house_5_d.h"
#include "bn_regular_bg_items_bg_house_5_e.h"
#include "bn_regular_bg_items_bg_newspaper1.h"
#include "bn_regular_bg_items_bg_newspaper2.h"
#include "bn_regular_bg_items_bg_newspaper3.h"
#include "bn_regular_bg_items_bg_newspaper4.h"
#include "bn_regular_bg_items_bg_bottom_text_c.h"

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
        case 5:
            loadDay5();
            break;
        default:
            break;
    }

    #ifdef DEBUG_GAME
    Room::createExitsDebug();
    #endif
}

HouseEntrance::~HouseEntrance(){
    global_var.getDialogManager().resetBg();
}

void HouseEntrance::loadDay2(){
    cloud.set_visible(false);

    newspaper_item = bn::regular_bg_items::bg_newspaper2;
}

void HouseEntrance::loadDay3(){
    cloud.set_visible(false);

    newspaper_item = bn::regular_bg_items::bg_newspaper3;
    bg->set_item(bn::regular_bg_items::bg_house_5_b);
}

void HouseEntrance::loadDay4(){
    cloud.set_visible(false);

    newspaper_item = bn::regular_bg_items::bg_newspaper4;
    global_var.getDialogManager().setBg(bn::regular_bg_items::bg_bottom_text_c.create_bg(8,48));

    if(global_var.dayChoice(global_var.currentDay()) == CHOICE::SKIP_WORK){
        bg->set_item(bn::regular_bg_items::bg_house_5_d);
        bg->set_visible(false);
        bg_paper->set_visible(false);
        newspaper.set_visible(false);

        car.set_position(bn::fixed_point(219.6,67));
        auto car_pal = car.palette().value();
        car_pal.set_colors(car_dark_pal);
        player.setVisible(false);
        player.setPos(140,140);

        timer = bn::make_unique<Timer>();
        carMovement = CompositeSpritePosToAction(car,190, bn::fixed_point(72,67));
    
        exits.clear();
        exits.push_back(RoomExit("house_hall",bn::fixed_rect(-120,53,50,64),DIRECTION::RIGHT,false));
    }else{
        bg->set_item(bn::regular_bg_items::bg_house_5_c);

        player.setMovementBox(bn::fixed_rect(-51,0,104,160));

        npcs.push_back(bn::sprite_items::work_people.create_sprite(16,52,0));
        npcs.push_back(bn::sprite_items::work_people.create_sprite(49,48,2));
        npcs.push_back(bn::sprite_items::work_people.create_sprite(67,53,9));
        npcs.push_back(bn::sprite_items::work_people.create_sprite(88,51,5));
        npcs.back().getPalette().set_color(12,bn::color(6,3,2)); //Change hair color
        npcs.back().getPalette().set_color(19,bn::color(0,0,0)); //Change shirt color
        for(auto& npc: npcs){
            npc.setVisibility(false);
        }

        exits.back().trigger = bn::fixed_rect(20,53,40,64);
        exits.back().name = "work_lobby";
    }
}

void HouseEntrance::loadDay5(){
    cloud.set_visible(false);

    newspaper.set_visible(false);

    if(global_var.dayChoice(5) == CHOICE::DEFEND){
        bg->set_item(bn::regular_bg_items::bg_house_5_d);
        bg->set_visible(false);
        bg_paper->set_visible(false);

        car.set_position(bn::fixed_point(219.6,67));
        auto car_pal = car.palette().value();
        car_pal.set_colors(car_dark_pal);
        player.setVisible(false);
        player.setPos(140,140);

        timer = bn::make_unique<Timer>();
        carMovement = CompositeSpritePosToAction(car,190, bn::fixed_point(72,67));
    
        exits.clear();
        exits.push_back(RoomExit("house_hall",bn::fixed_rect(-120,53,50,64),DIRECTION::RIGHT,false));
    }else{
        bg->set_item(bn::regular_bg_items::bg_house_5_e);
    }
}

bn::optional<RoomExit> HouseEntrance::updateDay1_3(){
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

        if(carMovement && carMovement->done()){ 
            player.setVisible(true);
            return exits[0];
        }

        return bn::nullopt;
    }

    if(newspaper_bg){
        if(bn::keypad::a_held()) newspaper_bg.reset();
        
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

bn::optional<RoomExit> HouseEntrance::updateDay4(){
    if(global_var.dayChoice(global_var.currentDay()) == CHOICE::SKIP_WORK){
        if(timer && carMovement){
            if(timer->elapsedFrames() >= 44){
                bg->set_visible(true);
                bg_paper->set_visible(true);
                timer.reset();
            }
            return bn::nullopt;
        }

        if(carMovement){
            if(carMovement->done()){
                timer = bn::make_unique<Timer>();
                carMovement.reset();
            }
            else carMovement->update();
            return bn::nullopt;
        }

        if(timer && timer->elapsedFrames() >= 44){
            timer.reset();
            player.setPos(68,50);
            player.setVisible(true);
            player.setHflip(true);
            player.resetAnim();
            return bn::nullopt;
        }

        player.update();
    }else{
        if(newspaper_bg){
            if(bn::keypad::a_held()) newspaper_bg.reset();
            for(auto& npc: npcs){
                npc.setVisibility(true);
            }
            timer = bn::make_unique<Timer>();
            return bn::nullopt;
        }
        if(timer && timer->elapsedFrames() >= 72){
            timer.reset();
            {
            DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(-50,0,100,64),false,false);
            dialog->addDialog(Pair<int,int>(38,272));
            dialog->addDialog(Pair<int,int>(39,456));
            npcs[0].addDialog(dialog);
            }
            exits.push_back(RoomExit("house_molly",bn::fixed_rect(-120,53,40,64),DIRECTION::LEFT,true));
            exits.back().info = "Go home";
        }
        npcs[0].checkDialog(player.boundaries());

        player.update(global_var.getDialogManager().hasADialogSequence() || timer);
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

        auto exit = Room::checkExits();
        if(exit && exit->name == bn::string_view("house_molly")) global_var.setDayChoice(global_var.currentDay(),CHOICE::GO_HOME);
        return exit;
    }

    return Room::checkExits();
}

bn::optional<RoomExit> HouseEntrance::updateDay5(){
    if(global_var.dayChoice(5) == CHOICE::DEFEND){
        if(timer && carMovement){
            if(timer->elapsedFrames() >= 44){
                bg->set_visible(true);
                bg_paper->set_visible(true);
                timer.reset();
            }
            return bn::nullopt;
        }

        if(carMovement){
            if(carMovement->done()){
                timer = bn::make_unique<Timer>();
                carMovement.reset();
            }
            else carMovement->update();
            return bn::nullopt;
        }

        if(timer && timer->elapsedFrames() >= 44){
            timer.reset();
            player.setPos(68,50);
            player.setVisible(true);
            player.setHflip(true);
            player.resetAnim();
            return bn::nullopt;
        }

        player.update();

        return Room::checkExits();
    }else{
        if(isExiting){
            for(auto &action : carRotations){
                if(action){
                    action->update();
                    if(action->done()) action.reset();
                    return bn::nullopt;
                }
            }

            if(carMovement) carMovement->update();

            if(carMovement && carMovement->done()){ 
                player.setVisible(true);
                return exits[0];
            }

            return bn::nullopt;
        }

        player.update();

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
    }
        
    return bn::nullopt;
}

bn::optional<RoomExit> HouseEntrance::update(){

    Room::updateExitsInfo();
    Room::update();

    #ifdef DEBUG_GAME
    if(mov) mov->update();
    #endif

    switch(global_var.currentDay()){
        case 4:
            return updateDay4();
        case 5:
            return updateDay5();
        case 3:
        case 2:
        default:
            return updateDay1_3();
    }

    return bn::nullopt;
}

}