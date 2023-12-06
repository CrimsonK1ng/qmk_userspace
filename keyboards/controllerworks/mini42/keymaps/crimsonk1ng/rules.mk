# LTO_ENABLE=yes
# NKRO_ENABLE=yes
# SPLIT_KEYBOARD = yes
CAPS_WORD_ENABLE = yes # CAPS WORD BB
COMBO_ENABLE = yes
SWAP_HANDS_ENABLE = yes
# RGB_MATRIX_ENABLE = yes
OS_DETECTION_ENABLE = yes
# combos
VPATH += keyboards/gboards

# doesn't wait for response from pc
NO_USB_STARTUP_CHECK = yes
REPEAT_KEY_ENABLE = yes
# expensive
#LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes # requires a ton of space :(

# SRC += lib/layer_lock.c
# SRC += lib/achordion.c
#     Forces the keyboard to wait for a USB connection to be established before it starts up
LIB_SRC += lib/tapdance.c
