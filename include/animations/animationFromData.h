#ifndef ANIMATIONFROMDATA_H
#define ANIMATIONFROMDATA_H

#include "bn_sprite_ptr.h"

#include "bn_log.h"
#include "bn_sram.h"
#include "bn_fixed.h"
#include "bn_array.h"
#include "bn_vector.h"
#include "bn_assert.h"
#include "bn_keypad.h"

#include "animation.h"

namespace game{

struct SRAMDataAccess {};
struct ROMDataAccess {};

template <typename DataPolicy,int MAX_FRAMES,int MAX_OBJECTS>
class AnimationFromData : public Animation {
protected:
    struct ObjectData{
        bn::fixed_point pos_offset;
        bn::fixed rotation;
    };

    struct FrameData{
        uint32_t frame_indx;
        bn::array<ObjectData,MAX_OBJECTS> objects_data;
    };

    struct AnimationData{
        bn::array<char,4> format;
        uint32_t max_frames;
        uint32_t max_objects;
        uint32_t duration;
        bn::array<FrameData,MAX_FRAMES> frames_data;
    };

    static constexpr bool data_from_sram = std::is_same_v<DataPolicy, SRAMDataAccess>;

    uint32_t frame = 0;
    uint32_t data_indx = 0;
    bn::vector<bn::sprite_ptr,MAX_OBJECTS> objects;

    [[no_unique_address]] std::conditional_t<data_from_sram, AnimationData, std::monostate> record_animation_data;
    [[no_unique_address]] std::conditional_t<data_from_sram, bool, std::monostate> record_mode;
    [[no_unique_address]] std::conditional_t<data_from_sram, bool, std::monostate> run;
    [[no_unique_address]] std::conditional_t<data_from_sram, bn::array<bn::fixed_point,MAX_OBJECTS>, std::monostate> objects_og_pos;
  
    [[no_unique_address]] std::conditional_t<!data_from_sram, const AnimationData&, std::monostate> animation_data;
public:

    AnimationFromData(uint32_t _duration,bool _record_mode = false)
    requires (data_from_sram) : record_mode(_record_mode)
    {
        if(!record_mode){
            bn::sram::read(record_animation_data);

            BN_ASSERT(record_animation_data.format[0] == 'A' && 
            record_animation_data.format[1] == 'N' && 
            record_animation_data.format[2] == 'I' &&
            record_animation_data.format[3] == 'M' &&
            record_animation_data.max_frames == MAX_FRAMES &&
            record_animation_data.max_objects == MAX_OBJECTS, "Bad format for animation data");
        }else{
            bn::sram::read(record_animation_data);
            record_animation_data.duration = _duration;

            if(!(record_animation_data.format[0] == 'A' && 
            record_animation_data.format[1] == 'N' && 
            record_animation_data.format[2] == 'I' &&
            record_animation_data.format[3] == 'M' &&
            record_animation_data.max_frames == MAX_FRAMES &&
            record_animation_data.max_objects == MAX_OBJECTS)){
                BN_LOG("Fixing... bad format");
                record_animation_data.format[0] = 'A';
                record_animation_data.format[1] = 'N';
                record_animation_data.format[2] = 'I';
                record_animation_data.format[3] = 'M';
                record_animation_data.max_frames = MAX_FRAMES;
                record_animation_data.max_objects = MAX_OBJECTS;
            }
        }
    }

    AnimationFromData(const uint8_t *data,size_t data_size)
    requires (!data_from_sram)
    : animation_data(*reinterpret_cast<const AnimationData(*)>(data)) {
        BN_ASSERT(data_size == sizeof(AnimationData),"Unexpected file size for animation data, expected:",sizeof(AnimationData),".Received:",data_size);
        BN_ASSERT(
            animation_data.format[0] == 'A' && 
            animation_data.format[1] == 'N' && 
            animation_data.format[2] == 'I' &&
            animation_data.format[3] == 'M' &&
            animation_data.max_frames == MAX_FRAMES &&
            animation_data.max_objects == MAX_OBJECTS, "Bad format for animation data");
    }


    virtual ~AnimationFromData() = default;

    void add_object(bn::sprite_ptr object){objects.push_back(object);}

    void set_objects_og_pos()
    requires(data_from_sram)
    {
        for(int i = 0; i< objects.size(); ++i){
            objects_og_pos[i] = objects[i].position();
        }
        BN_LOG("Objects og positions reseted");
    }

