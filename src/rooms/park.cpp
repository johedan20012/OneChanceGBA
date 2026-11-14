#include "park.h"

#include "bn_regular_bg_items_bg_park_1.h"
#include "bn_regular_bg_items_bg_park_2.h"
#include "bn_regular_bg_items_bg_graveyard.h"
#include "bn_regular_bg_items_bg_bottom_text_b.h"

namespace game{
Park::Park(Player& _player,GlobalVariables &_global_var):
Room(bn::regular_bg_items::bg_park_1.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
global_var(_global_var){
    global_var.setDayChoice(global_var.currentDay(),CHOICE::SKIP_WORK);

    player.setMovementBox(bn::fixed_rect(0,0,720,160));
    player.setPos(-98,44);
    player.setHflip(true);

    exits.push_back(RoomExit("park_2",bn::fixed_rect(120,26,16,64),DIRECTION::LEFT,false));

    #ifdef DEBUG_GAME
    createExitsDebug();
    #endif
}

Park::~Park(){
    if(molly_dialog != nullptr) delete molly_dialog;
    molly_dialog = nullptr;

    player.carryMolly(false);
}

bn::optional<RoomExit> Park::update(){
    player.update();
    
    if(second_room){
        if(molly_dialog != nullptr){
            molly_dialog->update(player.boundaries());
            if(molly_dialog->wasTriggered() && !global_var.getDialogManager().hasADialogSequence()){
                delete molly_dialog;
                molly_dialog = nullptr;
                timer = bn::make_unique<Timer>();
                player.setVisible(false);
                bg->set_visible(false);
                bg_paper->set_visible(false);
                global_var.getDialogManager().resetBg();
            }
            return bn::nullopt;
        }

        if(showing_graveyard){
            if(timer->elapsedFrames() >= 284) return RoomExit("day_change",DIRECTION::LEFT);
            return bn::nullopt;
        }

        if(timer && timer->elapsedFrames() >= 40){
            timer.reset();
            timer = bn::make_unique<Timer>();
            showing_graveyard = true;
            bg->set_item(bn::regular_bg_items::bg_graveyard);
            bg->set_visible(true);
            bg_paper->set_visible(true);
        }
    }else{
        auto exit = Room::checkExits();
        if(exit){
            second_room = true;
            bg->set_item(bn::regular_bg_items::bg_park_2);
            player.setPos(-98,44);
            molly_dialog = new DialogTrigger(global_var,bn::fixed_rect(0,32,28,64),false,false);
            molly_dialog->addDialog(Pair<int,int>(47,226));
            global_var.getDialogManager().setBg(bn::regular_bg_items::bg_bottom_text_b.create_bg(8,48));
        }
    }    
    return bn::nullopt;
}
}