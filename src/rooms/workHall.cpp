#include "workHall.h"

#include "bn_sprite_items_knife.h"
#include "bn_sprite_items_jim_day5.h"
#include "bn_sprite_items_work_people.h"
#include "bn_sprite_items_walking_dude.h"
#include "bn_sprite_items_small_cabinet.h"
#include "bn_sprite_items_bruce_walking.h"

#include "bn_regular_bg_items_bg_work_hall.h"
#include "bn_regular_bg_items_bg_work_hall_b.h"

#include "bn_math.h"

namespace game{

WorkHall::Jim::Jim():
    NPC(bn::sprite_items::jim_day5.create_sprite(62,21,0)),
    state(STATE::SPEAKING),
    knife(bn::sprite_items::knife.create_sprite(-16,6)){

    knife.set_position(sprite.position()+KNIFE_OFFSETS[0]);
    knife.set_rotation_angle(90);

    mov1 = bn::make_unique<Moveable<bn::sprite_ptr>>(knife);
    mov2 = bn::make_unique<Moveable<NPC>>(*this);
}

bn::fixed_point WorkHall::Jim::position(){
    return NPC::position();
}

bool WorkHall::Jim::isThreatening(){
    return state == STATE::THREATENING;
}

bool WorkHall::Jim::isCharging(){
    return state == STATE::CHARGING;
}

void WorkHall::Jim::update(){

    if(bn::keypad::start_pressed()){
        BN_LOG("STATE");
        switch(state){
        case STATE::IDLE:
            BN_LOG("State IDLE");
            break;
        case STATE::THREATENING:
            BN_LOG("State THREATENING");
            break;
        case STATE::SPEAKING:
            BN_LOG("State SPEAKING");
            break;
        case STATE::CHARGING:
            BN_LOG("State CHARGING");
            break;
        default://case STATE::ATTACKING:
            BN_LOG("State ATTACKING");
            break;
        }
    }

    switch(state){
    case STATE::THREATENING:
        if(timer && timer->elapsedFrames() >= 49){
            state = STATE::SPEAKING;

            sprite.set_tiles(bn::sprite_items::jim_day5.tiles_item(),0);
            knife.set_position(sprite.position()+KNIFE_OFFSETS[0]);
            knife.set_rotation_angle(90);

            timer.reset();
        }
        break;

    case STATE::SPEAKING:
        break;

    case STATE::CHARGING:
        if(anim_timer){
            if(anim_timer->elapsedFrames() == 7){
                sprite.set_tiles(bn::sprite_items::jim_day5.tiles_item(),2);
            }else if(anim_timer->elapsedFrames() == 12){
                sprite.set_tiles(bn::sprite_items::jim_day5.tiles_item(),1);
                anim_timer = bn::make_unique<Timer>();
            }
        }
        if(bn::keypad::select_pressed()) move = false;
        if(move) sprite.set_position(sprite.position()+bn::fixed_point(-MOV_SPEED,0.0));
        knife.set_position(sprite.position()+KNIFE_OFFSETS[2]);

        if(bn::keypad::start_pressed()) BN_LOG("Jim pos",sprite.x(),",",sprite.y());
        break;

    case STATE::ATTACKING:
        break;

    default: // IDLE
        break;
    }
}

void WorkHall::Jim::initiateTalk(GlobalVariables& global_var){
    dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,200,60),false,false);
    dialog->addDialog(Pair<int,int>(43,82));
    dialog->addDialog(Pair<int,int>(44,194));
    dialog->addDialog(Pair<int,int>(45,110));

    sprite.set_tiles(bn::sprite_items::jim_day5.tiles_item(),1);
    knife.set_rotation_angle(0);
    knife.set_position(sprite.position()+KNIFE_OFFSETS[1]);

    timer = bn::make_unique<Timer>();

    state = STATE::THREATENING;
}

void WorkHall::Jim::initiateCharging(){
    anim_timer = bn::make_unique<Timer>();

    knife.set_rotation_angle(270);
    sprite.set_tiles(bn::sprite_items::jim_day5.tiles_item(),1);
    knife.set_position(sprite.position()+KNIFE_OFFSETS[2]);
    knife.set_horizontal_flip(true);

    state = STATE::CHARGING;
}

