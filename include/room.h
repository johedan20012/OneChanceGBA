#ifndef ROOM_H
#define ROOM_H

#include "bn_regular_bg_ptr.h"

#include "bn_fixed_rect.h"
#include "bn_blending.h"
#include "bn_string.h"
#include "bn_log.h"

#include "player.h"

namespace game{

class Room{
private:
    bn::fixed background_weight; 
    bn::fixed foreground_weight; 
    bool change_intensity;

protected:
    bn::regular_bg_ptr bg;
    bn::optional<bn::regular_bg_ptr> bg_paper;
    Player& player;

    bn::vector<bn::fixed_rect,6> exits; 
    bn::vector<bn::string<15>,6> exitsName;

public:
    Room(const bn::regular_bg_ptr _bg,bn::optional<bn::regular_bg_ptr> _bg_paper,Player& _player);
    virtual ~Room();

    bn::optional<bn::string<15>> checkExits(); 

    virtual void update();
};
}

#endif // ROOM_H
