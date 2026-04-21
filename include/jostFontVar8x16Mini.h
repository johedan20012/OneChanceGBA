#ifndef JOSTFONTVAR8x16MINI_H
#define JOSTFONTVAR8x16MINI_H

#include "bn_sprite_font.h"
#include "bn_utf8_characters_map.h"
#include "bn_sprite_items_jost_font_var_8x16_mini.h"

namespace game{

constexpr bn::utf8_character JostFontVar8x16Mini_utf8_characters[] = {
    "Á", "É", "Í", "Ó", "Ú", "Ü", "Ñ", "á", "é", "í", "ó", "ú", "ü", "ñ", "¡", "¿"
};
constexpr int8_t JostFontVar8x16Mini_character_widths[] = {
    1,  // 32
    1,  // 33 !
    7,  // 34 "
    8,  // 35 #
    8,  // 36 $
    7,  // 37 %
    8,  // 38 &
    1,  // 39 ' -
    5,  // 40 (
    5,  // 41 )
    7,  // 42 *
    7,  // 43 +
    4,  // 44 ,
    7,  // 45 -
    1,  // 46 .
    7,  // 47 /
    7,  // 48 0
    4,  // 49 1
    7,  // 50 2
    7,  // 51 3
    7,  // 52 4
    7,  // 53 5
    7,  // 54 6
    7,  // 55 7
    7,  // 56 8
    7,  // 57 9
    4,  // 58 :
    4,  // 59 ;
    6,  // 60 <
    7,  // 61 =
    6,  // 62 >
    4,  // 63 ?
    8,  // 64 @
    5,  // 65 A
    3,  // 66 B
    4,  // 67 C
    4,  // 68 D
    3,  // 69 E
    3,  // 70 F
    5,  // 71 G
    4,  // 72 H
    1,  // 73 I
    2,  // 74 J
    3,  // 75 K
    3,  // 76 L
    6,  // 77 M
    4,  // 78 N
    5,  // 79 O
    3,  // 80 P
    6,  // 81 Q
    3,  // 82 R
    3,  // 83 S
    4,  // 84 T
    4,  // 85 U
    6,  // 86 V
    8,  // 87 W
    5,  // 88 X
    5,  // 89 Y
    5,  // 90 Z
    5,  // 91 [
    7,  // 92
    5,  // 93 ]
    4,  // 94 ^
    7,  // 95 _
    4,  // 96 `
    3,  // 97 a
    3,  // 98 b
    3,  // 99 c
    3,  // 100 d
    3,  // 101 e
    3,  // 102 f
    3,  // 103 g
    3,  // 104 h
    1,  // 105 i
    2,  // 106 j
    3,  // 107 k
    1,  // 108 l
    5,  // 109 m
    3,  // 110 n
    3,  // 111 o
    3,  // 112 p
    3,  // 113 q
    3,  // 114 r
    3,  // 115 s
    3,  // 116 t
    3,  // 117 u
    4,  // 118 v
    6,  // 119 w
    4,  // 120 x
    4,  // 121 y
    3,  // 122 z
    6,  // 123 {
    3,  // 124 |
    6,  // 125 }
    8,  // 126 ~
    7,  // Á
    7,  // É
    5,  // Í
    7,  // Ó
    7,  // Ú
    7,  // Ü
    7,  // Ñ
    7,  // á
    7,  // é
    4,  // í
    7,  // ó
    7,  // ú
    7,  // ü
    7,  // ñ
    3,  // ¡
    7,  // ¿
};

constexpr bn::span<const bn::utf8_character> JostFontVar8x16Mini_utf8_characters_span(
        JostFontVar8x16Mini_utf8_characters);

constexpr auto JostFontVar8x16Mini_utf8_characters_map =
        bn::utf8_characters_map<JostFontVar8x16Mini_utf8_characters_span>();

//constexpr bn::sprite_font JostFontVar8x16(bn::sprite_items::jost_font_var_8x16);


constexpr bn::sprite_font JostFontVar8x16Mini(bn::sprite_items::jost_font_var_8x16_mini,
        JostFontVar8x16Mini_utf8_characters_map.reference(),JostFontVar8x16Mini_character_widths,1);

}

#endif