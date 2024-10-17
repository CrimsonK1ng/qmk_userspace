// Copyright 2022 @boardsource
// SPDX-License-Identifier: GPL-2.0-or-later
#include "action_code.h"
#include "action_util.h"
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "lib/keycodes.h"
#include <stdio.h>
#ifdef TAP_DANCE_ENABLE
#    include "lib/tapdance.h"
#endif
#ifdef COMBO_ENABLE
#    include "g/keymap_combo.h"
#endif

// ALT TAB Timer
bool is_gui_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
// END ALT TAB Timer
uint16_t timer;

#define LAYOUT_FUN(...) LAYOUT_ortho_4x12(__VA_ARGS__)
#define ________________VIM_______________    KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_FUN(
  //,-----------------------------------------------------------------------------------------------------------.
       ADJUST,   MOD_Q,   LAY_W,   LAY_F,    KC_P,   MOD_B,   MOD_J,    KC_L,   LAY_U,   LAY_Y,    MINS,   FBSPC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
    OSL(_SYM),   MOD_A,   MOD_R,   MOD_S,   MOD_T,   MOD_G,   MOD_M,   MOD_N,   MOD_E,   MOD_I,   MOD_O,    QUOT,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
          ESC,   MOD_Z,   MOD_X,   MOD_C,   MOD_D,   MOD_V,   MOD_K,   MOD_H,MOD_COMM, MOD_DOT, MOD_SLSH, CW_TOGG,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+
         OSMC,    OSMG,    OSMA,  CW_TOGG,    BSPC,     ENT,    OSMS,     SPC,     TAB,     ESC,     ESC,     ESC
    ),
  [_SYM] = LAYOUT_FUN(
  //,-----------------------------------------------------.-----------------------------------------------------.
      _______,TD_TILDA, KC_SLSH, KC_COLN, KC_PLUS,      WQ, KC_PIPE, KC_AMPR, KC_ASTR, KC_QUES, KC_MINS, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      KC_PIPE,   KC_AT, KC_PERC, KC_EXLM,  KC_EQL, KC_PIPE, KC_COLN,  KC_EQL,  KC_DQT, KC_UNDS, KC_SCLN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______,     GRV, KC_HASH, KC_BSLS, TD_UPDIR,TD_UPDIR, KC_CIRC,  KC_DLR,  KC_DOT, _______, _______,
  //|--------+--------+--------+--------+--------+--------+---------+--------+--------+--------+--------+--------|
      _______, _______, _______,     GRV, MO(_BRK), _______,    _______, MO(_BRK), _______, _______, _______, _______
  ),
  [_BRK] = LAYOUT_FUN( // bracks on right, terminal stuff left
  //,-----------------------------------------------------.----------------------------------------------------.
      KC_MINS,   KC_LT,   KC_GT, KC_LCBR, KC_RCBR, _______,_______, KC_RCBR, KC_LCBR, KC_RBRC, KC_LBRC, _______,
  //|--------+--------+--------+--------+--------+--------|-------+--------+--------+--------+--------+--------|
      _______, _______, KC_LPRN, KC_RPRN,   KC_LT,   KC_GT,_______,  KC_DLR, KC_RPRN, KC_LPRN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|-------+--------+--------+--------+--------+--------|
      _______, _______, KC_LBRC, KC_RBRC, _______, _______,_______,   KC_GT, KC_MINS,   KC_LT, _______, _______,
  //|--------+--------+--------+--------+--------+--------+-------+--------+--------+--------+--------+--------
      _______, _______, _______, _______, KC_COLN, _______, KC_ENT, _______, QK_LEAD, _______, _______, _______
  ),
  [_NAV] = LAYOUT_FUN( //trying redundent mod placement for easier navigation
  //,-----------------------------------------------------.-----------------------------------------------------.
      _______,    OSMM,    OSMP,    OSMA,    OSMM, _______, KC_PGUP,  PRVTAB,  NXTTAB,  CMDTAB,  CMDGRV, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______,    OSMG,    OSMA,    OSMC,    OSMS,    OSMH, ________________VIM_______________, CW_TOGG,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, _______,    OSMG,    OSMA, _______, KC_PGDN, KC_HOME,  KC_END,   C_BSP, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+
      _______, _______, _______,    OSMM, _______, KC_LSFT, KC_LSFT,  KC_ENT,   A_BSP, _______, _______, _______
  ),

  [_NUM] = LAYOUT_FUN(
  //,-----------------------------------------------------.-----------------------------------------------------.
      _______,    OSMM,    OSMP, _______,    OSMM, _______,    KC_6,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|--------+---------+--------+-------+--------+--------|
      _______,    OSMG,    OSMA,    OSMC,    OSMS,    OSMH,    KC_0,    KC_4,    KC_5,    KC_6, KC_COLN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|--------+---------+--------+-------+--------+--------|
      _______, _______, _______, _______, _______, _______,  KC_DOT,    KC_1,    KC_2,    KC_3, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------+
      _______, _______, _______, _______, CW_TOGG,  KC_DOT, _______,   POPZED,  KC_DOT, _______, _______, _______
  ),


  [_FUNC] = LAYOUT_FUN(
  //,-----------------------------------------------------.-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______,    OSMG,    OSMA,    OSMC,    OSMS, _______, _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_FUN(
  //,-----------------------------------------------------.-----------------------------------------------------.
      _______, RGB_TOG, RGB_SAD, RGB_SAI, _______, QK_BOOT, _______, RGB_HUD, RGB_HUI, RGB_RMOD, RGB_MOD, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, RGB_SPD, RGB_SPI, _______, _______, KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
      _______, _______, RGB_VAD, RGB_VAI, _______, _______, KC_BRID, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, CG_TOGG, _______, _______, _______, _______, _______, _______, _______,  _______
  ),
};


