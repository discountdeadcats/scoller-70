// custom_84key.h
#pragma once

#include "quantum.h"
#include "print.h"

// Layout macro matching the physical key arrangement
#define LAYOUT_84_key( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E,      K2G, \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,           K3G, \
    K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E,      K4G, \
    K51, K52, K53,           K56,                K5A, K5B, K5C, K5D, K5E,      K5G  \
) { \
    { K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G }, \
    { K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G }, \
    { K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, KC_NO, K2G }, \
    { K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, KC_NO, KC_NO, K3G }, \
    { K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E, KC_NO, K4G }, \
    { K51, K52, K53, KC_NO, KC_NO, K56, KC_NO, KC_NO, KC_NO, K5A, K5B, K5C, K5D, K5E, KC_NO, K5G } \
}

