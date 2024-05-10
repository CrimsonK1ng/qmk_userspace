/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#ifdef TAP_DANCE_ENABLE
#    include "lib/tapdance.h"
#endif
#ifdef COMBO_ENABLE
#    include "g/keymap_combo.h"
#endif
#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif

bool     is_gui_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
// END ALT TAB Timer
uint16_t timer;

// clang-format off

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QMK_BASE] = LAYOUT_ansi_69(
        ADJUST,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,   KC_7,     KC_8,    KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,          KC_MUTE,
        KC_TAB,  MOD_Q,   LAY_W,    LAY_E,   MOD_R,   MOD_T,            MOD_Y,    KC_U,   LAY_I,    LAY_O,        KC_P,   HBSPC,    MBSPC, KC_BSLS,  KC_DEL,
     OSL(_SYM),  MOD_A,   MOD_S,    MOD_D,   MOD_F,   MOD_G,            MOD_H,   MOD_J,   MOD_K,    MOD_L,    MOD_SCLN,  KC_QUOT,  KC_ENT,          KC_HOME,
       KC_LSFT,  MOD_Z,   MOD_X,    MOD_C,   MOD_V,   MOD_B,            MOD_B,   MOD_N,   MOD_M, MOD_COMM,     MOD_DOT, MOD_SLSH,  KC_RSFT,  KC_UP,
       QK_LEAD, KC_LOPT,            CW_TOGG,    BSPC,   ENT,             OSMS,         SPC,           TAB,                        KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_69(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_DEL,
        KC_LCTL, KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,           KC_HOME,
        KC_LSFT, KC_Z,     KC_X,     KC_C,    KC_V,          KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT, KC_UP,
        KC_LCTL, KC_LWIN,  KC_LALT,         KC_SPC,        KC_ENT, OSMS,            SPC,            KC_RALT,            KC_LEFT, KC_DOWN, KC_RGHT),

    [_SYM] = LAYOUT_ansi_69(
        KC_ESC,      KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,     KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,   KC_BSPC,          KC_MUTE,
        _______, TD_TILDA,  KC_SLSH,  KC_COLN, KC_PLUS,      WQ,           KC_PIPE,  KC_AMPR, KC_ASTR, KC_QUES, KC_MINS,  _______,  _______, _______, _______,
        KC_PIPE,    KC_AT,  KC_PERC,  KC_EXLM,  KC_EQL, KC_PIPE,           KC_COLN,   KC_EQL,  KC_DQT, KC_UNDS, KC_SCLN,  KC_BSLS,  _______,          _______,
        _______,  _______,      GRV, KC_HASH, KC_BSLS, TD_UPDIR,          TD_UPDIR, TD_UPDIR, KC_CIRC,  KC_DLR,  KC_DOT,  _______,  _______, _______,
        _______,  _______,           _______, _______,  _______,           _______,  _______, _______,                    _______,  _______, _______),

    [_BRK] = LAYOUT_ansi_69(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          RGB_TOG,
        KC_MINS,   KC_LT,    KC_GT,  KC_LCBR, KC_RCBR, _______,           _______, _______, _______, _______,  _______,  _______,  _______, _______, _______,
        _______, _______,  KC_LPRN,  KC_RPRN,   KC_LT,   KC_GT,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, _______,  KC_LBRC, KC_RBRC,  _______, _______,           _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [_NAV] = LAYOUT_ansi_69(
        _______, _______,  _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          RGB_TOG,
        _______,    OSMM,     OSMP,     OSMA, _______, _______,           KC_PGUP,  PRVTAB,  NXTTAB,  CMDTAB,   CMDGRV,  KC_BSPC,  _______, _______, _______,
           OSMH,    OSMG,     OSMA,     OSMC,    OSMS, _______,           KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,  _______,  _______,  _______,          _______,
        _______, _______,     OSMG,     OSMA, _______, _______,           _______, KC_PGDN, KC_HOME,  KC_END,    C_BSP,  _______,  _______, _______,
        _______, _______,  _______,           KC_LCTL,          KC_LGUI,  KC_LSFT,              ENT,             A_BSP,            _______, _______, _______),

    [_NUM] = LAYOUT_ansi_69(
        KC_ESC,     KC_1,     KC_2,     KC_3,    KC_4,    KC_5,   KC_6,      KC_7,    KC_8,    KC_9,    KC_0,  KC_MINS,   KC_EQL,  KC_BSPC,          KC_MUTE,
        _______,    OSMM,     OSMP,  _______, _______, _______,           _______,    KC_7,    KC_8,    KC_9,  KC_MINS,  KC_BSPC,  _______, _______, _______,
           OSMH,    OSMG,     OSMA,     OSMC,    OSMS, _______,           _______,    KC_4,    KC_5,    KC_6,  KC_COLN,  KC_BSLS,  _______,          _______,
        _______,           _______,  _______, _______, _______, _______,  _______,  KC_DOT,    KC_1,    KC_2,     KC_3,  KC_SLSH,  _______, _______,
        _______, _______,  _______,           CW_TOGG,           KC_DOT,  _______,           POPZED,           _______,            _______, _______, _______),

    [_FUNC] = LAYOUT_ansi_69(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   _______,          _______,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______,  _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, _______,  _______, _______, _______, _______,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______),

    [_ADJUST] = LAYOUT_ansi_69(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   QK_BOOT,          _______,
        RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, RGB_HUD, RGB_HUI, RGB_RMOD,  RGB_MOD, _______,  _______,  _______,  _______,          _______,
        _______, RGB_RMOD, RGB_VAD,  RGB_HUD, RGB_SAD, RGB_SPD,           KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT,  _______,  _______,  _______,          _______,
        _______,           _______,  _______, _______, _______, _______,  KC_BRID, KC_VOLD, KC_MUTE, KC_VOLU,  _______,  _______,  _______, _______,
        _______, _______,  _______,           _______,          _______,  _______,          _______,           _______,            _______, _______, _______)
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [QMK_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_SYM] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_BRK] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_NAV] = {ENCODER_CCW_CW(_______, _______)},
    [_NUM] = {ENCODER_CCW_CW(_______, _______)},
    [_FUNC] = {ENCODER_CCW_CW(_______, _______)},
    [_ADJUST] = {ENCODER_CCW_CW(_______, _______)}
};
#endif // ENCODER_MAP_ENABLE

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
        case MOD_S: // alt is annoying to trigger
            return TAPPING_TERM + 15;
        case MOD_D:
        case MOD_F:
            // return TAPPING_TERM - 10;
        // case MOD_G:

        // case MOD_M:
        case MOD_J:
        case MOD_K: // still use permissive hold for ctrl
            return TAPPING_TERM - 10;
        case MOD_L:
        case MOD_SCLN: // this pinky lags behind the most, more than left pinky
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
        case tab:
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
        case MOD_S: // alt is annoying to trigger
        case MOD_D:
        case MOD_F:
        case MOD_G:

        case LAY_I:
        case LAY_O:

        case MOD_H:
        case MOD_J:
        case MOD_K: // still use permissive hold for ctrl
        case MOD_L:
        case MOD_SCLN: // this pinky lags behind the most, more than left pinky
        case QUOT:
            // bottom row
        case MOD_V:
        case MOD_M:

            return false;
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

