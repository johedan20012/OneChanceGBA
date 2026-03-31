#ifndef WORKPARKING_H
#define WORKPARKING_H

#include "bn_regular_bg_items_bg_work_parking.h"

#include "bn_sprite_actions.h"
#include "bn_sprite_items_jim.h"

#include "npc.h"
#include "room.h"
#include "timer.h"

namespace game{
class WorkParking : public Room{
private:
    class JimNPC : public NPC{
    private:
        Timer smoke;
    public:
        JimNPC();
        ~JimNPC() override;

        void update() override;
    };

    JimNPC jim;

public:
    WorkParking(Player& _player,DIRECTION entering_from);
    ~WorkParking() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif