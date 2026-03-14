#ifndef ROOMLOADER_H
#define ROOMLOADER_H

#include "bn_unique_ptr.h"

#include "rooms/houseBedroom1.h"
#include "rooms/houseHall.h"
#include "player.h"

namespace game{
class RoomLoader{
private:
    static const bn::string<15> roomsNames[2];

public:
    static bn::unique_ptr<Room> loadRoom(RoomExit room_exit, Player& player);
};
}

#endif