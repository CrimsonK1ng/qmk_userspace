#include "quantum.h"
#include QMK_KEYBOARD_H
#include "keycodes.h"

#ifdef COMBO_ENABLE
#    include "g/keymap_combo.h"
#endif
#ifdef ACHORDION_ENABLE
# include "features/achordion.h"
#endif
// MACROS
enum custom_keycodes {
    // some custom keys
    OSX = SAFE_RANGE,
    // LLOCK,
    WQ,
    UPDIR,
    CMDGRV,
    CMDTAB,
    ALTTAB,
    BRKS,
    CURLS,
    PARS,
};

#define xxxxxxx KC_NO
// ALT TAB Timer
bool     is_gui_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
// END ALT TAB Timer
uint16_t timer;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
     ADJUST,  MOD_Q,    MOD_W,    MOD_F,    MOD_P,    MOD_B,                                   MOD_J,    MOD_L,    MOD_U,    MOD_Y,    MINS,    KC_BSPC,
     MODLAY,  MOD_A,    MOD_R,    MOD_S,    MOD_T,    MOD_G,                                   MOD_M,    MOD_N,    MOD_E,    MOD_I,    MOD_O,    QUOT,
     CW_TOGG, MOD_Z,    MOD_X,    MOD_C,    MOD_D,    MOD_V, KC_QUES,               KC_DQT,    MOD_K,    MOD_H,    MOD_COMM, MOD_DOT,  MOD_SLSH,   CW_TOGG,
     KC_DEL, KC_VOLD,  KC_VOLU,      OSL(_NUM),  OSL(_SYM), BSPC, ENT,       OSMS,   SPC , OSL(_SYM), KC_TAB,    PARS, CURLS,    BRKS
    ),
    [_SYM] = LAYOUT(
     KC_TILD, KC_BSLS, KC_SLSH, KC_COLN, KC_PLUS,     GRV,                                            GRV, KC_AMPR, KC_ASTR, KC_QUES, KC_BSLS, _______,
     _______,   KC_AT, KC_PERC,    EXLM,  KC_EQL, KC_PIPE,                                        KC_HASH,  KC_EQL,     DQT, KC_UNDS, KC_SCLN, KC_QUOT,
     _______, KC_HASH, KC_MINS,   KC_LT,   KC_GT, KC_QUES, KC_LBRC,                      KC_RBRC,   UPDIR, KC_CIRC,  KC_DLR,  KC_DOT, _______, _______,
     _______, _______, _______,          _______, OSL(_LBRK), _______, _______,    _______, _______, OSL(_RBRK), _______,          _______, _______, _______
    ),
    [_NAV] = LAYOUT(
     _______, _______, _______,    OSMA,    OSMM, _______,                                        KC_PGUP,  PRVTAB,  NXTTAB,  CMDTAB,  CMDGRV, KC_BSPC,
     _______, _______,    OSMA,    OSMC,    OSMG,    OSMH,                                        KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, _______, _______,
     _______, _______, _______,    OSMA,    OSMS, _______, _______,                      _______, KC_PGDN, KC_HOME,  KC_END,   C_BSP, _______, _______,
     _______, _______, _______,          _______, _______,   SBSPC, _______,    _______,     ENT, _______, _______,          _______, _______, _______
    ),
    [_NUM] = LAYOUT(
     _______, _______,    OSMP, _______,    OSMM, _______,                                        KC_PLUS,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
     _______, _______,    OSMA,    OSMC,    OSMG,    OSMH,                                        KC_LBRC,    KC_4,    KC_5,    KC_6, KC_COLN, _______,
     _______, _______, _______, _______,    OSMS, _______, _______,                      _______, KC_RBRC,    KC_1,    KC_2,    KC_3, KC_SLSH, _______,
     _______, _______, _______,          _______, KC_LBRC,   SBSPC, KC_DOT,    _______, KC_0, KC_DOT, KC_RBRC,          _______, _______, _______
    ),
    [_NUMLINE] = LAYOUT(
     _______,    KC_0,    KC_7,    KC_8,    KC_9, KC_PLUS,                                        _______, KC_RCBR, KC_LCBR, _______, _______, _______,
     _______,    KC_0,    KC_1,    KC_2,    KC_3, KC_COLN,                                        _______, KC_RPRN, KC_LPRN, _______, _______, _______,
     _______, _______,    KC_4,    KC_5,    KC_6, _______, _______,                      _______, _______, KC_RBRC, KC_LBRC, _______, _______, _______,
     _______, _______, _______,          _______,    KC_0, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
     xxxxxxx,MO(_FUNC), xxxxxxx, xxxxxxx, xxxxxxx, QK_BOOT,                                        xxxxxxx, UG_HUED, UG_HUEU, UG_PREV, UG_NEXT, xxxxxxx,
     xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                                        KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT, xxxxxxx, xxxxxxx,
     xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                      xxxxxxx, KC_BRID, KC_VOLD, KC_MUTE, KC_VOLU, xxxxxxx, xxxxxxx,
     xxxxxxx, xxxxxxx, xxxxxxx,          xxxxxxx, xxxxxxx, xxxxxxx, _______,    _______, xxxxxxx, xxxxxxx, xxxxxxx,          xxxxxxx, xxxxxxx, xxxxxxx
    ),
    [_FUNC] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                        _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
     _______, _______, _______, _______, _______, _______,                                        _______,   KC_F4,   KC_F5,   KC_F6,  KC_F11, _______,
     _______, _______, _______, _______, _______, _______, _______,                      _______, _______,   KC_F1,   KC_F2,   KC_F3,  KC_F12, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
    [_LBRK] = LAYOUT(
     _______, _______, KC_LCBR, KC_RCBR, _______, _______,                                        _______, _______, _______, _______, _______, _______,
     _______, _______, KC_LPRN, KC_RPRN, _______, _______,                                        _______, _______, _______, _______, _______, _______,
     _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
    [_RBRK] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                        _______, _______, KC_RCBR, KC_LCBR, _______, _______,
     _______, _______, _______, _______, _______, _______,                                        _______, _______, KC_RPRN, KC_LPRN, _______, _______,
     _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, KC_RBRC, KC_LBRC, _______, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
};

