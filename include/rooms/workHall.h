#ifndef WORKHALL_H
#define WORKHALL_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_actions.h"

#include "bn_optional.h"
#include "bn_unique_ptr.h"

#include "jimStab.h"
#include "jimStabFail.h"

#include "npc.h"
#include "room.h"
#include "timer.h"
#include "globalVariables.h"

#ifdef DEBUG_GAME
#include "moveable.h"
#endif

namespace game{
class WorkHall : public Room{
private:
    class Jim : public NPC{
    private:
        enum class STATE{
            IDLE,
            THREATENING,
            SPEAKING,
            CHARGING,
            ATTACKING
        };

        static constexpr bn::fixed MOV_SPEED = 0.75;
        static constexpr bn::fixed_point KNIFE_OFFSETS[3] = {
            bn::fixed_point(17,13), //90° Holding normally it with right arm 
            bn::fixed_point(-13,5), //0° Holding with right arm lifted
            bn::fixed_point(-23,-5), //270° Holding with right arm lifted and pointed towards Jim
        };

        STATE state = STATE::IDLE;
        bn::sprite_ptr knife;
        bn::unique_ptr<Timer> timer;
        bn::unique_ptr<Timer> anim_timer;

        bn::unique_ptr<Moveable<bn::sprite_ptr>> mov1;
        bn::unique_ptr<Moveable<NPC>> mov2;
        bool selected = false;
        int rotation = 0;
        int g_indx = 0;
        bool move = true;
    public:
        Jim();
        ~Jim() override {};

        bn::fixed_point position();

        bool isThreatening();
        bool isCharging();

        void update() override;

        void initiateTalk(GlobalVariables& global_var);
        void initiateCharging();
    };

    enum class ROOMSTATE{
        JOHN_ENTERING,
        JIM_YAPPING,
        JIM_CHARGING,
        JIM_ATTACKING,
        ATTACK_CONCLUDED
    };

    GlobalVariables& global_var;

    bn::vector<NPC,4> npcs;

    bn::optional<bn::sprite_ptr> walking_dude;
    bn::optional<bn::sprite_move_to_action> walk_mov;
    bn::optional<bn::sprite_animate_action<2>> walk_anim;

    bn::sprite_ptr small_cabinet;

    bn::unique_ptr<Jim> jim;

    bn::unique_ptr<Timer> timer;
    ROOMSTATE state = ROOMSTATE::JOHN_ENTERING;
    bn::unique_ptr<Animation> day5_animation;

    #ifdef DEBUG_GAME
    bn::unique_ptr<Moveable<NPC>> mov;
    #endif 

    void loadDay1(DIRECTION entering_from);
    void loadDay2();
    void loadDay3(DIRECTION entering_from);
    void loadDay4();
    void loadDay5();

    bn::optional<RoomExit> updateDay5();
public:
    WorkHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~WorkHall() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif