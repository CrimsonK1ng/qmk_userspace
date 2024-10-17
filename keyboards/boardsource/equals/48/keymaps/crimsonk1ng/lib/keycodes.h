#pragma once

#include "action_code.h"
#include "action_util.h"
// clang-format off

#include QMK_KEYBOARD_H
#include "layers.h"

// MACROS
enum custom_keycodes {
  // some custom keys
  OSX = SAFE_RANGE,
  // LLOCK,
  WQ,
  CMDGRV,
  CMDTAB,
  ALTTAB,
};

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

// TOP RIGHT
#define MOD_J KC_J
#define LAY_U KC_U
#define LAY_Y LT(_BRK, KC_Y)
#define MINS  LT(_BRK,KC_MINS)
#define FBSPC LT(_FUNC, KC_BSPC)
// MIDDLE
#define MOD_M     RSFT_T(KC_M)
#define MOD_N     RGUI_T(KC_N)
#define MOD_E     RCTL_T(KC_E)
#define MOD_I     LT(_SYM, KC_I)
#define MOD_O     LT(_NAV, KC_O)
#define QUOT      MEH_T(KC_QUOT)
// BOTTOM
#define MOD_SLSH  RGUI_T(KC_SLSH)
#define MOD_DOT   RCTL_T(KC_DOT)
#define MOD_COMM  LALT_T(KC_COMM)
#define MOD_H     RSFT_T(KC_H)
#define MOD_K     KC_K
// END RIGHT

// TOP LEFT
#define MOD_Q LT(_NUM, KC_Q)
#define LAY_W LT(_NAV, KC_W)
#define LAY_F LT(_NUM, KC_F)
#define MOD_B KC_B
// MIDDLE
#define MOD_G   LSFT_T(KC_G)
#define MOD_T   LGUI_T(KC_T)
#define MOD_S   LCTL_T(KC_S)
#define MOD_R   LT(_SYM, KC_R)
#define MOD_A   LT(_NAV, KC_A)
#define MODLAY  LT(_NAV, KC_BSPC) // outer column
// BOTTOM
#define NUM_DEL LT(_NUM, KC_DEL)
#define MOD_Z   LGUI_T(KC_Z)
#define MOD_X   LCTL_T(KC_X)
#define MOD_C   LALT_T(KC_C)
#define MOD_D   LSFT_T(KC_D)
#define MOD_V   KC_V
// THUMBS
#define BSPC   LSFT_T(KC_BSPC)
#define ENT    LT(_NAV, KC_ENT)
#define SYMO   OSL(_SYM)
// END LEFT

// ----------------------------------

// Stuff
#define GRV     LT(0, KC_GRV)
#define ADJUST  LT(_ADJUST, KC_TAB)
#define ESC     LT(_NUM, KC_ESC)
#define SPC    LT(_FUNC, KC_SPC)//LT(0, KC_SPC)// RCTL_T(KC_SPC)
#define TAB    HYPR_T(KC_TAB)

// SPECIAL THUMBS
#define C_BSP  C(KC_BSPC)
#define A_BSP  A(KC_BSPC)

// NUMBERS
#define POPZED  MT(MOD_LCTL | MOD_LGUI, KC_0)
// shortcuts
#define NXTTAB C(KC_TAB)
#define PRVTAB S(C(KC_TAB))