//  Template:
//    [_INDEX] = LAYOUT(
//     _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
//    ),

// clang-format on

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OSMS:
            return TAPPING_TERM + 50;
        // case BSPC: // still use permissive hold for ctrl
        //     return TAPPING_TERM - 50;
        // case SPC: // still use permissive hold for ctrl
        //     return TAPPING_TERM - 25;
        case MOD_A: // try high tapping term and permissive hold
            return TAPPING_TERM + 25;
        case MOD_R: // alt is annoying to trigger
        case MOD_S:
        case MOD_T:
            return TAPPING_TERM - 10;
        // case MOD_G:
        case MOD_H:
        case MOD_D:
            return TAPPING_TERM + 15;

        // case MOD_M:
        case MOD_N:
        case MOD_E: // still use permissive hold for ctrl
        case MOD_I:
            return TAPPING_TERM - 10;
        case MOD_O: // this pinky lags behind the most, more than left pinky
            return TAPPING_TERM + 25;

        case DQT:
        case EXLM:
            return TAPPING_TERM - 25;

        default:
            return TAPPING_TERM;
    }
}
#endif

#ifdef COMBO_TERM_PER_COMBO
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // Home-row and other tight combos
        case resc:
        case lesc:
        case rent:
        case ctrl_bspc:
        case alt_bspc:
            return COMBO_TERM - 10;
        default: // this is pretty decent
            return COMBO_TERM;
    }
}
#endif

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ENT:
        case ESC:
        case TAB:
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
        case ENT:
        case MOD_R: // symbol layer
        case MOD_I: // symbol layer
            return true;
        default:
            return false;
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

