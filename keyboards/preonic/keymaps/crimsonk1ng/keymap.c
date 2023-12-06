/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "action_code.h"
#include "action_util.h"
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "lib/keycodes.h"

#include <stdio.h>
// #include "lib/oneshot.h"
#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif
#ifdef LAYER_LOCK_ENABLED
#    include "lib/layer_lock.h"
#endif
#ifdef TAP_DANCE_ENABLE
#    include "lib/tapdance.h"
#endif
#ifdef COMBO_ENABLE
#    include "g/keymap_combo.h"
#endif
#ifdef ACHORDION_ENABLE
#    include "lib/achordion.h"
#endif

// ALT TAB Timer
bool     is_gui_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
// END ALT TAB Timer
uint16_t timer;
// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  [_BASE] = LAYOUT_preonic_grid(
     KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,      KC_9,      KC_0,      KC_DEL,

     ADJUST,    KC_Q,   LAY_W,   LAY_F,   KC_P,    KC_B,    KC_J,    KC_L,    LAY_U,     LAY_Y,     KC_SCLN,    HBSPC,

  OSL(_SYM),   MOD_A,   MOD_R,   MOD_S,   MOD_T,   MOD_G,   MOD_M,   MOD_N,   MOD_E,     MOD_I,     MOD_O,      QUOT,

        ESC,   MOD_Z,   MOD_X,   MOD_C,   MOD_D,    KC_V,   KC_K,    MOD_H,   MOD_COMM,  MOD_DOT,   MOD_SLSH,   OSL(_SYM),

        ENT,    OSMM,    OSMH,   OSL(_SYM),     BSPC,    ENT,   OSMS,     SPC,    TAB,      KC_DOWN,   KC_UP,     ENT
  ),

  [_SYM] = LAYOUT_preonic_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_TILD, KC_SLSH, KC_COLN, KC_PLUS,      WQ, KC_PIPE, KC_AMPR, KC_ASTR, KC_QUES, KC_BSLS, _______,
    KC_PIPE,   KC_AT, KC_PERC, KC_EXLM,  KC_EQL, KC_PIPE, KC_COLN,  KC_EQL,  KC_DQT, KC_UNDS, KC_SCLN, KC_SCLN,
    _______, _______,     GRV, KC_MINS, KC_BSLS, _______,TD_UPDIR, KC_CIRC,  KC_DLR, _______, _______, _______,
    _______, _______, _______, _______, KC_COLN, _______, _______, _______, _______, _______, _______, _______
  ),

  [_BRK] = LAYOUT_preonic_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,   KC_LT,   KC_GT, KC_LCBR, KC_RCBR, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_LPRN, KC_RPRN,   KC_LT,   KC_GT, _______, _______, _______, _______, _______, _______,
    _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_NAV] = LAYOUT_preonic_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,    OSMM,    OSMP,    OSMA, _______, KC_PGUP,  PRVTAB,  NXTTAB,  CMDTAB,  CMDGRV, KC_BSPC,
       OSMH,    OSMG,    OSMA,    OSMC,    OSMS, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, _______, _______,
    _______, _______, _______,    OSMG,    OSMA, _______, KC_PGDN, KC_HOME,  KC_END,   C_BSP, _______, _______,
    _______, _______, _______, _______, KC_LGUI, KC_LCTL, _______, KC_ENTER, _______, _______, _______, _______
  ),

  [_NUM] = LAYOUT_preonic_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    _______,    OSMM,    OSMP, _______,    OSMG, _______, _______,    KC_7,    KC_8,    KC_9, _______, _______,
       OSMH,    OSMG,    OSMA,    OSMC,    OSMS, _______, _______,    KC_4,    KC_5,    KC_6, KC_COLN, _______,
    _______, _______, _______, _______, _______, _______, _______,    KC_1,    KC_2,    KC_3, KC_SLSH, _______,
    _______, _______, _______, _______, CW_TOGG, KC_DOT, _______, KC_0, _______, _______, _______, _______
  ),

  [_FUNC] = LAYOUT_preonic_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
    _______, _______, _______, _______, _______, _______, _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,
    _______, _______, _______, _______, _______, _______, _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_preonic_grid(
    _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SPI, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
    _______, _______, _______, RGB_VAD, RGB_VAI, RGB_SPD, _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  )


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
            // MIDDLE
            //
        case MODLAY:
        case MOD_A: // try high tapping term and permissive hold
        case MOD_R: // alt is annoying to trigger
        case MOD_S:
        case MOD_T:
        case MOD_G:

        case LAY_U:
        case LAY_Y:

        case MOD_M:
        case MOD_N:
        case MOD_E: // still use permissive hold for ctrl
        case MOD_I:
        case MOD_O: // this pinky lags behind the most, more than left pinky
        case QUOT:
            // bottom row
        case MOD_V:
        case MOD_K:

            return false;
        default:
            return true;
    }
}
#endif

#ifdef CAPS_WORD_ENABLE
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
            return true;

        default:
            return false; // Deactivate Caps Word.
    }
}
#endif

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
        case EXLM:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_EXLM);
                return false;
            }
            break;
        case DQT:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_DQT);
                return false;
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

void matrix_scan_user(void) {}
