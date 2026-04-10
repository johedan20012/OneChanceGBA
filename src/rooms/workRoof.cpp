#include "workRoof.h"

#include "bn_sprite_items_matthew.h"
#include "bn_sprite_affine_mat_ptr.h"
#include "bn_sprite_items_roof_edge.h"

#include "bn_regular_bg_items_bg_work_roof.h"
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
            BN_LOG("Change Matthew to leaning");
        }
        break;
    case MSTATE::LEANING:

        rotateRespectTo(bn::fixed_point(84,39),-0.6666);

        if(timer && timer->elapsedFrames() >= 30){
            state = MSTATE::FALLING;

            sprite.set_tiles(bn::sprite_items::matthew.tiles_item().create_tiles(3));
            timer = bn::make_unique<Timer>();
            BN_LOG("Change Matthew to falling");
        }
        break;
    case MSTATE::FALLING:
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

void WorkRoof::Matthew::rotateRespectTo(bn::fixed_point pivot, bn::fixed delta_degrees){
    bn::fixed_point local_coords = sprite.position() - pivot;
    bn::fixed_point aplified_coords = local_coords * 1000;
    BN_LOG("Local Coords:",local_coords.x()," ",local_coords.y());
    bn::fixed radius = bn::sqrt((local_coords.x() * local_coords.x()) + (local_coords.y() * local_coords.y()));
    bn::fixed angle_degrees = bn::degrees_atan2(aplified_coords.x().integer(),aplified_coords.y().integer());
    BN_LOG("Amp Coords:",aplified_coords.x()," ",aplified_coords.y());
    BN_LOG("Atan2:",bn::degrees_atan2(aplified_coords.x().integer(),aplified_coords.y().integer()));
    angle_degrees = bn::safe_degrees_angle(angle_degrees + delta_degrees - 90);

    BN_LOG("Degrees from pivot:",angle_degrees);

    sprite.set_rotation_angle(bn::safe_degrees_angle(sprite.rotation_angle()+delta_degrees));
        
    bn::fixed aux = 1.0 + bn::degrees_cos(angle_degrees);
    aux *= radius;
    BN_LOG("Aux:",aux);
    aux -= (radius - 0.1);
    bn::fixed x =  pivot.x() + aux;
    BN_LOG("Radius:",radius);
    BN_LOG("Aux:",aux);
    BN_LOG("Cos * Radius:",bn::degrees_cos(angle_degrees));
    BN_LOG("Degrees cos:",bn::degrees_cos(angle_degrees));
    BN_LOG("Degrees sin:",bn::degrees_sin(angle_degrees));
    bn::fixed y =  pivot.y() - (bn::degrees_sin(angle_degrees)*radius);// minus cause y-axis is flipped
    BN_LOG("New Pos:",x,",",y);
    BN_LOG("---------------------");
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
    global_var(_global_var),state(STATE::NORMAL),matthew(),edge(){

    player.setPos(-98,25);

    {
    DialogTrigger* dialog = new DialogTrigger(global_var,bn::fixed_rect(0,0,50,64),false,false);
    dialog->addDialog(Pair<int,int>(16,92));
    dialog->addDialog(Pair<int,int>(17,157));
    dialog->addDialog(Pair<int,int>(18,167));
    dialog->addDialog(Pair<int,int>(19,133));
    dialog->addDialog(Pair<int,int>(20,126));
    matthew.addDialog(dialog);
    }

    matthew.setHorizontalFlip(true);

    edge.addSprite(bn::sprite_items::roof_edge.create_sprite(16,-32,0));
    edge.addSprite(bn::sprite_items::roof_edge.create_sprite(0,0,1));
    edge.addSprite(bn::sprite_items::roof_edge.create_sprite(-32,16,2));
    edge.set_position(bn::fixed_point(87,48));

    global_var.getDialogManager().resetBottomText();
    global_var.getDialogManager().setBg(bn::regular_bg_items::bg_bottom_text_b.create_bg(8,48));

    BN_LOG("cos(360):",bn::degrees_cos(360.0));
    BN_LOG("cos(270):",bn::degrees_cos(270.0));
    BN_LOG("cos(180):",bn::degrees_cos(180.0));
    BN_LOG("cos(90):",bn::degrees_cos(90.0));

    BN_LOG("arctan2(1,0):",bn::degrees_atan2(0,-26));
    BN_LOG("arctan2(1,0):",bn::degrees_atan2(-26,0));
    BN_LOG("arctan2(1,0):",bn::degrees_atan2(0,26));
    BN_LOG("arctan2(1,0):",bn::degrees_atan2(26,0));

    timer = bn::make_unique<Timer>(); //ERASEME
    state = STATE::DIALOG;
    matthew.setHorizontalFlip(true);
}

bn::optional<RoomExit> WorkRoof::update(){
    player.update(state != STATE::NORMAL);

    switch (state){
    case STATE::DIALOG:
        if(timer == nullptr && !global_var.getDialogManager().hasADialogSequence()){
            timer = bn::make_unique<Timer>();
            matthew.setHorizontalFlip(true);
        }
        if(timer && timer->elapsedFrames() >= 35){
            state = STATE::ANIM;
            edge.setVisibility(false);
            timer.reset();
            matthew.startJump();
            BN_LOG("Change state to ANIM");
        }
        break;

    case STATE::ANIM:
        matthew.update();
        if(matthew.jumpfinished()){
            state = STATE::DARK;
            timer = bn::make_unique<Timer>();
            player.setVisible(false);
            bg_paper.set_visible(false);
            bg.set_visible(false);
            BN_LOG("Change state to dark");
        }
        break;
    
    case STATE::DARK:
        if(timer && timer->elapsedFrames() >= 90){
            state = STATE::NEWS;
            timer = bn::make_unique<Timer>();
            bg.set_visible(true); // Change background
            bg_paper.set_visible(true);
            BN_LOG("Change state to news");
        }
        break;

    case STATE::NEWS:
        if(timer && timer->elapsedFrames() >= 230){
            state = STATE::NORMAL;
            timer.reset();
            BN_LOG("Going to day change from roof");
            return RoomExit("day_change",DIRECTION::DOOR1);
        }
        break;
    
    default: //Normal
        matthew.checkDialog(player.boundaries());

        if(global_var.getDialogManager().hasADialogSequence()){
            state = STATE::DIALOG;
            matthew.setHorizontalFlip(false);
            BN_LOG("Change state to DIALOG");
        }
        break;
    }

    Room::update();

    return bn::nullopt;
}
}