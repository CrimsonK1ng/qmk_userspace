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

// clang-format off

/*
NOTES: swap_lctl_lgui is available in the keymap_config struct and will tell us if it is enabled
*/

#define LAYOUT_FUN(...) LAYOUT_split_3x6_3(__VA_ARGS__)
// #define ____________ONESHOTS______________    OSMA, OSMC,  OSMG, OSMS
#define ________________VIM_______________    KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT
// ALT TAB Timer
bool is_gui_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.
// END ALT TAB Timer
uint16_t timer;
// bool numlock = false;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_FUN(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ADJUST,   MOD_Q,   LAY_W,   LAY_F,    KC_P,   MOD_B,                        MOD_J,    KC_L,   LAY_U,   LAY_Y,    MINS,   FBSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    OSL(_SYM),   MOD_A,   MOD_R,   MOD_S,   MOD_T,   MOD_G,                        MOD_M,   MOD_N,   MOD_E,   MOD_I,   MOD_O,    QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
          ESC,   MOD_Z,   MOD_X,   MOD_C,   MOD_D,   MOD_V,                        MOD_K,   MOD_H,MOD_COMM, MOD_DOT, MOD_SLSH, QK_REP,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CW_TOGG,    BSPC,     ENT,       OSMS,     SPC,  TAB
                                      //`--------------------------'  `--------------------------'

  ),

  [_SYM] = LAYOUT_FUN(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,TD_TILDA, KC_SLSH, KC_COLN, KC_PLUS,      WQ,                      KC_PIPE, KC_AMPR, KC_ASTR, KC_QUES, KC_MINS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_PIPE,   KC_AT, KC_PERC, KC_EXLM,  KC_EQL, KC_PIPE,                      KC_COLN,  KC_EQL,  KC_DQT, KC_UNDS, KC_SCLN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______,     GRV, KC_HASH, KC_BSLS, TD_UPDIR,                    TD_UPDIR, KC_CIRC,  KC_DLR,  KC_DOT, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              GRV, _______, MO(_BRK),  MO(_BRK), _______, _______
                                       //`--------------------------'  `--------------------------'
  ),

  [_BRK] = LAYOUT_FUN( // bracks on right, terminal stuff left
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_MINS,   KC_LT,   KC_GT, KC_LCBR, KC_RCBR, _______,                      _______, KC_RCBR, KC_LCBR,   KC_GT,   KC_LT, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, KC_LPRN, KC_RPRN, KC_MINS, _______,                      _______, _______, KC_RPRN, KC_LPRN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, KC_LBRC, KC_RBRC, _______, _______,                      _______, _______, KC_RBRC, KC_LBRC, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_COLN, _______,   _______, _______, _______
                                       //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_FUN( //trying redundent mod placement for easier navigation
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    OSMM,    OSMP,    OSMA,    OSMM, _______,                      KC_PGUP,  PRVTAB,  NXTTAB,  CMDTAB,  CMDGRV, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    OSMG,    OSMA,    OSMC,    OSMS,    OSMH,                      ________________VIM_______________, CW_TOGG,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______,    OSMG,    OSMA, _______,                      KC_PGDN, KC_HOME,  KC_END,   C_BSP, _______,    OSMH,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                             OSMH, _______, KC_LSFT,    KC_LSFT,  KC_ENT, A_BSP
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT_FUN(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______,    OSMP, _______,    OSMM, _______,                         KC_6,    KC_7,    KC_8,    KC_9, KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+---------+--------+-------+--------+--------|
      _______,    OSMG,    OSMA,    OSMC,    OSMS,    OSMH,                         KC_0,    KC_4,    KC_5,    KC_6, KC_COLN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+---------+--------+-------+--------+--------|
      _______, _______, _______, _______, _______, _______,                       KC_DOT,    KC_1,    KC_2,    KC_3, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  --------+--------+--------+--------+--------+--------+--------|
                                          _______, CW_TOGG, KC_DOT,    _______,   POPZED, KC_DOT
                                       //`--------------------------'  `--------------------------'
  ),


  [_FUNC] = LAYOUT_FUN(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      _______,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                      _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    OSMG,    OSMA,    OSMC,    OSMS, _______,                      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                       //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_FUN(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, RGB_TOG, RGB_SAD, RGB_SAI, _______, QK_BOOT,                      _______, RGB_HUD, RGB_HUI, RGB_RMOD, RGB_MOD, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, RGB_SPD, RGB_SPI, _______, _______,                      KC_BRIU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, RGB_VAD, RGB_VAI, _______, _______,                      KC_BRID, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CG_TOGG, _______,  _______,    _______, _______,  _______
                                      //`--------------------------'  `--------------------------'
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
/*
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
        case MOD_D:
        case MOD_K:
        case MOD_H:

            return false;
        default:
            return true;
*/
    }
}
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // if (!is_keyboard_master()) {
    //   return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
    // }
    return OLED_ROTATION_90;
    // return rotation;
}

