#ifndef ROOMLOADER_H
#define ROOMLOADER_H

#include "bn_unique_ptr.h"

#include "rooms/houseBedroom1.h"
#include "rooms/houseBedroom2.h"
#include "rooms/houseBathroom.h"
#include "rooms/houseHall.h"
#include "rooms/houseEntrance.h"
#include "rooms/city.h"
#include "rooms/workParking.h"
#include "rooms/workLobby.h"
#include "rooms/workHall.h"
#include "rooms/workLabDoor.h"
#include "rooms/workStairs.h"
#include "rooms/skipWork.h"
#include "rooms/workLab.h"
#include "player.h"

namespace game{
class RoomLoader{
private:
    static const bn::string<15> roomsNames[15];

public:
    static bn::unique_ptr<Room> loadRoom(RoomExit room_exit, Player& player);
};
}

#endif