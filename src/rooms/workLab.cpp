#include "workLab.h"

namespace game{
WorkLab::WorkLab(Player& _player):
    Room(bn::regular_bg_items::bg_work_lab.create_bg(8,48),bn::fixed_rect(0,0,240,132),_player),
    npcs{bn::sprite_items::work_people.create_sprite(-92,23,2),bn::sprite_items::work_people.create_sprite(-8,23,6)},
    pc_screen(bn::sprite_items::pc_screen.create_sprite(-28,17)){

    player.resetAnim();
    player.setHflip(true);
    player.setPos(60,23);
    player.setMovementBox(bn::fixed_rect(0,0,240,160));

    setVisibility(false);
}

WorkLab::~WorkLab(){
    Room::~Room();
}

void WorkLab::setVisibility(bool visibility){
    bg.set_visible(visibility);
    bg_paper.set_visible(visibility);

    npcs[0].setVisibility(visibility);
    npcs[1].setVisibility(visibility);

    pc_screen.set_visible(visibility);

    player.setVisible(visibility);
}

bn::optional<RoomExit> WorkLab::update(){

    if(initial_dark.elapsedFrames() <= 54){
        if(initial_dark.elapsedFrames() >= 54){
            setVisibility(true);
        }
    }

    if(initial_dark.elapsedFrames() >= 54){
        if(end_room.elapsedFrames() >= 240){
            return RoomExit("end_day",DIRECTION::DOOR1);
        }
    }

    Room::update();

    return bn::nullopt;
}

}