WorkHall::WorkHall(Player& _player,DIRECTION entering_from,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_work_hall.create_bg(8,48),bn::fixed_rect(0,1,240,118),_player),
    global_var(_global_var),
    small_cabinet(bn::sprite_items::small_cabinet.create_sprite(-34,27)){
    
    player.setMovementBox(bn::fixed_rect(0,0,260,160));

    switch (entering_from){
        case DIRECTION::LEFT:
            player.setPos(-106,28);
            break;
        case DIRECTION::RIGHT:
            player.setPos(106,28);
            break;
        default:
            player.setPos(0,0);
            break;
    }

    exits.push_back(RoomExit("work_lobby",bn::fixed_rect(-128,20,7,64),DIRECTION::RIGHT,false));
    exits.push_back(RoomExit("work_lab_door",bn::fixed_rect(128,20,7,64),DIRECTION::LEFT,false));

    switch(global_var.currentDay()){
        case 2:
            loadDay2();
            break;
        case 3:
            loadDay3(entering_from);
            break;
        case 4:
            loadDay4();
            break;
        case 5:
            loadDay5();
            break;
        default:
            loadDay1(entering_from);
            break;
    }

    #ifdef DEBUG_GAME
    Room::createExitsDebug();
    #endif
}

void WorkHall::loadDay1(DIRECTION entering_from){
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(-63,17,8)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(-43,17,9)));

    walking_dude = bn::sprite_items::walking_dude.create_sprite(140,20,0);
    walking_dude->set_bg_priority(2);
    walking_dude->set_z_order(2);

    {
        DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,30,64),false);
        dialog->addDialog(Pair<int,int>(5,180));
        npcs[1].addDialog(dialog);
    }

    if(entering_from == DIRECTION::LEFT){
        walk_mov = bn::sprite_move_to_action(walking_dude.value(),280,bn::fixed_point(-140,20));
        walk_anim = bn::create_sprite_animate_action_forever(walking_dude.value(),6,bn::sprite_items::walking_dude.tiles_item(),0,1);    
    }

    exits.push_back(RoomExit("skip_work",bn::fixed_rect(-45,20,19,64),DIRECTION::DOOR1,true));
    exits.back().info = "Skip work";
}

void WorkHall::loadDay2(){
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(-63,17,8)));
    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(-43,17,9)));

    npcs[0].set_position(bn::fixed_point(-49,17));
    npcs[1].set_position(bn::fixed_point(-29,17));

    npcs.push_back(bn::sprite_items::work_people.create_sprite(-62,21,5));
    npcs.back().setHorizontalFlip(true);
}

void WorkHall::loadDay3(DIRECTION entering_from){
    small_cabinet.set_rotation_angle(90);
    small_cabinet.set_position(-36,26);

    if(global_var.roofCheckedDay3() && entering_from == DIRECTION::RIGHT){
        walking_dude = bn::sprite_items::bruce_walking.create_sprite(-140,20);
        walking_dude->set_horizontal_flip(true);
        walking_dude->set_bg_priority(2);
        walking_dude->set_z_order(2);

        walk_mov = bn::sprite_move_to_action(walking_dude.value(),280,bn::fixed_point(140,20));
        walk_anim = bn::create_sprite_animate_action_forever(walking_dude.value(),6,bn::sprite_items::bruce_walking.tiles_item(),0,1);    
    }
}

void WorkHall::loadDay4(){
    small_cabinet.set_rotation_angle(90);
    small_cabinet.set_position(-36,26);

    npcs.push_back(NPC(bn::sprite_items::work_people.create_sprite(-5,16,9)));
    if(!global_var.hasVisitedWorkHall()){
        DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(-13,0,24,64),false,false);
        dialog->addDialog(Pair<int,int>(40,200));
        dialog->addDialog(Pair<int,int>(41,296));
        dialog->addDialog(Pair<int,int>(42,176));
        npcs[0].addDialog(dialog);
    }
    global_var.setVisitedWorkHall(!global_var.hasVisitedWorkHall());

    exits.push_back(RoomExit("skip_work",bn::fixed_rect(1,23,58,64),DIRECTION::RIGHT,true));
    exits.back().info = "Skip work";
}

