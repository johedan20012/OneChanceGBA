#include "workRoof.h"

#include "bn_sprite_items_matthew.h"
#include "bn_sprite_affine_mat_ptr.h"
#include "bn_sprite_items_roof_edge.h"
#include "bn_sprite_items_work_people_b.h"

#include "bn_regular_bg_items_bg_work_roof.h"
#include "bn_regular_bg_items_bg_conference.h"
#include "bn_regular_bg_items_bg_bottom_text_b.h"

#include "bn_math.h"

#include "bn_log.h"

namespace game{
WorkRoof::Matthew::Matthew():
    NPC(bn::sprite_items::matthew.create_sprite(82,18,0)){}

void WorkRoof::Matthew::update(){
    switch(state){
    case MSTATE::STANDING:
        if(timer && timer->elapsedFrames() >= 37){
            state = MSTATE::ARMS;
            sprite.set_tiles(bn::sprite_items::matthew.tiles_item().create_tiles(2));
            timer = bn::make_unique<Timer>();
            BN_LOG("Change Matthew to arms");
        }
        break;
    case MSTATE::ARMS:
        if(timer && timer->elapsedFrames() >= 36){
            state = MSTATE::LEANING;
            timer = bn::make_unique<Timer>();
            setPivot(bn::fixed_point(84,39));
            BN_LOG("Change Matthew to leaning");
        }
        break;
    case MSTATE::LEANING:
        rotateTo(sprite.rotation_angle()-0.6666);

        if(timer && timer->elapsedFrames() >= 30){
            state = MSTATE::FALLING;
            sprite.set_tiles(bn::sprite_items::matthew.tiles_item().create_tiles(3));
            setPivot(bn::fixed_point(76,60));
            timer = bn::make_unique<Timer>();
            BN_LOG("Change Matthew to falling");
        }
        break;
    case MSTATE::FALLING:
        rotateTo(sprite.rotation_angle()-1);
        if(timer && timer->elapsedFrames() == 20){
            setPivot(bn::fixed_point(-120,-80));
        }

        if(timer && timer->elapsedFrames() >= 50) sprite.set_visible(false);
        if(timer && timer->elapsedFrames() >= 141){
            state = MSTATE::LEG_OVER;
            sprite.set_tiles(bn::sprite_items::matthew.tiles_item().create_tiles(3));
            timer.reset();
            jumpFinished = true;
            BN_LOG("Change Matthew to leg over");
        }
        break;
    default: //LEG_OVER
        if(timer && timer->elapsedFrames() >= 14){
            state = MSTATE::STANDING;
            sprite.set_tiles(bn::sprite_items::matthew.tiles_item().create_tiles(0));
            sprite.set_position(84,7); // -11y - 2x
            timer = bn::make_unique<Timer>();
            BN_LOG("Change Matthew to standing");
        }
        break;
    }

}

void WorkRoof::Matthew::setPivot(bn::fixed_point _pivot){
    bn::fixed_point local_coords = sprite.position() - _pivot;
    pivot = _pivot;
    degrees_offset = bn::safe_degrees_angle(bn::degrees_atan2(local_coords.x().integer(),local_coords.y().integer())-90);    
    radius = bn::sqrt((local_coords.x() * local_coords.x()) + (local_coords.y() * local_coords.y()));
}

void WorkRoof::Matthew::rotateTo(bn::fixed angle){
    bn::fixed true_angle = bn::safe_degrees_angle(angle + degrees_offset);

    sprite.set_rotation_angle(bn::safe_degrees_angle(angle));
        
    bn::fixed x =  pivot.x() + bn::degrees_cos(true_angle)*radius;
    bn::fixed y =  pivot.y() - (bn::degrees_sin(true_angle)*radius);// minus cause y-axis is flipped

    sprite.set_position(x,y);
}

void WorkRoof::Matthew::startJump(){
    jumpStarted = true;
    sprite.set_tiles(bn::sprite_items::matthew.tiles_item().create_tiles(1));
    timer = bn::make_unique<Timer>();
    state = MSTATE::LEG_OVER;
}

bool WorkRoof::Matthew::jumpfinished(){
    return jumpFinished;
}

WorkRoof::WorkRoof(Player& _player,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_work_roof.create_bg(8,48),bn::fixed_rect(0,0,280,160),_player),
    global_var(_global_var),state(STATE::NORMAL),edge(){

    player.setPos(-98,25);

    edge.addSprite(bn::sprite_items::roof_edge.create_sprite(16,-32,0));
    edge.addSprite(bn::sprite_items::roof_edge.create_sprite(0,0,1));
    edge.addSprite(bn::sprite_items::roof_edge.create_sprite(-32,16,2));
    edge.set_position(bn::fixed_point(87,48));

    global_var.getDialogManager().resetBottomText();
    global_var.getDialogManager().setBg(bn::regular_bg_items::bg_bottom_text_b.create_bg(8,48));

    switch (global_var.currentDay()){
    case 3:
        loadDay3();
        break;
    default:    // Day 1,2
        loadDay2();
        break;
    }
}

WorkRoof::~WorkRoof(){
    global_var.getDialogManager().resetBg();
}

void WorkRoof::loadDay2(){
    matthew = bn::make_unique<Matthew>();

    {
    DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,50,64),false,false);
    dialog->addDialog(Pair<int,int>(16,92));
    dialog->addDialog(Pair<int,int>(17,157));
    dialog->addDialog(Pair<int,int>(18,167));
    dialog->addDialog(Pair<int,int>(19,133));
    dialog->addDialog(Pair<int,int>(20,126));
    matthew->addDialog(dialog);
    }

    matthew->setHorizontalFlip(true);
}

