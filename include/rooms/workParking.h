#ifndef WORKPARKING_H
#define WORKPARKING_H

#include "bn_sprite_actions.h"

#include "npc.h"
#include "room.h"
#include "timer.h"
#include "globalVariables.h"

namespace game{
class WorkParking : public Room{
private:
    class JimNPC : public NPC{
    private:
        Timer smoke;
    public:
        JimNPC();
        ~JimNPC() override {}

        void update() override;
    };

    GlobalVariables& global_var;

    JimNPC jim;

public:
    WorkParking(Player& _player,DIRECTION entering_from,GlobalVariables& _global);
    ~WorkParking() override;

    bn::optional<RoomExit> update() override;
};
}

#endif