bool oled_render_layer(void) {
    // Host Keyboard Layer Status
    // enum {
    //     OS_UNSURE,
    //     OS_LINUX,
    //     OS_WINDOWS,
    //     OS_MACOS,
    //     OS_IOS,
    // } os_variant_t;
    switch (detected_host_os()) {
        case OS_LINUX:
            oled_write_P(PSTR("UNIX\n"), false);
            break;
        case OS_WINDOWS:
            oled_write_P(PSTR(" WIN\n"), false);
            break;
        case OS_MACOS:
            oled_write_P(PSTR(" MAC\n"), false);
            break;
        default:
            oled_write_P(PSTR("VOID\n"), false);
            break;
    }
    // oled_write_P((osx) ? PSTR("MAC \n") : PSTR("UNIX\n"), false);
    oled_write_P(PSTR("----\n"), false);
    uint8_t layer = get_highest_layer(layer_state);
    oled_write_P((layer == _BASE) ? PSTR("BASE\n") : PSTR("\n"), false);
    oled_write_P((layer == _SYM) ? PSTR("SYM\n") : PSTR("\n"), false);
    oled_write_P((layer == _BRK) ? PSTR("BRK\n") : PSTR("\n"), false);
    oled_write_P((layer == _NAV) ? PSTR("NAV\n") : PSTR("\n"), false);
    oled_write_P((layer == _NUM) ? PSTR("NUM\n") : PSTR("\n"), false);
    oled_write_P((layer == _FUNC) ? PSTR("FUN\n") : PSTR("\n"), false);
    oled_write_P((layer == _ADJUST) ? PSTR("ADJ\n") : PSTR("\n"), false);

    oled_write_P((is_caps_word_on()) ? PSTR("CAP\n") : PSTR("\n"), false);

    return false;
}

void oled_render_mods(void) {
    // See how to customize the bitmaps here: https://github.com/joric/qle
    // static const char PROGMEM font_option_img[7] = {0x04, 0x04, 0x08, 0x10, 0x24, 0x24, 0};
    // static const char PROGMEM font_cmd_img[8]    = {0x77, 0x55, 0x7F, 0x14, 0x7F, 0x55, 0x77, 0x00};
    // static const char PROGMEM font_shift_img[7]  = {0x00, 0x08, 0x34, 0x02, 0x34, 0x08, 0};
    // Host Keyboard LED Status
    oled_write_P(PSTR("MODS\n"), false);
    oled_write_P((get_oneshot_mods() & MOD_MASK_SHIFT) ? PSTR("S") : PSTR("-"), false);
    oled_write_P((get_oneshot_mods() & MOD_MASK_CTRL) ? PSTR("C") : PSTR("-"), false);
    oled_write_P((get_oneshot_mods() & MOD_MASK_ALT) ? PSTR("A") : PSTR("-"), false);
    oled_write_P((get_oneshot_mods() & MOD_MASK_GUI) ? PSTR("G\n") : PSTR("-\n"), false);
    oled_write_P(PSTR("----\n"), false);
    oled_write_P((get_mods() & MOD_MASK_SHIFT) ? PSTR("+SFT\n") : PSTR("\n"), false);
    oled_write_P((get_mods() & MOD_MASK_CTRL) ? PSTR("^CTL\n") : PSTR("\n"), false);
    oled_write_P((get_mods() & MOD_MASK_ALT) ? PSTR("~ALT\n") : PSTR("\n"), false);
    oled_write_P((get_mods() & MOD_MASK_GUI) ? PSTR("*GUI\n") : PSTR("\n"), false);

    // led_t led_state = host_keyboard_led_state();
    // oled_write_P(led_state.caps_lock ? PSTR("CAP") : PSTR("\n"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer();
    } else {
        oled_render_mods();
    }
    return false;
}
#endif // oled_enable

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

#ifdef ACHORDION_ENABLE
bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    // Exceptionally consider the following chords as holds, even though they
    // are on the same hand in Dvorak.
    switch (tap_hold_keycode) {
        case OSL(_SYM):
        case OSL(_NUM):
        case OSMS:
        case SPC:
        case ENT:
            return true;
            // LEFT
        case MOD_Z: // S + H and S + G.
            switch (other_keycode) {
                case MOD_C:
                case MOD_D:
                case MOD_V:
                case MOD_R:
                case MOD_S:
                case MOD_T:
                    return true;
            }
            break;
        case MOD_S: // A + U.
            switch (other_keycode) {
                case MOD_D:
                case MOD_V:
                case MOD_R:
                case MOD_A:
                case MOD_T:
                    return true;
            }
            break;
    }

    // Also allow same-hand holds when the other key is in the rows below the
    // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
    if (other_record->event.key.row % (MATRIX_ROWS / 2) >= 4) {
        return true;
    }

    // Otherwise, follow the opposite hands rule.
    return achordion_opposite_hands(tap_hold_record, other_record);
}
#endif
