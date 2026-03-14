#include "roomLoader.h"

namespace game{

const bn::string<15> RoomLoader::roomsNames[2] = {
    "house_bedroom",
    "house_hall" 
};

bn::unique_ptr<Room> RoomLoader::loadRoom(const bn::string<15> &room_name,Player& player){
    if(room_name == roomsNames[0]){ 
        return bn::make_unique<HouseBedroom1>(player);
    }
    if(room_name == roomsNames[1]){
        return bn::make_unique<HouseHall>(player);
    }
    return bn::unique_ptr<Room>();
}
}