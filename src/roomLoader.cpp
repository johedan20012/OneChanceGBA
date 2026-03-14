#include "roomLoader.h"

namespace game{

const bn::string<15> RoomLoader::roomsNames[2] = {
    "house_bedroom",
    "house_hall" 
};

bn::unique_ptr<Room> RoomLoader::loadRoom(RoomExit room_exit,Player& player){
    if(room_exit.name == roomsNames[0]){ 
        return bn::make_unique<HouseBedroom1>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[1]){
        return bn::make_unique<HouseHall>(player,room_exit.next_in_dir);
    }
    return bn::unique_ptr<Room>();
}
}