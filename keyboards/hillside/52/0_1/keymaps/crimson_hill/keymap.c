#include "quantum.h"
#include QMK_KEYBOARD_H
#include "keycodes.h"

#ifdef COMBO_ENABLE
#    include "g/keymap_combo.h"
#endif

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

#define xxxxxxx KC_NO
// ALT TAB Timer
bool     is_gui_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer     = 0;     // we will be using them soon.
// END ALT TAB Timer
uint16_t timer;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
     ADJUST,  MOD_Q,    MOD_W,    MOD_F,    MOD_P,    MOD_B,                                   MOD_J,    MOD_L,    MOD_U,    MOD_Y,     MINS,    KC_BSPC,
     MODLAY,  MOD_A,    MOD_R,    MOD_S,    MOD_T,    MOD_G,                                   MOD_M,    MOD_N,    MOD_E,    MOD_I,    MOD_O,    QUOT,
     CW_TOGG, MOD_Z,    MOD_X,    MOD_C,    MOD_D,    MOD_V, BRACKS,               BRACKS, MOD_K,    MOD_H,    MOD_COMM, MOD_DOT,  MOD_SLSH,   CW_TOGG,
     KC_MUTE, KC_ESC,  KC_LCTL,         KC_LGUI, KC_LALT, BSPC, ENT,       OSMS ,   SPC ,   TAB, KC_RGUI,                   KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_SYM] = LAYOUT(
     _______, KC_TILD, KC_SLSH, KC_COLN, KC_PLUS, KC_BSLS,                                        _______, KC_AMPR, KC_ASTR, KC_QUES, KC_MINS, _______,
     _______,   KC_AT, KC_PERC, KC_EXLM,  KC_EQL, KC_PIPE,                                        _______,  KC_EQL,  KC_DQT, KC_UNDS, KC_SCLN, _______,
     _______,     GRV,  KC_GRV, KC_HASH,   KC_LT,   KC_GT, _______,                      _______, KC_SCLN, KC_CIRC,  KC_DLR,  KC_DOT, _______, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
    [_BRK] = LAYOUT(
     _______,   KC_LT,   KC_GT, KC_LCBR, KC_RCBR, _______,                                        _______, KC_RCBR, KC_LCBR, _______, _______, _______,
     _______,   KC_AT, KC_LPRN, KC_RPRN, KC_MINS, _______,                                        _______, KC_RPRN, KC_LPRN,  KC_EQL, _______, _______,
     _______, _______, KC_LBRC, KC_RBRC, _______, _______, _______,                      _______, _______, KC_RBRC, KC_LBRC, _______, _______, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
    [_NAV] = LAYOUT(
     _______, _______, _______,    OSMA,    OSMM, _______,                                        KC_PGUP,  PRVTAB,  NXTTAB,  CMDTAB,  CMDGRV, KC_BSPC,
     _______, _______,    OSMA,    OSMC,    OSMG,    OSMH,                                        KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, _______, _______,
     _______, _______, _______,    OSMA,    OSMS, _______, _______,                      _______, KC_PGDN, KC_HOME,  KC_END,   C_BSP, _______, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, KC_ENT, _______,          _______, _______, _______
    ),
    [_NUM] = LAYOUT(
     _______, _______,    OSMP, _______,    OSMM, _______,                                        _______,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
     _______,    OSMG,    OSMA,    OSMC,    OSMS,    OSMH,                                        _______,    KC_4,    KC_5,    KC_6, KC_COLN, KC_BSLS,
     _______, _______, _______, _______, _______, _______, _______,                      _______, _______,    KC_1,    KC_2,    KC_3, KC_SLSH, _______,
     _______, _______, _______,          _______, _______, CW_TOGG, _______,    _______, KC_0, KC_DOT, _______,          _______, _______, _______
    ),
    [_FUNC] = LAYOUT(
     _______, _______, _______, _______, _______, _______,                                        _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
     _______, _______, _______, _______, _______, _______,                                        _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,
     _______, _______, _______, _______, _______, _______, _______,                      _______, _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,
     _______, _______, _______,          _______, _______, _______, _______,    _______, _______, _______, _______,          _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
     xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, QK_BOOT,                                        xxxxxxx, UG_HUED, UG_HUEU, UG_PREV, UG_NEXT, xxxxxxx,
     xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                                        KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT, xxxxxxx, xxxxxxx,
     xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,                      xxxxxxx, KC_BRID, KC_VOLD, KC_MUTE, KC_VOLU, xxxxxxx, xxxxxxx,
     xxxxxxx, xxxxxxx, xxxxxxx,          xxxxxxx, xxxxxxx, xxxxxxx, _______,    _______, xxxxxxx, xxxxxxx, xxxxxxx,          xxxxxxx, xxxxxxx, xxxxxxx
    ),
    [_GAME] = LAYOUT(
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
     KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_QUOT,                      KC_SLSH, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_RSFT,
     KC_MUTE, KC_ESC,  KC_LCTL,          KC_LGUI, KC_LCTL,  KC_SPC, _______,    _______ ,KC_SPC , KC_LALT, KC_RGUI,          KC_LEFT, KC_DOWN, KC_RGHT
    )
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
        case MOD_R: // alt is annoying to trigger
            return TAPPING_TERM + 25;
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
            return TAPPING_TERM - 10;
        case MOD_I:
        case MOD_O: // this pinky lags behind the most, more than left pinky
            return TAPPING_TERM + 25;

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
        case lent:
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
