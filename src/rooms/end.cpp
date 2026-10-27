#include "end.h"

#include "bn_regular_bg_items_bg_end_4.h"

namespace game{
End::End(Player& _player,GlobalVariables& _global_var): 
Room(bn::regular_bg_items::bg_end_4.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),global_var(_global_var){
    
    player.setVisible(false);
    
    switch (global_var.endType().value()){
    case 4:
        break;
    
    default:
        break;
    }
}

bn::optional<RoomExit> End::update(){
    return bn::nullopt;
}
}