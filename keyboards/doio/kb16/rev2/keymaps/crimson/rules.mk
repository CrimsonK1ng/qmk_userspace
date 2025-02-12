SRC += ./lib/layer_status/layer_status.c
SRC += ./lib/logo.c

# Configure for 128K flash
MCU_LDSCRIPT = STM32F103xB
VIA_ENABLE = yes
MOUSEKEY_ENABLE = yes
ENCODER_MAP_ENABLE = yes