void housekeeping_task_user(void) {
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
#ifdef ACHORDION_ENABLE
    if (!process_achordion(keycode, record)) {
        return false;
    }
#endif
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
        case UPDIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;
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
        case PARS:
            if (record->event.pressed) {
                tap_code16(KC_LPRN);
                tap_code16(KC_RPRN);
            }
            break;
        case CURLS:
            if (record->event.pressed) {
                tap_code16(KC_LCBR);
                tap_code16(KC_RCBR);
            }
            break;
        case BRKS:
            if (record->event.pressed) {
                tap_code16(KC_LBRC);
                tap_code16(KC_RBRC);
            }
            break;
        case DQT:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_DQT); // Send KC_DQUO on tap
                return false;       // Return false to ignore further processing of key
            }
            break;
        case EXLM:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_EXLM); // Send KC_DQUO on tap
                return false;        // Return false to ignore further processing of key
            }
            break;
    }
    return true;
};

#ifdef ACHORDION_ENABLE
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    // Exceptionally consider the following chords as holds, even though they
    // are on the same hand in Dvorak.
    switch (tap_hold_keycode) {
        case MOD_W:
            switch (other_keycode) {
                case MOD_F:
                case MOD_P:
                case MOD_S:
                case MOD_T:
                    return true;
            }
            break;
        case MOD_F:
            switch (other_keycode) {
                case MOD_W:
                case MOD_P:
                    return true;
            }
            break;
        case MOD_Z:
            switch (other_keycode) {
                case MOD_X:
                case MOD_C:
                case MOD_D:
                case MOD_V:
                case MOD_F:
                case MOD_S:
                case MOD_T:
                case MOD_G:
                case MOD_B:
                    return true;
            }
            break;
        case MOD_X:
            switch (other_keycode) {
                case MOD_C:
                case MOD_D:
                case MOD_V:
                case MOD_S:
                case MOD_T:
                case MOD_G:
                    return true;
            }
            break;
        case MOD_C:
            switch (other_keycode) {
                case MOD_T:
                    return true;
            }
            break;
        case MOD_T:
            switch (other_keycode) {
                case MOD_S:
                case MOD_R:
                case MOD_A:
                case MOD_F:
                case MOD_W:
                case MOD_Q:
                case MOD_C:
                case MOD_V:
                    return true;
            }
            break;
        case MOD_S:
            switch (other_keycode) {
                case MOD_T:
                case MOD_D:
                case MOD_X:
                    return true;
            }
            break;
        case MOD_R:
            switch (other_keycode) {
                case MOD_S:
                case MOD_T:
                case MOD_G:
                case MOD_F:
                case MOD_P:
                case MOD_C:
                case MOD_D:
                    return true;
            }
            break;
        case MOD_A:
            switch (other_keycode) {
                case MOD_R:
                case MOD_T:
                case MOD_C:
                case MOD_S:
                case MOD_G:
                    return true;
            }
            break;
        // END LEFT
        // START RIGHT
        case MOD_SLSH:
            switch (other_keycode) {
                case MOD_L:
                case MOD_U:
                case MOD_N:
                    return true;
            }
            break;
        case MOD_N:
            switch (other_keycode) {
                case MOD_U:
                    return true;
            }
            break;
        case MOD_E:
            switch (other_keycode) {
                case MOD_L:
                case MOD_N:
                    return true;
            }
            break;
        case MOD_I:
            switch (other_keycode) {
                case MOD_L:
                case MOD_U:
                case MOD_E:
                case MOD_N:
                case MOD_COMM:
                case MOD_H:
                    return true;
            }
            break;

        // SPECIAL CASE
        case ADJUST:
        case QUOT:
            return true;
            break;

    }

    switch (other_keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            other_keycode &= 0xff;  // Get base keycode.
    }
    // Allow same-hand holds with non-alpha keys.
    if (other_keycode > KC_Z) { return true; }

    // Also allow same-hand holds when the other key is in the rows below the
    // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
    if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 3) { // I think it is 3 because 8 / 2 == 4 so > 3 is bottom
        return true;
    }

    // Otherwise, follow the opposite hands rule.
    return achordion_opposite_hands(tap_hold_record, other_record);
}
#endif