    virtual void update()
    {
    if constexpr(data_from_sram){
        if(record_mode){
            if(bn::keypad::l_held() && bn::keypad::b_pressed()){
                set_objects_og_pos();
            }

            if(bn::keypad::r_held() && bn::keypad::a_pressed() && data_indx < MAX_FRAMES){
                BN_LOG("Applying data_indx:",data_indx);
                for(int i = 0; i < record_animation_data.frames_data[data_indx].objects_data.size(); ++i){
                    BN_ASSERT(i >= 0 && i < MAX_OBJECTS, "AnimationFromData: indx out of bounds for object_data");
                    objects[i].set_position(objects[i].position() + record_animation_data.frames_data[data_indx].objects_data[i].pos_offset);
                    objects[i].set_rotation_angle(record_animation_data.frames_data[data_indx].objects_data[i].rotation);
                }

                frame = record_animation_data.frames_data[data_indx].frame_indx;
                ++data_indx;
            }

            if(bn::keypad::r_held() && bn::keypad::left_pressed()){
                frame = bn::max(frame-1,uint32_t(0));
                BN_LOG("Anim frame:",frame);
            }

            if(bn::keypad::r_held() && bn::keypad::right_pressed()){
                ++frame;
                BN_LOG("Anim frame:",frame);
            }

            if(bn::keypad::l_held() && bn::keypad::left_pressed()){
                data_indx = bn::max(data_indx-1,uint32_t(0));
                BN_LOG("Anim dataindx:",data_indx);
            }

            if(bn::keypad::l_held() && bn::keypad::right_pressed()){
                data_indx = bn::min(data_indx+1,uint32_t{MAX_FRAMES-1});
                BN_LOG("Anim dataindx:",data_indx);
            }

            if(bn::keypad::l_held() && bn::keypad::r_held() && bn::keypad::select_pressed()){
                // Save the frame data
                BN_LOG("Anim dataindx:",data_indx);
                record_animation_data.frames_data[data_indx].frame_indx = frame;

                bn::array<bn::fixed_point,MAX_OBJECTS> acum_offsets{};
                for(uint32_t d_indx = 0; d_indx < data_indx; ++d_indx){
                    for(int indx = 0; indx < objects.size(); ++indx){
                        acum_offsets[indx] += record_animation_data.frames_data[d_indx].objects_data[indx].pos_offset;
                    }
                }

                for(int indx = 0; indx < objects.size(); ++indx){
                    record_animation_data.frames_data[data_indx].objects_data[indx].pos_offset = objects[indx].position() - (acum_offsets[indx] + objects_og_pos[indx]);
                    record_animation_data.frames_data[data_indx].objects_data[indx].rotation = objects[indx].rotation_angle();
                }

                ++frame;
                ++data_indx;
                BN_LOG("Anim new frame:",frame,"\nFrame data saved in data indx:",data_indx-1);
            }

            if(bn::keypad::l_held() && bn::keypad::r_held() && bn::keypad::start_pressed()){
                // Save all the data to SRAM
                bn::sram::write(record_animation_data);
                BN_LOG("Animation data written to save file");
            }
            return;
        }
        
        if(bn::keypad::r_held() && bn::keypad::a_pressed()) run = !run;
        if(!run && !(bn::keypad::l_held() && bn::keypad::a_pressed())) return;

        BN_LOG("Frame animation:",frame);
        if(data_indx < MAX_FRAMES && record_animation_data.frames_data[data_indx].frame_indx <= frame){
            for(int i = 0; i < record_animation_data.frames_data[data_indx].objects_data.size(); ++i){
                BN_ASSERT(i >= 0 && i < MAX_OBJECTS, "AnimationFromData: indx out of bounds for object_data");
                objects[i].set_position(objects[i].position() + record_animation_data.frames_data[data_indx].objects_data[i].pos_offset);
                objects[i].set_rotation_angle(record_animation_data.frames_data[data_indx].objects_data[i].rotation);
            }

            ++data_indx;
        }

        ++frame;
    }else{
        if(data_indx < MAX_FRAMES && animation_data.frames_data[data_indx].frame_indx <= frame){
            for(int i = 0; i < animation_data.frames_data[data_indx].objects_data.size(); ++i){
                BN_ASSERT(i >= 0 && i < MAX_OBJECTS, "AnimationFromData: indx out of bounds for object_data");
                objects[i].set_position(objects[i].position() + animation_data.frames_data[data_indx].objects_data[i].pos_offset);
                objects[i].set_rotation_angle(animation_data.frames_data[data_indx].objects_data[i].rotation);
            }
            ++data_indx;
        }
        ++frame;
    }
    }
    
    virtual bool isFinished(){
        if constexpr(data_from_sram){
            return false;
        }else{
            return frame >= animation_data.duration;
        }
    };
};
}
#endif