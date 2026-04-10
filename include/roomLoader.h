#ifndef ROOMLOADER_H
#define ROOMLOADER_H

#include "bn_unique_ptr.h"

#include "room.h"
#include "player.h"
#include "globalVariables.h"

namespace game{
class RoomLoader{
private:
    static const bn::string<15> roomsNames[15];

public:
    static bn::unique_ptr<Room> loadRoom(RoomExit room_exit, Player& player,GlobalVariables& _global);
};
}

#endif