void WorkHall::loadDay5(){
    player.setMovementBox(bn::fixed_rect(0,0,205,160));

    small_cabinet.set_rotation_angle(90);
    small_cabinet.set_position(-36,26);

    bg->set_item(bn::regular_bg_items::bg_work_hall_b); 

    player.setPos(-99,28);

    jim = bn::make_unique<Jim>();
    timer = bn::make_unique<Timer>();

    exits.clear();
}

bn::optional<RoomExit> WorkHall::updateDay5(){
    if(jim) jim->update();

    switch (state){
    case ROOMSTATE::JIM_YAPPING:
        player.update(!jim->isThreatening());

        if(!global_var.getDialogManager().hasADialogSequence()){
            state = ROOMSTATE::JIM_CHARGING;
            jim->initiateCharging();
            player.setMovementBox(bn::fixed_rect(0,0,215,160));
        }

        break;
    case ROOMSTATE::JIM_CHARGING:
        player.update();

        if(exits.size() == 0 && bn::abs(player.getPos().x() - jim->position().x()) <= 66){
            exits.push_back(RoomExit("defend",bn::fixed_rect(0,0,240,64),DIRECTION::LEFT,true));
            exits[0].info = "Defend";
        }

        if(exits.size() > 0){
            auto exit = Room::checkExits();
            if(exit){
                state = ROOMSTATE::JIM_ATTACKING;
                player.setVisible(false);
                day5_animation = bn::make_unique<JimStabFail>(jim->position());               
                global_var.setDayChoice(5,CHOICE::DEFEND);
                jim.reset();
                exits.clear();
                Room::clearExitsInfo();
                break;
            }
        }

        if(bn::abs(player.getPos().x() - jim->position().x()) <= 34){
            state = ROOMSTATE::JIM_ATTACKING;
            player.setVisible(false);
            day5_animation = bn::make_unique<JimStab>(jim->position());
            global_var.setDayChoice(5,CHOICE::NO_DEFEND);
            jim.reset();
            exits.clear();
            Room::clearExitsInfo();
        }

        break;
    case ROOMSTATE::JIM_ATTACKING:        
        if(day5_animation){
            day5_animation->update();

            if(day5_animation->isFinished()){
                state = ROOMSTATE::ATTACK_CONCLUDED;
                if(global_var.dayChoice(5) == CHOICE::DEFEND) return RoomExit("work_lab",DIRECTION::DOOR1);
            }
        }

        break;
    case ROOMSTATE::ATTACK_CONCLUDED:
        break;
    default: // JOHN_ENTERING
        player.update();
        
        if(timer && timer->elapsedFrames() >= 20){
            state = ROOMSTATE::JIM_YAPPING;

            jim->initiateTalk(global_var);
            jim->checkDialog(player.boundaries());

            timer.reset();
        }
        break;
    }

    Room::updateExitsInfo();

    return bn::nullopt;
}

bn::optional<RoomExit> WorkHall::update(){

    #ifdef DEBUG_GAME
    if(mov) mov->update();
    #endif

    if(global_var.currentDay() == 5) return updateDay5();

    if(walk_anim) walk_anim->update();
    if(walk_mov){
        walk_mov->update();
        if(walk_mov->done()){
            walk_anim.reset();
            walk_mov.reset();
        }
    }

    player.update(global_var.currentDay() == 4 && global_var.getDialogManager().hasADialogSequence());

    if(global_var.currentDay() == 4 && npcs.size() > 0){
        npcs[0].lookAt(player.getPos(),true);
        npcs[0].checkDialog(player.boundaries());    
    }

    if(npcs.size() >= 2){ 
        npcs[1].lookAt(player.getPos(),true);
        npcs[1].checkDialog(player.boundaries());
    }

    if(npcs.size() >= 3) npcs[2].lookAt(player.getPos(),true);

    Room::updateExitsInfo();
    Room::update();

    return checkExits();
}

}