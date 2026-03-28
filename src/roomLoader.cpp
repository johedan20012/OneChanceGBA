#include "roomLoader.h"

namespace game{

const bn::string<15> RoomLoader::roomsNames[15] = {
    "house_bedroom",
    "house_hall",
    "house_molly",
    "house_bath",
    "house_entrance",
    "city",
    "work_parking",
    "work_lobby",
    "work_hall",
    "work_lab_door",
    "work_stairs",
    "skip_work",
    "work_lab",
    "day_change",
    ""
};

bn::unique_ptr<Room> RoomLoader::loadRoom(RoomExit room_exit,Player& player,GlobalVariables& _global){
    BN_LOG("Loading room:",room_exit.name);
    if(room_exit.name == roomsNames[0]){ 
        return bn::make_unique<HouseBedroom1>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[1]){
        return bn::make_unique<HouseHall>(player,room_exit.next_in_dir,_global);
    }
    if(room_exit.name == roomsNames[2]){
        return bn::make_unique<HouseBedroom2>(player,room_exit.next_in_dir,_global);
    }
    if(room_exit.name == roomsNames[3]){
        return bn::make_unique<HouseBathroom>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[4]){
        return bn::make_unique<HouseEntrance>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[5]){
        return bn::make_unique<City>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[6]){
        return bn::make_unique<WorkParking>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[7]){
        return bn::make_unique<WorkLobby>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[8]){
        return bn::make_unique<WorkHall>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[9]){
        return bn::make_unique<WorkLabDoor>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[10]){
        return bn::make_unique<WorkStairs>(player,room_exit.next_in_dir);
    }
    if(room_exit.name == roomsNames[11]){
        return bn::make_unique<SkipWork>(player,_global);
    }
    if(room_exit.name == roomsNames[12]){
        return bn::make_unique<WorkLab>(player,_global);
    }
    if(room_exit.name == roomsNames[13]){
        return bn::make_unique<DayChange>(player,_global);
    }
    BN_LOG("Error loading room: ",room_exit.name);
    return bn::make_unique<HouseBedroom1>(player,room_exit.next_in_dir);
}
}