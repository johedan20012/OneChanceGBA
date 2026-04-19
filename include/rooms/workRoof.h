#ifndef WORKROOF_H
#define WORKROOF_H

#include "bn_unique_ptr.h"

#include "npc.h"
#include "room.h"
#include "timer.h"
#include "compositeSprite.h"
#include "globalVariables.h"

namespace game{
class WorkRoof : public Room{
private:
    enum class STATE{
        NORMAL,
        DIALOG,
        ANIM,
        DARK,
        NEWS
    };

    class Matthew : public NPC{
    private:
        enum class MSTATE{
            LEG_OVER,
            STANDING,
            ARMS,
            LEANING,
            FALLING
        };

        bn::unique_ptr<Timer> timer;
        MSTATE state = MSTATE::LEG_OVER;

        bool jumpStarted = false;
        bool jumpFinished = false;

        bn::fixed degrees_offset = 0;
        bn::fixed radius = 1;
        bn::fixed_point pivot = bn::fixed_point(0,0);
    private:
        void setPivot(bn::fixed_point _pivot);
        void rotateTo(bn::fixed angle);

    public:
        Matthew();
        ~Matthew() = default;

        void update() override;

        void startJump();
        bool jumpfinished();
    };

    static constexpr bn::fixed_point pivot = bn::fixed_point(82,39);

    GlobalVariables& global_var;

    STATE state;
    bn::unique_ptr<Timer> timer;

    bn::unique_ptr<Matthew> matthew;
    CompositeSprite edge;

    bn::optional<NPC> npc;

    void loadDay2();
    void loadDay3();
public:
    WorkRoof(Player& _player,GlobalVariables& _global_var);
    ~WorkRoof();

    bn::optional<RoomExit> update() override;

    bn::optional<RoomExit> updateDay2();
    bn::optional<RoomExit> updateDay3();
};
}

#endif