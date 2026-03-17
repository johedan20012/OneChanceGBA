#include "roomLoader.h"

namespace game{

const bn::string<15> RoomLoader::roomsNames[12] = {
    "house_bedroom",
    "house_hall",
    "house_molly",
    "house_bath",
    "house_entrance",
    "",
    "",
    "",
    "",
    "",
    "",
    "" 
};

bn::unique_ptr<Room> RoomLoader::loadRoom(RoomExit room_exit,Player& player){
    BN_LOG("Loading room:",room_exit.name);
    if(room_exit.name == roomsNames[0]){ 
        return bn::make_unique<HouseBedroom1>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[1]){
        return bn::make_unique<HouseHall>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[2]){
        return bn::make_unique<HouseBedroom2>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[3]){
        return bn::make_unique<HouseBathroom>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[4]){
        return bn::make_unique<HouseEntrance>(player,room_exit.next_in_dir);
    }
    return bn::unique_ptr<Room>();
}
}