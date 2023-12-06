#include "action_util.h"
#include "caps_word.h"
#include "quantum.h"
#include QMK_KEYBOARD_H

#include "tapdance.h"
#include "layers.h"
#include "keycodes.h"

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t tap_state = {.is_press_action = true, .state = TD_NONE};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

void td_dot(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING("../");
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING("./");
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("../../");
            break;
        default:
            break;
    }
}

// backslash

void td_bsls(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_BSLS);
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING("\\/");
            break;
        default:
            break;
    }
}

// colon vim quick key

void td_colon(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_COLN);
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("::");
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING(":=");
            break;
        case TD_TRIPLE_TAP:
            SEND_STRING(":q!" SS_TAP(X_ENT));
            break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        // case TD_DOUBLE_SINGLE_TAP:
        //     tap_code16(KC_COLN);
        //     tap_code16(KC_COLN);
        //     break;
        default:
            break;
    }
}

void td_exlm(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_EXLM);
            break;
            // for quick quick tapping
        case TD_SINGLE_HOLD:
            SEND_STRING("!=");
            break;
        case TD_DOUBLE_TAP:
            SEND_STRING("!%");
            break;
        default:
            break;
    }
}

void td_tilda(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_TILD);
            break;
        case TD_SINGLE_HOLD:
            SEND_STRING("~/");
            break;
            // for quick quick tapping
        default:
            break;
    }
}

void td_quot(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_QUOT);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(KC_ENT);
            break;
        default:
            tap_code16(KC_QUOT);
            break;
    }
}

void td_tab(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            // tap_code16(KC_TAB);
            set_oneshot_layer(_SYM, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        case TD_SINGLE_HOLD:
            leader_start();
            break;
        default:
            break;
    }
}

// clang-format off

// Tap dance declarations

tap_dance_action_t tap_dance_actions[] = {
    [SDB_UPDIR] = ACTION_TAP_DANCE_FN(td_dot),
    // [SDB_DOT] = ACTION_TAP_DANCE_FN(td_dot),
    // [SDB_COM] = ACTION_TAP_DANCE_FN(td_comma),
    [SDB_BSLS] = ACTION_TAP_DANCE_FN(td_bsls),
    [SDB_COLN] = ACTION_TAP_DANCE_FN(td_colon),
    [TP_EXLM] = ACTION_TAP_DANCE_FN(td_exlm),
    [TP_TILDA] = ACTION_TAP_DANCE_FN(td_tilda),
    [TP_TAB] = ACTION_TAP_DANCE_FN(td_tab),
    [TP_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_ENT),
    [TP_DELNAV] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_DEL, _NAV),
};

// clang-format on
