#ifndef END_H
#define END_H

#include "room.h"
#include "globalVariables.h"

namespace game{
class End : public Room{
private:
    GlobalVariables& global_var;

public:
    End(Player& _player,GlobalVariables& _global_var);
    ~End() override {}

    bn::optional<RoomExit> update() override;
};
}
#endif