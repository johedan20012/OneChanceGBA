#ifndef HOUSEENTRANCE_H
#define HOUSEENTRANCE_H

#include "bn_sprite_actions.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"

#include "bn_math.h"
#include "bn_vector.h"
#include "bn_unique_ptr.h"

#include "npc.h"
#include "room.h"
#include "timer.h"
#include "compositeSprite.h"
#include "globalVariables.h"

#ifdef DEBUG_GAME
#include "moveable.h"
#endif

namespace game{
class HouseEntrance : public Room{
private:
    static constexpr bn::color car_dark_pal[16] = {
        bn::color(0,0,0),bn::color(0,0,0),
        bn::color(5,7,10),bn::color(2,2,7),bn::color(12,9,0),
        bn::color(3,3,3),bn::color(6,6,6)
    };

    GlobalVariables& global_var;

    CompositeSprite car;
    bn::sprite_ptr cloud;
    bn::fixed cloud_y_dir = 0.07;
    bn::sprite_ptr newspaper;
    bool newspaper_picked_up = false;

    bool newspaper_showed = false;
    bn::optional<bn::regular_bg_ptr> newspaper_bg;
    bn::regular_bg_item newspaper_item;

    bool isExiting;

    bn::vector<bn::optional<CompositeSpriteRotToAction>,3> carRotations;
    bn::fixed rotations = 0;
    bn::optional<CompositeSpritePosToAction> carMovement;

    bn::vector<NPC,4> npcs;
    bn::unique_ptr<Timer> timer;

    #ifdef DEBUG_GAME
    int indx = 0;
    bn::unique_ptr<Moveable<NPC>> mov;
    #endif

    void loadDay2();
    void loadDay3();
    void loadDay4();

    bn::optional<RoomExit> updateDay1_3();
    bn::optional<RoomExit> updateDay4();
public:
    HouseEntrance(Player& _player, DIRECTION _entering_from,GlobalVariables& _global_var);
    ~HouseEntrance() override;

    bn::optional<RoomExit> update() override;
};
}

#endif