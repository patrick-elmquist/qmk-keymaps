VPATH += keyboards/gboards/

# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
# AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight. 
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
ENCODER_ENABLE = no         # Enables the use of one or more encoders
AUTO_SHIFT_ENABLE = no
WPM_ENABLE = no
TAP_DANCE_ENABLE = no
DYNAMIC_MACRO_ENABLE = no
RGB_MATRIX_ENABLE = no     

RAW_ENABLE = no
SPACE_CADET_ENABLE = no
POINTING_DEVICE_ENABLE = no
GRAVE_ESC_ENABLE = no
UNICODE_ENABLE = no
CAPS_WORD_ENABLE = no

CONSOLE_ENABLE = yes        # Console for debug
COMBO_ENABLE = yes
EXTRAKEY_ENABLE = yes       # Audio control and System control
OLED_ENABLE = yes           # OLED display
LTO_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

# To use gboards combos
INTROSPECTION_KEYMAP_C = combos.c

SRC += ./pket.c
SRC += ./features/casemodes.c
SRC += ./features/swapper.c
SRC += ./oled.c

EXTRAFLAGS += -flto

