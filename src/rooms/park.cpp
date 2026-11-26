#include "park.h"

#include "bn_sprite_palette_items_park1_snow_particle.h"

#include "bn_regular_bg_items_bg_park_1.h"
#include "bn_regular_bg_items_bg_park_1b.h"
#include "bn_regular_bg_items_bg_park_2.h"
#include "bn_regular_bg_items_bg_park_2b.h"
#include "bn_regular_bg_items_bg_park_2c.h"
#include "bn_regular_bg_items_bg_graveyard.h"
#include "bn_regular_bg_items_bg_bottom_text_b.h"

#include "snowData.h"

namespace game{
Park::Park(Player& _player,GlobalVariables &_global_var):
Room(bn::regular_bg_items::bg_park_1.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player,_global_var.getDayVariant(_global_var.currentDay())),
global_var(_global_var){
    global_var.setDayChoice(global_var.currentDay(),CHOICE::SKIP_WORK);

    player.setMovementBox(bn::fixed_rect(0,0,720,160));
    player.setPos(-98,44);
    player.setHflip(true);

    exits.push_back(RoomExit("park_2",bn::fixed_rect(120,26,16,64),DIRECTION::LEFT,false));

    if(global_var.currentDay() == 6){
        loadDay6();
    }

    #ifdef DEBUG_GAME
    createExitsDebug();
    #endif
}

Park::~Park(){
    if(molly_dialog != nullptr) delete molly_dialog;
    molly_dialog = nullptr;

    player.carryMolly(false);
}

void Park::loadDay6(){
    // A,I variant
    bg->set_item(bn::regular_bg_items::bg_park_1b);
    snow_particles = bn::make_unique<SnowParticles>(global_var,player,PARK1_IN_AREAS,PARK1_OUT_AREAS,bn::sprite_palette_items::park1_snow_particle,true);    
    player.setMovementBox(bn::fixed_rect(46,0,300,160));

    switch(Room::variant){
    case 2:
    case 3:
    case 4:
    case 9:
    case 10:
    case 11:
    case 12:
    default: // A,B,C,D,I,J,K,L variant
        player.carryMolly(true);
        break;
    }
}

void Park::load2Day5(){
    second_room = true;
    bg->set_item(bn::regular_bg_items::bg_park_2);
    player.setPos(-98,44);
    molly_dialog = new DialogTrigger(global_var,bn::fixed_rect(0,32,28,64),false,false);
    molly_dialog->addDialog(Pair<int,int>(47,226));
    global_var.getDialogManager().setBg(bn::regular_bg_items::bg_bottom_text_b.create_bg(8,48));
}

void Park::load2Day6(){
    exits.clear();
    global_var.saveEndType(1);
    second_room = true;
    bg->set_item(bn::regular_bg_items::bg_park_2b);
    player.setPos(-98,44);
    snow_particles = bn::make_unique<SnowParticles>(global_var,player,PARK2_IN_AREAS,PARK2_OUT_AREAS,bn::sprite_palette_items::park1_snow_particle,true);    
}

bn::optional<RoomExit> Park::update2Day5(){
    player.update();
    if(molly_dialog != nullptr){
        molly_dialog->update(player.boundaries());
        if(molly_dialog->wasTriggered() && player.getPos().x() <= bn::fixed{-139}){
            global_var.getDialogManager().resetBottomText();
            delete molly_dialog;
            molly_dialog = new DialogTrigger(global_var,bn::fixed_rect(0,32,28,64),false,false);
            molly_dialog->addDialog(Pair<int,int>(47,226));
            return bn::nullopt;
        }
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
    return bn::nullopt;
}

bn::optional<RoomExit> Park::update2Day6(){
    player.update();

    switch(second_room_state){
    case 0:
        player.update();

        if(player.getPos().x() >= bn::fixed{38}){
            second_room_state = 1;
            john_animation = bn::make_unique<JohnSitPark>(bn::fixed_point{39,44});
            player.setVisible(false);
        }
        break;
    case 1:
        if(john_animation){
            john_animation->update();
            if(john_animation->isFinished()){
                second_room_state = 2;
                john_animation.reset();
                bg->set_item(bn::regular_bg_items::bg_park_2c);
            }
        }
    default:
        break;
    }

    return bn::nullopt;
}

bn::optional<RoomExit> Park::update(){
    if(snow_particles) snow_particles->update();

    if(second_room){
        if(global_var.currentDay() == 5) return update2Day5();
        return update2Day6();
    }
    // First room
    player.update();

    if(global_var.currentDay() == 6){
        switch(Room::variant){
        case 2:
        case 3:
        case 4:
        case 9:
        case 10:
        case 11:
        case 12:
        default: // A,B,C,D,I,J,K,L variant
            if(bn::keypad::left_pressed() || bn::keypad::right_pressed()) player.carryMolly(false);
            break;
        }
    }

    auto exit = Room::checkExits();
    if(exit){
        if(global_var.currentDay() == 5) load2Day5();
        else load2Day6();
    }    
    return bn::nullopt;
}
}