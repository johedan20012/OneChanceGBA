#ifndef HOUSEENTRANCE_H
#define HOUSEENTRANCE_H

#include "bn_regular_bg_items_bg_house_5.h"

#include "bn_sprite_items_car.h"
#include "bn_sprite_actions.h"
#include "bn_value_template_actions.h"

#include "bn_deque.h"

#include "room.h"
#include "compositeSprite.h"

namespace game{
class HouseEntrance : public Room{
private:
    CompositeSprite car;
    bool isExiting;

    bn::vector<bn::optional<CompositeSpriteRotToAction>,3> carRotations;
    bn::fixed rotations = 0;
    bn::optional<CompositeSpritePosToAction> carMovement;
public:
    HouseEntrance(Player& _player, DIRECTION _entering_from);
    virtual ~HouseEntrance() override;

    bn::optional<RoomExit> update() override;
};
}

#endif