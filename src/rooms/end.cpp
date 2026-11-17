#include "end.h"

#include "bn_sprite_palette_items_roof_snow_particle.h"

#include "bn_regular_bg_items_bg_end_4.h" // Ends: 4
#include "bn_regular_bg_items_bg_work_roof_c.h" // Ends: 8

#include "bn_assert.h"

#include "snowData.h"

namespace game{
End::End(Player& _player,GlobalVariables& _global_var): 
Room(bn::regular_bg_items::bg_end_4.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),global_var(_global_var){
    
    player.setVisible(false);
    
    BN_ASSERT(global_var.endType() != bn::nullopt, "No end saved");
    switch (global_var.endType().value()){
    case 8:
        bg->set_item(bn::regular_bg_items::bg_work_roof_c);
        snow_particles = bn::make_unique<SnowParticles>(global_var,player,ROOF_IN_AREAS,ROOF_OUT_AREAS,bn::sprite_palette_items::roof_snow_particle,false);
        break;
    
    default:
        break;
    }
}

bn::optional<RoomExit> End::update(){
    if(snow_particles) snow_particles->update();

    return bn::nullopt;
}
}