// Copyright 2022 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TAPPING_TERM 250 // with permissive hold
#define CHORDAL_HOLD true
#define TAPPING_TERM_PER_KEY
// #define PERMISSIVE_HOLD_PER_KEY
#define PERMISSIVE_HOLD // trying achordion

#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define TAPPING_TOGGLE 3
#define DEBOUNCE 15

// #define QUICK_TAP_TERM 125

#define CAPS_WORD_INVERT_ON_SHIFT

#define LEADER_NO_TIMEOUT
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250

#define CAPS_WORD_IDLE_TIMEOUT 2000
#define CAPS_WORD_INVERT_ON_SHIFT

// ################# COMBO_TERM is set to how fast you have to hit both at the same time
#ifdef COMBO_ENABLE
#    define COMBO_TERM 30
#    define COMBO_TERM_PER_COMBO
#    define COMBO_MUST_TAP_PER_COMBO
#    define COMBO_STRICT_TIMER // make that time to activate super tight
#    define COMBO_MUST_HOLD_PER_COMBO
#endif

// #ifdef RGBLIGHT_ENABLE
// #define RGBLIGHT_EFFECT_BREATHING
// #define RGBLIGHT_EFFECT_TWINKLE
// #endif
// Some boards have issues detecting handedness using the vbus voltage.
// Such as Elite-C v3, but not v3.1 on. Also apparently some ProMicro boards.
// For those boands, use usb detection instead.
// #define SPLIT_USB_DETECT