// clang-format on

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // tap dance
#    ifdef TAP_DANCE_ENABLE
        // set tap dance keys to use a shorter tap term
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return TAPPING_TERM - 50;
#    endif
        case OSMS:
            return TAPPING_TERM + 50;
        // case BSPC: // still use permissive hold for ctrl
        //     return TAPPING_TERM - 50;
        // case SPC: // still use permissive hold for ctrl
        //     return TAPPING_TERM - 25;
        case MOD_A: // try high tapping term and permissive hold
        case MOD_R: // alt is annoying to trigger
        case MOD_H:
        case MOD_D:
            return TAPPING_TERM + 15;
        case MOD_S:
        case MOD_T:
            // return TAPPING_TERM - 10;
        // case MOD_G:

        // case MOD_M:
        case MOD_N:
        case MOD_E: // still use permissive hold for ctrl
            return TAPPING_TERM - 10;
        case MOD_I:
        case MOD_O: // this pinky lags behind the most, more than left pinky
            return TAPPING_TERM + 15;

        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // Home-row and other tight combos
        case esc_homer:
        case lesc:
        case lent:
        case alfred:
            return COMBO_TERM - 10;
        // case ctrl_bspc:
        // case ltab:
        // // case terminal:
        // case alt_bspc:
        // case colon:
        // case caps:
        // case nav_layer_toggle: // three keys takes more effort
        // one shot on top
        default: // this is pretty decent
            return COMBO_TERM;
    }
}
#endif

#ifdef COMBO_MUST_HOLD_PER_COMBO
bool get_combo_must_hold(uint16_t index, combo_t *combo) {
    // require this for anything that uses MO

    if (KEYCODE_IS_MOD(combo->keycode) || (combo->keycode >= QK_MOMENTARY && combo->keycode <= QK_MOMENTARY_MAX) // MO(kc) keycodes
    ) {
        return true;
    }

    return false;
}
#endif

#ifdef COMBO_MUST_TAP_PER_COMBO
bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    if (KEYCODE_IS_MOD(combo->keycode) || (combo->keycode >= QK_MOMENTARY && combo->keycode <= QK_MOMENTARY_MAX) // MO(kc) keycodes
    ) {
        return false;
    }
    return true;
}
#endif

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case BSPC:
        case ENT:
        // case MODLAY:
        case ESC:
        case TAB:
            // case MOD_SLSH:
            // case MOD_Z:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
#endif

#ifdef PERMISSIVE_HOLD_PER_KEY
// makes it a little difficult to manage with layer taps
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case BSPC:
            return true;
        default:
            return true;
    }
}
#endif

#ifdef CAPS_WORD_ENABLE
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // keycodes that continue caps word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // apply shift to next key.
            return true;

        // keycodes that continue caps word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
            return true;

        default:
            return false; // deactivate caps word.
    }
}
#endif

void matrix_scan_user(void) { // The very important timer.
#ifdef ACHORDION_ENABLE
    achordion_task();
#endif
    if (is_gui_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LGUI);
            is_gui_tab_active = false;
        }
    }
}

// repeat key setup stolen from precondition gist here: https://gist.github.com/NotGate/3e3d8ab81300a86522b2c2549f99b131
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef LAYER_LOCK_ENABLED
    if (!process_layer_lock(keycode, record, LLOCK)) {
        return false;
    }
#endif
#ifdef ACHORDION_ENABLE
    if (!process_achordion(keycode, record)) {
        return false;
    }
#endif
    // const uint8_t mods         = get_mods();
    // const uint8_t oneshot_mods = get_oneshot_mods();
    // hit transparent key, swap out and continue
    // if (!process_numlock(keycode, record)){
    //   return false;
    // }
    //
    // say oneshot is pressed and handle the interaction
    switch (keycode) {
        // not super useful
        // case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        //   return process_mod_hold(keycode, record);
        // OSM(mod) - One-shot mod
        // case CG_TOGG:
        //     if (record->event.pressed) {
        //         osx = !osx;
        //     }
        //     return false;
        case GRV:
            if (record->tap.count == 0) { // Key is being held.
                if (record->event.pressed) {
                    tap_code16(KC_GRV);
                    tap_code16(KC_GRV);
                    tap_code16(KC_GRV);
                }
                return false;
            }
            return true;
        // case BRACES: // Types [], {}, or <> and puts cursor between braces.
        //     if (record->event.pressed) {
        //         clear_mods(); // Temporarily disable mods.
        //         clear_oneshot_mods();
        //         if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
        //             SEND_STRING("{}");
        //         } else if ((mods | oneshot_mods) & MOD_MASK_CTRL) {
        //             SEND_STRING("()");
        //         } else if ((mods | oneshot_mods) & MOD_MASK_ALT) {
        //             SEND_STRING("<>");
        //         } else {
        //             SEND_STRING("[]");
        //         }
        //         tap_code(KC_LEFT); // Move cursor between braces.
        //         set_mods(mods);    // Restore mods.
        //     }
        //     return false;
        case WQ:
            if (record->event.pressed) {
                SEND_STRING(":wq");
                tap_code(KC_ENT);
            }
            return false;
        case CMDTAB:
            if (record->event.pressed) {
                if (!is_gui_tab_active) {
                    is_gui_tab_active = true;
                    register_code(KC_LGUI);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
        case CMDGRV:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                tap_code16_delay(KC_GRV, 100);
            } else {
                unregister_code(KC_LGUI);
            }
            break;
        case QUOT:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_QUOT);
                return false;
            }
            break;
    }
    return true;
};
