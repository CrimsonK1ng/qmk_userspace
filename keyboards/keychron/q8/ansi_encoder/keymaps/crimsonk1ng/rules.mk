ENCODER_MAP_ENABLE = yes
CAPS_WORD_ENABLE = yes # CAPS WORD BB
COMBO_ENABLE = yes

OS_DETECTION_ENABLE = yes
VPATH += keyboards/gboards
TAP_DANCE_ENABLE = yes # requires a ton of space :(
LEADER_ENABLE = yes
LIB_SRC += lib/tapdance.c
