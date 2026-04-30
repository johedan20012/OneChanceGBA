#include "skipWork.h"

#include "bn_sprite_items_car.h"
#include "bn_sprite_items_work_people.h"

#include "bn_regular_bg_items_bg_skip_work_1.h"
#include "bn_regular_bg_items_bg_work_parking_c.h"

namespace game{
SkipWork::SkipWork(Player& _player,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_skip_work_1.create_bg(8,48),bn::fixed_rect(0,4,240,137),_player),
    
    global_var(_global_var){

    global_var.setDayChoice(global_var.currentDay(),CHOICE::SKIP_WORK);
    global_var.getDialogManager().resetBottomText();
    global_var.getDialogManager().resetBg();

    switch (global_var.currentDay()){
        case 4:
            loadDay4();
            break;        
        case 2:
        case 3:
        default: //Day 1
            loadDay1();
            break;
    }

    initial_dark = bn::make_unique<Timer>();

    setVisibility(false);
}

void SkipWork::loadDay1(){
    people.push_back(bn::sprite_items::work_people.create_sprite(-99,30,2));
    people.push_back(bn::sprite_items::work_people.create_sprite(-64,30,5));
    people.push_back(bn::sprite_items::work_people.create_sprite(-53,44,3));
    people.push_back(bn::sprite_items::work_people.create_sprite(3,31,9));

    player.resetAnim();
    player.setHflip(true);
    player.setPos(43,31);

    people[0].set_horizontal_flip(true);
    people[3].set_horizontal_flip(true);
}

void SkipWork::loadDay4(){
    bg->set_item(bn::regular_bg_items::bg_work_parking_c);

    car = CompositeSprite();

    car->addSprite(bn::sprite_items::car.create_sprite(-31,0,0));
    car->addSprite(bn::sprite_items::car.create_sprite(0,0,1));
    car->addSprite(bn::sprite_items::car.create_sprite(31,0,2));

    car->set_position(bn::fixed_point(7,58));
}

bn::optional<RoomExit> SkipWork::updateDay1(){
    if(initial_dark && initial_dark->elapsedFrames() >= 60){
        setVisibility(true);
        initial_dark.reset();
        end_room = bn::make_unique<Timer>();
    }

    if(end_room && end_room->elapsedFrames() >= 330) return RoomExit("day_change",DIRECTION::DOOR1);

    return bn::nullopt;
}

bn::optional<RoomExit> SkipWork::updateDay4(){
    if(initial_dark && initial_dark->elapsedFrames() >= 44){
        setVisibility(true);
        player.setVisible(false);
        initial_dark.reset();
        end_room = bn::make_unique<Timer>();
    }

    if(end_room){
        if(end_room->elapsedFrames() >= 148){
            player.useNightColors(true);
            return RoomExit("house_entrance",DIRECTION::DOOR1);
        }

        if(frames_anim_car == 15 || frames_anim_car == 0){
            car->changeSpriteTiles(0,bn::sprite_items::car.tiles_item(),(frames_anim_car==15)? 3: 0);
            car->changeSpriteTiles(1,bn::sprite_items::car.tiles_item(),(frames_anim_car==15)? 4: 1);
            car->changeSpriteTiles(2,bn::sprite_items::car.tiles_item(),(frames_anim_car==15)? 5: 2);
            
            car->set_position(bn::fixed_point(7,(frames_anim_car==15)? 57: 58));
        }
        frames_anim_car = (frames_anim_car+1)%20;
    }

    return bn::nullopt;
}

bn::optional<RoomExit> SkipWork::update(){
    Room::update();

    if(global_var.currentDay() == 4) return updateDay4();
    else return updateDay1();

    return bn::nullopt;
}

void SkipWork::setVisibility(bool visible){
    bg->set_visible(visible);
    bg_paper->set_visible(visible);
    if(car) car->setVisibility(visible);
    for(auto& ppl : people) ppl.set_visible(visible);
    player.setVisible(visible);
}

}