#ifdef SWAP_HANDS_ENABLE
__attribute__((weak)) const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    // Left
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}},
    // Right
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}}};
#endif

#ifdef LEADER_ENABLE
void send_os_mod(uint16_t keycode) {
    switch (detected_host_os()) {
        case OS_LINUX:
        case OS_WINDOWS:
            tap_code16(C(keycode));
            break;
        case OS_MACOS:
            tap_code16(G(keycode));
            break;
        default:
            break;
    }
}
void leader_end_user(void) {
    if (leader_sequence_one_key(KC_W)) {
        SEND_STRING(":wq" SS_TAP(X_ENT));
    } else if (leader_sequence_one_key(KC_V)) {
        send_os_mod(KC_V);
    } else if (leader_sequence_one_key(KC_C)) {
        send_os_mod(KC_C);
    } else if (leader_sequence_one_key(KC_T)) {
        SEND_STRING(SS_LALT("t"));
    } else if (leader_sequence_two_keys(KC_F, KC_R)) {
        SEND_STRING(":%s///g" SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT));
    } else if (leader_sequence_two_keys(KC_G, KC_O)) {
        SEND_STRING("if err != nil {}" SS_TAP(X_LEFT) SS_TAP(X_ENTER));
    } else if (leader_sequence_two_keys(KC_X, KC_X)) {
        SEND_STRING("| xargs -I {} \\;" SS_TAP(X_LEFT) SS_TAP(X_LEFT));
    } else if (leader_sequence_two_keys(KC_V, KC_V)) {
        send_os_mod(S(KC_V));
    } else if (leader_sequence_two_keys(KC_C, KC_C)) {
        send_os_mod(S(KC_C));
    } else if (leader_sequence_two_keys(KC_G, KC_P)) {
        SEND_STRING("git push origin main");
    } else if (leader_sequence_two_keys(KC_G, KC_C)) {
        SEND_STRING("git commit -m \"\"" SS_TAP(X_LEFT));
    } else if (leader_sequence_two_keys(KC_T, KC_T)) {
        SEND_STRING("```" SS_TAP(X_ENTER) SS_TAP(X_ENTER) "```" SS_TAP(X_UP));
    }
}
#endif
