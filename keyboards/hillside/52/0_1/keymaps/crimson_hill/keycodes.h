#pragma once

// clang-format off

#include QMK_KEYBOARD_H
#include "layers.h"


// One shot mods
#define OSMS OSM(MOD_LSFT)
#define OSMC OSM(MOD_LCTL)
#define OSMG OSM(MOD_LGUI)
#define OSMA OSM(MOD_LALT)
#define OSMH OSM(MOD_HYPR)
#define OSMM OSM(MOD_MEH)

#define OSMP OSM(MOD_LGUI | MOD_LCTL)
#define OSMCS OSM(MOD_LSFT | MOD_LCTL)
#define OSMGS OSM(MOD_LSFT | MOD_LGUI)

#define BRACKS OSL(_BRK)

// TOP RIGHT
#define MOD_J KC_J
#define MOD_L KC_L
#define MOD_U KC_U
#define MOD_Y LT(_BRK, KC_Y)
#define MINS  KC_MINS
#define FBSPC LT(_FUNC, KC_BSPC)
// MIDDLE
#define MOD_M     MEH_T(KC_M)
#define MOD_N     RGUI_T(KC_N)
#define MOD_E     RCTL_T(KC_E)
#define MOD_I     LT(_SYM, KC_I)
#define MOD_O     LT(_BRK, KC_O)
#define QUOT      HYPR_T(KC_QUOT)
// BOTTOM
#define MOD_K     KC_K
#define MOD_H     RSFT_T(KC_H)
#define MOD_DOT   RCTL_T(KC_DOT)
#define MOD_COMM  LALT_T(KC_COMM)
#define MOD_SLSH  RGUI_T(KC_SLSH)
// END RIGHT

// TOP LEFT
#define MOD_Q LT(_NUM, KC_Q)
#define MOD_W LT(_NAV, KC_W)
#define MOD_F LT(_NUM, KC_F)
#define MOD_P KC_P
#define MOD_B KC_B
// MIDDLE
#define MODLAY  LT(_NAV, KC_BSPC) // outer column
#define MOD_A   LT(_NAV, KC_A)
#define MOD_R   LT(_SYM, KC_R)
#define MOD_S   LCTL_T(KC_S)
#define MOD_T   LGUI_T(KC_T)
#define MOD_G   MEH_T(KC_G)
// BOTTOM
#define NUM_DEL LT(_NUM, KC_DEL)
#define MOD_Z   LGUI_T(KC_Z)
#define MOD_X   LCTL_T(KC_X)
#define MOD_C   LALT_T(KC_C)
#define MOD_D   LSFT_T(KC_D)
#define MOD_V   KC_V
// THUMBS
#define BSPC   LT(_NAV, KC_BSPC)
#define ENT    LSFT_T(KC_ENT)
#define SYMO   OSL(_SYM)
// END LEFT

// ----------------------------------

// Stuff
#define GRV     LT(0, KC_GRV)
#define ADJUST  LT(_ADJUST, KC_TAB)
#define ESC     LT(_NUM, KC_ESC)
#define SPC    LT(_BRK, KC_SPC)//LT(0, KC_SPC)// RCTL_T(KC_SPC)
#define TAB    HYPR_T(KC_TAB)

// SPECIAL THUMBS
#define C_BSP  C(KC_BSPC)
#define A_BSP  A(KC_BSPC)

// NUMBERS
#define POPZED  MT(MOD_LCTL | MOD_LGUI, KC_0)
// shortcuts
#define NXTTAB C(KC_TAB)
#define PRVTAB S(C(KC_TAB))
