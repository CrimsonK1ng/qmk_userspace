#pragma once
#include "quantum.h"

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool       is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t dance_state(tap_dance_state_t *state);

// Tap dance codes

// clang-format off
#ifdef TAP_DANCE_ENABLE
enum { TD_CODE_START, 
  SDB_UPDIR, 
  SDB_BSLS, 
  SDB_COLN, 
  TP_EXLM,
  TP_TILDA,
  TP_QUOT,
  TP_DELNAV,
  TP_TAB,
  TD_CODE_END };
// clang-format on

// Tap dance keycodes

#    define TD_UPDIR TD(SDB_UPDIR)
#    define TD_BSLS TD(SDB_BSLS)
// #define TD_COM TD(SDB_COM)
#    define TD_COLN TD(SDB_COLN)
#    define TD_EXLM TD(TP_EXLM)
#    define TD_TILDA TD(TP_TILDA)
#    define TD_QUOT TD(TP_QUOT)
#    define TD_TAB TD(TP_TAB)
#    define TD_DELNAV TD(TP_DELNAV)

#endif
