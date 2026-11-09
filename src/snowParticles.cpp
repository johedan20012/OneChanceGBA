#include "snowParticles.h"

#include "bn_sprite_items_snow_particle.h"

#include "bn_math.h"
#include "bn_memory.h"
#include "bn_affine_mat_attributes.h"

namespace game{

SnowParticles::Particle::Particle(bool _go_right,bn::fixed_point _init_pos,bn::fixed _fade_out_y,bn::fixed dist_to_left_limit,bn::fixed dist_to_right_limit,bn::sprite_affine_mat_ptr scale,int _fade_in_color,bn::sprite_palette_ptr palette):
tiles(bn::sprite_tiles_ptr::allocate(2,bn::bpp_mode::BPP_8)),
spr(bn::sprite_ptr::create(_init_pos,bn::sprite_shape_size(bn::sprite_shape::SQUARE,bn::sprite_size::SMALL),tiles,palette)),
init_pos(_init_pos),fade_in_color(_fade_in_color),fade_out_color(-1),curr_color(fade_in_color),
frames_to_step_fade(SnowParticles::FADE_STEP_TIME),fading_in(true),fading_out(false),faded_out(false),
min_x(_init_pos.x() - dist_to_left_limit),max_x(_init_pos.x() + dist_to_right_limit),fade_out_y(_fade_out_y)
{
    spr.set_affine_mat(scale);
    going_right = _go_right;
    update_particle_color();
}

void SnowParticles::Particle::update_particle_color(){
    BN_ASSERT(tiles.vram() != bn::nullopt,"Can't access vram of snow particle");
    BN_ASSERT(curr_color >= 0 && curr_color <= 64, "Color out of bounds for snow particle:",curr_color," ",fading_out);
    
    bn::tile* vram_tiles_ptr = tiles.vram().value().data();
    for(int j=0; j<2; ++j) for(int i =0; i<8; ++i) vram_tiles_ptr[j].data[i] = curr_color | (curr_color << 8) | (curr_color << 16) | (curr_color << 24);
}

void SnowParticles::Particle::update(){
    spr.set_y(spr.y()+SnowParticles::PARTICLE_SPEED_Y);

    bn::fixed aux = (spr.x()-min_x) / (max_x-min_x);
    aux = bn::min(bn::max((aux*2)-1,bn::fixed{-1}),bn::fixed{1}); // aux \in [-1,1]

    if(aux >= bn::fixed{1} && going_right){
        going_right = false;
        aux = bn::fixed{1};
    }else if(aux <= bn::fixed{-1} && !going_right){
        going_right = true;
        aux = bn::fixed{-1};
    }

    bn::fixed amp = bn::sqrt(1 - (aux*aux)); // cos(arcsin(x)) = \sqrt{1-x^2}
    if(!going_right) amp *= -1;
    bn::fixed vel_x = amp*SnowParticles::PARTICLE_SPEED_X;

    if(amp == bn::fixed{0}){
        if(going_right) vel_x = bn::fixed{0.0156};
        else vel_x = -bn::fixed{0.0156};
    }

    spr.set_x(spr.x() + vel_x);

    if(faded_out){
        spr.set_position(init_pos);
        fading_in = true;
        fading_out = true;
        faded_out = false;
        fade_out_color = -1;
        curr_color = fade_in_color;
        frames_to_step_fade = SnowParticles::FADE_STEP_TIME;
        return;
    }else if(spr.y() >= fade_out_y && !fading_out){
        for(int i=0; i<SnowParticles::MAX_FADE_OUT_AREAS; ++i){
            if(fade_out_areas[i].area.edge_contains(spr.position())){
                fading_out = true;
                fade_out_color = SnowParticles::FADE_OUT_COLOR_INDX[fade_out_areas[i].palette_indx];
                curr_color = fade_out_color;
            }        
        }
    }

    if(fading_in){
        if(fading_out){
            update_particle_color();
            fading_out = false;
        }

        frames_to_step_fade--;
        if(frames_to_step_fade <= 0){
            curr_color--;
            if(curr_color == fade_in_color-SnowParticles::FADE_STEPS) fading_in = false;

            update_particle_color();

            frames_to_step_fade = SnowParticles::FADE_STEP_TIME;
        }
        return;
    }

    if(fading_out){
        frames_to_step_fade--;
        if(frames_to_step_fade <= 0){
            curr_color++;
            if(curr_color == fade_out_color+SnowParticles::FADE_STEPS){
                fading_out = false;
                faded_out = true;
            }

            update_particle_color();

            frames_to_step_fade = SnowParticles::FADE_STEP_TIME;
        }
    }
}

SnowParticles::SnowParticles(GlobalVariables &_global_var):
global_var(_global_var),
snow_palette(bn::sprite_items::snow_particle.palette_item().create_new_palette()){    
    create_particles(12,bn::sprite_affine_mat_ptr::create(bn::affine_mat_attributes(0,bn::fixed{0.5},bn::fixed{0.5},false,false)));
    create_particles(14,bn::sprite_affine_mat_ptr::create(bn::affine_mat_attributes(0,bn::fixed{0.25},bn::fixed{0.25},false,false)));
    create_particles(16,bn::sprite_affine_mat_ptr::create(bn::affine_mat_attributes(0,bn::fixed{0.125},bn::fixed{0.125},false,false)));
}

void SnowParticles::create_particles(int n,bn::sprite_affine_mat_ptr scale){
    int fade_in_area=0,aux;
    bn::fixed_point init_pos;
    bn::fixed y_fade_out;
    for(int i=0; i<n; i++){
        aux = global_var.random_int(0,TOTAL_WEIGHT_FADE_IN);
        for(int j=0; j<MAX_FADE_IN_AREAS; ++j){
            if(aux <= fade_in_areas[j].weight){fade_in_area = j; break;}
            else aux -= fade_in_areas[j].weight;
        }
        init_pos = {
            global_var.random_fixed(fade_in_areas[fade_in_area].area.left(),fade_in_areas[fade_in_area].area.right()),
            global_var.random_fixed(fade_in_areas[fade_in_area].area.top(),fade_in_areas[fade_in_area].area.bottom())};
        y_fade_out = global_var.random_fixed(15,90);
        particles.push_back(Particle(global_var.random_int(0,2) == 1,init_pos,y_fade_out,global_var.random_fixed(6,56),global_var.random_fixed(6,56),scale,FADE_IN_COLOR_INDX[fade_in_areas[fade_in_area].palette_indx],snow_palette));
    }
}

void SnowParticles::update(){    
    for(int i=0; i<particles.size(); i++){
        particles[i].update();
    }
}
}