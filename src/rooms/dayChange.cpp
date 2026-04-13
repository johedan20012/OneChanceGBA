#include "dayChange.h"

#include "bn_sprite_text_generator.h"   

#include "bn_regular_bg_items_bg_house_1.h"

#include "bn_log.h"

#include "jostFontVar8x16Mini.h"

namespace game{
DayChange::DayChange(Player& _player,GlobalVariables& _global_var):
    Room(bn::regular_bg_items::bg_house_1.create_bg(8,48),bn::fixed_rect(0,0,240,160),_player),
    global_var(_global_var){
    
    global_var.goNextDay();
    global_var.setVisitedLabDoor(false);

    BN_LOG("Day 1:",global_var.dayChoice(1));
    BN_LOG("Day 2:",global_var.dayChoice(2));
    BN_LOG("Day 3:",global_var.dayChoice(3));
    BN_LOG("Day 4:",global_var.dayChoice(4));
    BN_LOG("Day 5:",global_var.dayChoice(5));
    BN_LOG("Day 6:",global_var.dayChoice(6));

    bn::string<80> top_message;
    bn::string<30> bottom_message;
    switch (global_var.currentDay()){
    case 2:
        top_message = "In five days,";
        break;
    case 3:
        top_message = "In four days,";
        break;
    case 4:
        top_message = "In three days,";
        break;
    case 5:
        top_message = "In Two days,";
        break;
    case 6:
        top_message = "Today";
        break;
    default: // Day 1
        top_message = "In six days,";
        break;
    }

    if(global_var.currentDay() < 6) top_message += " every single living cell on Planet Earth will be dead.";
    else top_message += " every single living cell on Planet Earth will die.";

    if(global_var.currentDay() < 6) bottom_message = "You have one chance.";
    else bottom_message = "You had one chance.";

    player.setVisible(false);
    bg->set_visible(false);
    bg_paper->set_visible(false);

    if(global_var.currentDay() >= 3) player.takeOffLabCoat();

    timer = bn::make_unique<Timer>();

    bn::sprite_text_generator text_gen(JostFontVar8x16Mini,bn::sprite_palette_item(palette1,bn::bpp_mode::BPP_4));
    text_gen.set_center_alignment();
    text_gen.generate(bn::fixed_point(0,-37),top_message,text);
    pal1 = text.back().palette();
    pal1->set_fade_color(bn::color(0,0,0));
    pal1->set_fade_intensity(1);
    bn::sprite_text_generator text_gen2(JostFontVar8x16Mini,bn::sprite_palette_item(palette2,bn::bpp_mode::BPP_4));
    text_gen2.set_center_alignment();
    text_gen2.generate(bn::fixed_point(0,2),bottom_message,text);
    pal2 = text.back().palette();
    pal2->set_fade_color(bn::color(0,0,0));
    pal2->set_fade_intensity(1);
}

bn::optional<RoomExit> DayChange::update(){
    switch (state){
        case STATE::DARK:
            if(timer && timer->elapsedFrames() >= DARK_FRAMES){
                pal1_fade = bn::make_unique<bn::sprite_palette_fade_to_action>(pal1.value(),120,0);
                timer.reset();
            }
            if(pal1_fade && !pal1_fade->done()){
                pal1_fade->update();
                if(pal1_fade->done()){
                    pal1_fade.reset();
                    state = STATE::LIGHT_TOP;
                    pal2_fade = bn::make_unique<bn::sprite_palette_fade_to_action>(pal2.value(),120,0);
                }
            }
            break;
        case STATE::LIGHT_TOP:
            if(pal2_fade && !pal2_fade->done()){
                pal2_fade->update();
                if(pal2_fade->done()){
                    pal2_fade.reset();
                    state = STATE::HOLD_LIGHT;
                    timer = bn::make_unique<Timer>();
                }
            }
            break;
        case STATE::HOLD_LIGHT:
            if(timer && timer->elapsedFrames() >= BRIGHT_FRAMES){
                timer.reset();
                pal1_fade = bn::make_unique<bn::sprite_palette_fade_to_action>(pal1.value(),120,1);
                pal2_fade = bn::make_unique<bn::sprite_palette_fade_to_action>(pal2.value(),120,1);
            }
            if(pal1_fade && !pal1_fade->done()) pal1_fade->update();
            if(pal2_fade && !pal2_fade->done()) pal2_fade->update();
            if(pal1_fade && pal1_fade->done()){
                state = STATE::HOLD_DARK;
                timer = bn::make_unique<Timer>();
            }
            break;
        case STATE::HOLD_DARK:
            if(timer && timer->elapsedFrames() >= LAST_DARK_FRAMES){
                player.setVisible(true);
                return RoomExit("house_bedroom",DIRECTION::DOOR1);
            }
            break;
        default: // i don't like compiler warnings
            break;
    }

    Room::update();

    return bn::nullopt;
}
}