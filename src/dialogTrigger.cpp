#include "dialogTrigger.h"

namespace game{
DialogTrigger::DialogTrigger(GlobalVariables& _global_var,bn::fixed_rect _box,bool _hold_til_leaving,bool _reusable):
    global_var(_global_var),trigger_box(_box),hold_until_leaving(_hold_til_leaving),is_reuseable(_reusable){
    #ifdef DEBUG_GAME
    createTriggerDebug();
    #endif
}

void DialogTrigger::setPos(bn::fixed_point _pos){
    trigger_box.set_position(_pos);
    #ifdef DEBUG_GAME
    trigger_debug.clear();
    createTriggerDebug();
    #endif
}

bn::fixed_point DialogTrigger::getPos(){
    return trigger_box.position();
}

void DialogTrigger::addDialog(Pair<int,int> dialog){
    dialog_sequence.push_back(dialog);
}

void DialogTrigger::update(bn::fixed_rect player_boundaries){
    if(!active) return;

    if(player_in && hold_until_leaving){
        if(!trigger_box.intersects(player_boundaries)){
            player_in = false;
            if(dialog_sequence.size() >= 1) global_var.getDialogManager().setBottomTextDuration(dialog_sequence[0].second);
            if(!is_reuseable) active = false;
        }
    }else{
        if(trigger_box.intersects(player_boundaries)){
            player_in = true;
            global_var.getDialogManager().setActDialogSequence(dialog_sequence);
            if(hold_until_leaving) global_var.getDialogManager().setBottomTextDuration(-1);
            if(!is_reuseable && !hold_until_leaving) active = false;
        }else player_in = false;
    }
}


#ifdef DEBUG_GAME
void DialogTrigger::createTriggerDebug(){
    bn::sprite_ptr top_left = bn::sprite_items::debug_corner.create_sprite(trigger_box.top_left());
    top_left.set_bg_priority(2);
    top_left.set_z_order(-10);
    {
    auto pal = top_left.palette();
    pal.set_color(1,bn::color(0,0,31));
    }
    bn::sprite_ptr top_right = bn::sprite_items::debug_corner.create_sprite(trigger_box.top_right());
    top_right.set_bg_priority(2);
    top_right.set_z_order(-10);
    top_right.set_horizontal_flip(true);
    {
    auto pal = top_right.palette();
    pal.set_color(1,bn::color(0,0,31));
    }
    bn::sprite_ptr bottom_left = bn::sprite_items::debug_corner.create_sprite(trigger_box.bottom_left());
    bottom_left.set_bg_priority(2);
    bottom_left.set_z_order(-10);
    bottom_left.set_vertical_flip(true);
    {
    auto pal = bottom_left.palette();
    pal.set_color(1,bn::color(0,0,31));
    }
    bn::sprite_ptr bottom_right = bn::sprite_items::debug_corner.create_sprite(trigger_box.bottom_right());
    bottom_right.set_bg_priority(2);
    bottom_right.set_z_order(-10);
    bottom_right.set_horizontal_flip(true);
    bottom_right.set_vertical_flip(true);
    {
    auto pal = bottom_right.palette();
    pal.set_color(1,bn::color(0,0,31));
    }
    trigger_debug.push_back(top_left);
    trigger_debug.push_back(top_right);
    trigger_debug.push_back(bottom_left);
    trigger_debug.push_back(bottom_right);
}
#endif
}