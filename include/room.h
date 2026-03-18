#ifndef ROOM_H
#define ROOM_H

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg_paper_full.h"

#include "bn_rect_window.h"
#include "bn_fixed_rect.h"
#include "bn_blending.h"
#include "bn_window.h"
#include "bn_string.h"
#include "bn_log.h"

#include "player.h"

namespace game{

enum DIRECTION{
    LEFT = 0,
    DOOR1,
    DOOR2,
    DOOR3,
    DOOR4,
    RIGHT
};

struct RoomExit{
    bn::string<15> name;
    bn::fixed_rect trigger;
    DIRECTION next_in_dir;
    bool needs_action;

    RoomExit(bn::string<15> _name,bn::fixed_rect _trigger,DIRECTION _next,bool _needs_action){
        name = _name;
        trigger = _trigger;
        next_in_dir = _next;
        needs_action = _needs_action;
    }

    RoomExit(bn::string<15> _name, DIRECTION _next){
        name = _name;
        trigger = bn::fixed_rect(1000,1000,2,2); //Don't bother
        next_in_dir = _next;
        needs_action = true;
    }
};

class Room{
private:
    bn::fixed background_weight; 
    bn::fixed foreground_weight; 
    bool change_intensity;

protected:
    bn::regular_bg_ptr bg;
    bn::regular_bg_ptr bg_paper;
    Player& player;
    bool isExiting = false;

    bn::vector<RoomExit,6> exits;

    bn::optional<RoomExit> checkExits(); 

public:
    Room(const bn::regular_bg_ptr _bg,bn::fixed_rect _paper_boundaries,Player& _player);
    virtual ~Room();

    virtual bn::optional<RoomExit> update();
};
}

#endif // ROOM_H
