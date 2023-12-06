CAPS_WORD_ENABLE = yes # CAPS WORD BB
COMBO_ENABLE = yes
OS_DETECTION_ENABLE = yes
# combos
VPATH += keyboards/gboards
# expensive
LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes # requires a ton of space :(
LIB_SRC += lib/tapdance.c
