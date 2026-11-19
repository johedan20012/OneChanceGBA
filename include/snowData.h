#ifndef SNOWDATA_H
#define SNOWDATA_H

#include "snowParticles.h"

namespace game{
inline constexpr FadeInOutArea ROOF_IN_AREAS[5] = {
    {bn::fixed_rect(8.0, -80, 256.0, 30.0),0,7680},
    {bn::fixed_rect(-1.5, -65.0, 149.0, 30.0),0,4470},
    {bn::fixed_rect(103.0, -33.0, 28.0, 16.0),1,448},
    {bn::fixed_rect(-31.5, -18.0, 19.0, 46.0),2,874},
    {bn::fixed_rect(48.5, -17.0, 17.0, 44.0),2,748}
};

inline constexpr FadeInOutArea ROOF_OUT_AREAS[5] = {
    {bn::fixed_rect(-27.0, 53.0, 132.0, 54.0),3,0},
    {bn::fixed_rect(124.0, 53.0, 24.0, 54.0),4,0},
    {bn::fixed_rect(90.0, 72.0, 30.0, 16.0),5,0},
    {bn::fixed_rect(52.0, 38.5, 18.0, 25.0),3,0},
    {bn::fixed_rect(-2.0, 18.0, 182.0, 6.0),6,0}
};

inline constexpr FadeInOutArea PARK1_IN_AREAS[3] = {
    {bn::fixed_rect(8.0, -88.5, 256.0, 63.0),6,16128},
    {bn::fixed_rect(-2.0, -54.0, 160.0, 34.0),6,5440},
    {bn::fixed_rect(-69.0, -18.0, 78.0, 20.0),1,1560}
};

inline constexpr FadeInOutArea PARK1_OUT_AREAS[] = {
    {bn::fixed_rect(-74.0, 89.5, 78.0, 35.0),0,0},
    {bn::fixed_rect(67.0, 93.5, 80.0, 47.0),0,0},
    {bn::fixed_rect(-26.0, 62.5, 108.0, 7.0),1,0},
    {bn::fixed_rect(-5.5, 83.0, 51.0, 48.0),1,0},
    {bn::fixed_rect(42.5, 46.5, 81.0, 5.0),5,0},
    {bn::fixed_rect(106.0, 25.5, 12.0, 47.0),4,0},
    {bn::fixed_rect(-93.0, 25.5, 12.0, 47.0),4,0},
    {bn::fixed_rect(-42.5, 25.5, 13.0, 47.0),4,0},
    {bn::fixed_rect(39.5, 32.0, 47.0, 14.0),3,0},
};

inline constexpr FadeInOutArea PARK2_IN_AREAS[] = {
    {bn::fixed_rect(8.0, -79.5, 256.0, 61.0),6,15616},
    {bn::fixed_rect(-19.5, -43.0, 201.0, 14.0),6,2814},
    {bn::fixed_rect(69.0, -18.0, 76.0, 20.0),1,1520},
    {bn::fixed_rect(-81.0, -18.0, 78.0, 20.0),1,1560}
};

inline constexpr FadeInOutArea PARK2_OUT_AREAS[] = {
    {bn::fixed_rect(75.0, 90.5, 122.0, 61.0),1,0},
    {bn::fixed_rect(-105.5, 89.0, 29.0, 60.0),1,0},
    {bn::fixed_rect(-33.0, 72.0, 70.0, 8.0),0,0},
    {bn::fixed_rect(-8.0, 51.5, 54.0, 11.0),2,0},
    {bn::fixed_rect(-79.5, 52.5, 25.0, 9.0),2,0}
};
}
#endif