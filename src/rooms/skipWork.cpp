#include "skipWork.h"

#include "globalVariables.h"

namespace game{
SkipWork::SkipWork(Player& _player):
    Room(bn::regular_bg_items::bg_skip_work_1.create_bg(8,48),bn::fixed_rect(0,4,240,137),_player),
    people{bn::sprite_items::work_people.create_sprite(-99,30,2),
           bn::sprite_items::work_people.create_sprite(-64,30,5),
           bn::sprite_items::work_people.create_sprite(-53,44,3),
           bn::sprite_items::work_people.create_sprite(3,31,9)}{

    GlobalVariables::setDayChoice(GlobalVariables::currentDay(),CHOICE::SKIP_WORK);

    people[0].set_horizontal_flip(true);
    people[3].set_horizontal_flip(true);

    player.resetAnim();
    player.setHflip(true);
    player.setPos(43,31);

    setVisibility(false);
}

SkipWork::~SkipWork(){
    Room::~Room();
}

bn::optional<RoomExit> SkipWork::update(){
    if(initial_dark.elapsedFrames() <= 60){
        if(initial_dark.elapsedFrames() >= 60){
            setVisibility(true);
        }
    }

    if(initial_dark.elapsedFrames() >= 60){
        if(end_room.elapsedFrames() >= 390){
            return RoomExit("day_change",DIRECTION::DOOR1);
        }
    }

    Room::update();

    return bn::nullopt;
}

void SkipWork::setVisibility(bool visible){
    bg.set_visible(visible);
    bg_paper.set_visible(visible);
    for(auto ppl : people) ppl.set_visible(visible);
    player.setVisible(visible);
}

}