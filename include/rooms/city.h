#ifndef CITY_H
#define CITY_H

#include "bn_regular_bg_items_bg_city.h"

#include "bn_sprite_ptr.h"
#include "bn_sprite_items_car_small.h"

#include "room.h"

namespace game{
class City : public Room{
private:
    bn::sprite_ptr car;

public:
    City(Player& _player,DIRECTION entering_from);
    virtual ~City() override;

    bn::optional<RoomExit> update() override;
};
}
#endif