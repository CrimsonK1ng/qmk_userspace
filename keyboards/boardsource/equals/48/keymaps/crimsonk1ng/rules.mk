
CAPS_WORD_ENABLE = yes # CAPS WORD BB
COMBO_ENABLE = yes
OS_DETECTION_ENABLE = yes
# combos
VPATH += keyboards/gboards

# expensive
#LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes # requires a ton of space :(

# # SRC += lib/layer_lock.c
# SRC += lib/achordion.c
#     Forces the keyboard to wait for a USB connection to be established before it starts up
LIB_SRC += lib/tapdance.c
