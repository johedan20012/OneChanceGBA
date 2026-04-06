#ifndef HOUSEENTRANCE_H
#define HOUSEENTRANCE_H

#include "bn_sprite_actions.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"

#include "bn_math.h"

#include "room.h"
#include "moveable.h"
#include "compositeSprite.h"
#include "globalVariables.h"

namespace game{
class HouseEntrance : public Room{
private:
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

    void loadDay2();
public:
    HouseEntrance(Player& _player, DIRECTION _entering_from,GlobalVariables& _global_var);
    ~HouseEntrance() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif