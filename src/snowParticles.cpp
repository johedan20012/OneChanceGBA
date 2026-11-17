#include "snowParticles.h"

#include "bn_math.h"
#include "bn_memory.h"
#include "bn_affine_mat_attributes.h"

namespace game{

Particle::Particle(bool _go_right,bn::fixed_point _init_pos,bn::fixed _fade_out_y,bn::fixed dist_to_left_limit,bn::fixed dist_to_right_limit,bn::sprite_affine_mat_ptr scale,int _fade_in_color,bn::sprite_palette_ptr palette,bn::span<const FadeInOutArea> _fade_out_areas):
fade_out_areas(_fade_out_areas),tiles(bn::sprite_tiles_ptr::allocate(2,bn::bpp_mode::BPP_8)),
spr(bn::sprite_ptr::create(_init_pos,bn::sprite_shape_size(bn::sprite_shape::SQUARE,bn::sprite_size::SMALL),tiles,palette)),
init_pos(_init_pos),fade_in_color(_fade_in_color),fade_out_color(-1),curr_color(fade_in_color),
frames_to_step_fade(FADE_STEP_TIME),fading_in(true),fading_out(false),faded_out(false),
min_x(_init_pos.x() - dist_to_left_limit),max_x(_init_pos.x() + dist_to_right_limit),fade_out_y(_fade_out_y)
{
    spr.set_affine_mat(scale);
    going_right = _go_right;
    update_particle_color();
}

void Particle::update_particle_color(){
    BN_ASSERT(tiles.vram() != bn::nullopt,"Can't access vram of snow particle");
    BN_ASSERT(curr_color >= 0 && curr_color <= 64, "Color out of bounds for snow particle:",curr_color," ",fading_out);
    
    bn::tile* vram_tiles_ptr = tiles.vram().value().data();
    for(int j=0; j<2; ++j) for(int i =0; i<8; ++i) vram_tiles_ptr[j].data[i] = curr_color | (curr_color << 8) | (curr_color << 16) | (curr_color << 24);
}

void Particle::update(bn::optional<bn::fixed_rect> area_to_avoid){
    spr.set_y(spr.y()+PARTICLE_SPEED_Y);

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
    bn::fixed vel_x = amp*PARTICLE_SPEED_X;

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
        frames_to_step_fade = FADE_STEP_TIME;
        return;
    }else if(spr.y() >= fade_out_y && !fading_out){
        for(int i=0; i<fade_out_areas.size(); ++i){
            if(fade_out_areas[i].area.edge_contains(spr.position())){
                if(area_to_avoid && area_to_avoid->contains(spr.position())) continue;
                fading_out = true;
                fade_out_color = FADE_OUT_COLOR_INDX[fade_out_areas[i].palette_indx];
                curr_color = fade_out_color;
                break;
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
            if(curr_color == fade_in_color-FADE_STEPS) fading_in = false;

            update_particle_color();

            frames_to_step_fade = FADE_STEP_TIME;
        }
        return;
    }

    if(fading_out){
        frames_to_step_fade--;
        if(frames_to_step_fade <= 0){
            curr_color++;
            if(curr_color == fade_out_color+FADE_STEPS){
                fading_out = false;
                faded_out = true;
            }

            update_particle_color();

            frames_to_step_fade = FADE_STEP_TIME;
        }
    }
}

SnowParticles::SnowParticles(GlobalVariables &_global_var,Player &_player,bn::span<const FadeInOutArea> in_areas,bn::span<const FadeInOutArea> out_areas,bn::sprite_palette_item _snow_palette,bool _avoid_player):
global_var(_global_var),player(_player),fade_in_areas(in_areas),fade_out_areas(out_areas),avoid_player(_avoid_player),
snow_palette(_snow_palette.create_new_palette()){   
    for(int i=0; i<fade_in_areas.size(); ++i){
        TOTAL_WEIGHT_FADE_IN += fade_in_areas[i].weight;
    }
    
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
        for(int j=0; j<fade_in_areas.size(); ++j){
            if(aux <= fade_in_areas[j].weight){fade_in_area = j; break;}
            else aux -= fade_in_areas[j].weight;
        }
        init_pos = {
            global_var.random_fixed(fade_in_areas[fade_in_area].area.left(),fade_in_areas[fade_in_area].area.right()),
            global_var.random_fixed(fade_in_areas[fade_in_area].area.top(),fade_in_areas[fade_in_area].area.bottom())};
        y_fade_out = global_var.random_fixed(15,90);
        particles.push_back(Particle(global_var.random_int(0,2) == 1,init_pos,y_fade_out,global_var.random_fixed(6,56),global_var.random_fixed(6,56),scale,FADE_IN_COLOR_INDX[fade_in_areas[fade_in_area].palette_indx],snow_palette,fade_out_areas));
    }
}

void SnowParticles::update(){    
    for(int i=0; i<particles.size(); i++){
        if(avoid_player) particles[i].update(bn::fixed_rect{player.getPos(),bn::fixed_size{32,64}});
        else particles[i].update(bn::nullopt);
    }
}
}