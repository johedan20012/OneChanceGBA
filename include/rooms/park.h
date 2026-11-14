#ifndef PARK_H
#define PARK_H

#include "bn_unique_ptr.h"

#include "room.h"
#include "timer.h"
#include "dialogTrigger.h"
#include "globalVariables.h"

namespace game{
class Park : public Room{
private:
    GlobalVariables &global_var;

    bool second_room = false;
    bool showing_graveyard = false;
    bn::unique_ptr<Timer> timer;
    DialogTrigger* molly_dialog;
    
public:
    Park(Player& _player,GlobalVariables &_global_var);
    ~Park();

    bn::optional<RoomExit> update();
};
}
#endif