#ifndef CITY_H
#define CITY_H

#include "bn_sprite_ptr.h"

#include "bn_color.h"
#include "bn_vector.h"

#include "room.h"
#include "globalVariables.h"

namespace game{
class City : public Room{
private:
    static constexpr bn::color pal1[16] = {bn::color(0,0,0),bn::color(0,0,0),bn::color(14,19,26),bn::color(0,19,0),bn::color(31,24,1),bn::color(8,8,8),bn::color(15,15,15)};
    static constexpr bn::color pal2[16] = {bn::color(0,0,0),bn::color(0,0,0),bn::color(14,19,26),bn::color(19,0,0),bn::color(31,24,1),bn::color(8,8,8),bn::color(15,15,15)};

    static constexpr bn::fixed y_level_npc[8][8] = 
        {
         {33,33,33,33,32,32,32,32}, //+ 3
         {34,34,34,34,33,33,33,33}, //- 7
         {35,35,35,35,34,34,34,34}, //- 5
         {40,40,40,40,39,39,39,39}, //- 4
         {40,40,40,40,39,39,39,39}, //- 6 
         {41,41,41,41,40,40,40,40}, //+ 1 
         {42,42,42,42,41,41,41,41}, //+ 0
         {42,42,42,42,41,41,41,41}, //+ 2
        };
    static constexpr bn::fixed dir_npc[8] = {0.7,-0.7,-0.7,-0.7,-0.7,0.7,0.7,0.7};

    GlobalVariables& global_var;
    bn::vector<bn::sprite_ptr,10> small_npc;
    bn::vector<bn::sprite_ptr,30> small_npc_nmov;
    bn::vector<bn::sprite_ptr,5> npc_signs;
    int y_level_indx = 1;

    bn::vector<bn::sprite_ptr,4> npc_cars;

    bn::sprite_ptr car;

    void loadDay1_2();
    void loadDay3();

    void updateDay1_2();
    void updateDay3();
    
public:
    City(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var);
    ~City() override {}

    bn::optional<RoomExit> update() override;
};
}
#endif