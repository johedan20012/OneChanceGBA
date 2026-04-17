#ifndef WORKPARKING_H
#define WORKPARKING_H

#include "bn_sprite_items_car.h"
#include "bn_sprite_actions.h"

#include "bn_unique_ptr.h"

#include "npc.h"
#include "room.h"
#include "timer.h"
#include "compositeSprite.h"
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

    bn::unique_ptr<JimNPC> jim;
    bn::optional<NPC> npc;

    bn::optional<CompositeSprite> car1;
    bn::optional<CompositeSprite> car2;

    void loadDay1();
    void loadDay2();
    void loadDay3();

public:
    WorkParking(Player& _player,DIRECTION entering_from,GlobalVariables& _global);
    ~WorkParking() override;

    bn::optional<RoomExit> update() override;
};
}

#endif