void WorkRoof::loadDay3(){
    player.setMovementBox(bn::fixed_rect(-17,0,173,160));

    npc = bn::sprite_items::work_people_b.create_sprite(0,13);

    {
    DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,40,64),false,false);
    dialog->addDialog(Pair<int,int>(28,152));
    dialog->addDialog(Pair<int,int>(29,168));
    dialog->addDialog(Pair<int,int>(30,156));
    npc->addDialog(dialog);
    }

    edge.setZOrder(-1);
}

bn::optional<RoomExit> WorkRoof::update(){
    player.update(state != STATE::NORMAL);

    Room::update();

    switch (global_var.currentDay()){
    case 3:
        return updateDay3();
    case 2:
    default: // Day 1 just for the lol's XD
        return updateDay2();
    }
}

bn::optional<RoomExit> WorkRoof::updateDay2(){
    switch (state){
    case STATE::DIALOG:
        if(timer == nullptr && !global_var.getDialogManager().hasADialogSequence()){
            timer = bn::make_unique<Timer>();
            matthew->setHorizontalFlip(true);
        }
        if(timer && timer->elapsedFrames() >= 35){
            state = STATE::ANIM;
            edge.setVisibility(false);
            timer.reset();
            matthew->startJump();
            BN_LOG("Change state to ANIM");
        }
        break;

    case STATE::ANIM:
        matthew->update();
        if(matthew->jumpfinished()){
            state = STATE::DARK;
            timer = bn::make_unique<Timer>();
            player.setVisible(false);
            bg_paper->set_visible(false);
            bg->set_visible(false);
            BN_LOG("Change state to dark");
        }
        break;
    
    case STATE::DARK:
        if(timer && timer->elapsedFrames() >= 90){
            state = STATE::NEWS;
            timer = bn::make_unique<Timer>();
            bg_paper.reset();
            bg->set_visible(true); // Change background
            bg = bn::regular_bg_items::bg_conference.create_bg(8,48);
            BN_LOG("Change state to news");
        }
        break;

    case STATE::NEWS:
        if(timer && timer->elapsedFrames() >= 230){
            state = STATE::NORMAL;
            timer.reset();
            global_var.setDayChoice(global_var.currentDay(),CHOICE::WORK);
            BN_LOG("Going to day change from roof");
            return RoomExit("day_change",DIRECTION::DOOR1);
        }
        break;
    
    default: //Normal
        matthew->checkDialog(player.boundaries());

        if(global_var.getDialogManager().hasADialogSequence()){
            state = STATE::DIALOG;
            matthew->setHorizontalFlip(false);
            BN_LOG("Change state to DIALOG");
        }
        break;
    }
    return bn::nullopt;
}

bn::optional<RoomExit> WorkRoof::updateDay3(){
    switch (state){
    case STATE::DIALOG:
        if(!global_var.getDialogManager().hasADialogSequence()){
            state = STATE::NORMAL; 
            exits.push_back(RoomExit("work_stairs",bn::fixed_rect(-120,23,40,64),DIRECTION::RIGHT,false));

            #ifdef DEBUG_GAME
            Room::createExitsDebug();
            #endif
        }
        break;
    default:
        if(global_var.getDialogManager().hasADialogSequence()) state = STATE::DIALOG;

        npc->checkDialog(player.boundaries());
        npc->lookAt(player.getPos(),true);

        auto exit = Room::checkExits();
        if(exit){
            global_var.setRoofCheckedDay3(true);
            return exit;
        }
        break;
    }

    return bn::nullopt;
}
}