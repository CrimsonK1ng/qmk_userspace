#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 200 // with permissive hold
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
// #define TAPPING_TOGGLE 2
// #define ACHORDION_ENABLE

#define QUICK_TAP_TERM 150

// #define USB_SUSPEND_WAKEUP_DELAY 200
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_INVERT_ON_SHIFT


#define ONESHOT_TAP_TOGGLE 6 /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 2000 /* Time (in ms) before the one shot key is released */

// #################
// LEADER KEY
// #################
// per key leader
// don't timeout after pressing leader key
#define LEADER_NO_TIMEOUT
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
// #################

// ################# COMBO_TERM is set to how fast you have to hit both at the same time
#ifdef COMBO_ENABLE
#    define COMBO_TERM 30
// #    define COMBO_ONLY_FROM_LAYER 0
#    define COMBO_TERM_PER_COMBO
#    define COMBO_MUST_TAP_PER_COMBO
#    define COMBO_STRICT_TIMER // make that time to activate super tight
#    define COMBO_MUST_HOLD_PER_COMBO
#endif

// ################# Hit both shifts for the caps to be turned on while in word mode
// #define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD // I think this is less effective than using a combo
#define CAPS_WORD_IDLE_TIMEOUT 1500
// #################
