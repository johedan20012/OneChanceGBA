#ifndef END_H
#define END_H

#include "bn_unique_ptr.h"

#include "room.h"
#include "snowParticles.h"
#include "globalVariables.h"

namespace game{
class End : public Room{
private:
    GlobalVariables& global_var;

    bn::unique_ptr<SnowParticles> snow_particles;

public:
    End(Player& _player,GlobalVariables& _global_var);
    ~End() override {}

    bn::optional<RoomExit> update() override;
};
}
#endif