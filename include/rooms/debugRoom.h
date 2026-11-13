#ifdef DEBUG_GAME
#ifndef DEBUGROOM_H
#define DEBUGROOM_H

#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "bn_vector.h"

#include "room.h"
#include "globalVariables.h"

namespace game{
class DebugRoom : public Room{
private:
    static constexpr int MAX_OPTIONS = 14;
    static constexpr int MAX_ROOMS = 16;
    static const bn::string<15> roomsNames[MAX_ROOMS];

    GlobalVariables& global_var;

    bn::sprite_ptr cursor;

    bn::vector<bn::sprite_ptr,50> text_sprs;
    bn::sprite_text_generator info_gen;

    unsigned int room_selected = 0;
    int option_selected = 0;
    bool player_lab_coat = true;
    bool player_night_colors = false;
    bool molly_on_players_back = false;

    void display_info();
public:
    DebugRoom(Player& _player, GlobalVariables& _global_var);
    ~DebugRoom();

    bn::optional<RoomExit> update() override;
};
}
#endif
#endif