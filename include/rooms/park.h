#ifndef PARK_H
#define PARK_H

#include "bn_unique_ptr.h"

#include "room.h"
#include "timer.h"
#include "johnSitPark.h"
#include "dialogTrigger.h"
#include "snowParticles.h"
#include "globalVariables.h"

namespace game{
class Park : public Room{
private:
    GlobalVariables &global_var;

    bn::unique_ptr<SnowParticles> snow_particles;

    bool second_room = false;
    bool showing_graveyard = false;
    bn::unique_ptr<Timer> timer;
    DialogTrigger* molly_dialog;
    bn::unique_ptr<JohnSitPark> john_animation;
    int second_room_state = 0;
    
    void loadDay6();

    void load2Day5();
    void load2Day6();

    bn::optional<RoomExit> update2Day5();
    bn::optional<RoomExit> update2Day6();
public:
    Park(Player& _player,GlobalVariables &_global_var);
    ~Park();

    bn::optional<RoomExit> update();
};
}
#endif