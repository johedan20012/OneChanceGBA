#ifndef HOUSEENTRANCE_H
#define HOUSEENTRANCE_H

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_bg_house_5.h"
#include "bn_regular_bg_items_bg_newspaper1.h"

#include "bn_sprite_items_cloud.h"
#include "bn_sprite_items_newspaper.h"
#include "bn_sprite_items_car.h"
#include "bn_sprite_actions.h"

#include "bn_math.h"

#include "room.h"
#include "compositeSprite.h"
#include "globalVariables.h"
#include "moveable.h"

namespace game{
class HouseEntrance : public Room{
private:
    CompositeSprite car;
    bn::sprite_ptr cloud;
    bn::fixed cloud_y_dir = 0.07;
    bn::sprite_ptr newspaper;
    bool newspaper_picked_up = false;

    bool newspaper_showed = false;
    bn::optional<bn::regular_bg_ptr> newspaper_bg;

    bool isExiting;

    bn::vector<bn::optional<CompositeSpriteRotToAction>,3> carRotations;
    bn::fixed rotations = 0;
    bn::optional<CompositeSpritePosToAction> carMovement;
public:
    HouseEntrance(Player& _player, DIRECTION _entering_from,GlobalVariables& _global_var);
    ~HouseEntrance() override {}

    bn::optional<RoomExit> update() override;
};
}

#endif