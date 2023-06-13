#include <stdio.h>
#include "oled.h"
#include "custom_keycodes.h"
#include "custom_layers.h"
#include "features/casemodes.h"

// Should perhaps check if these are already defined
#define BLINK_TIMEOUT 10000
#define BLINK_INTERVAL 500

// ... same for this one!
#define KEYLOG_LEN 6

#define MOD_ICON_WIDTH 4
#define MOD_ICON_HEIGHT 3

static char     keylog_str[KEYLOG_LEN]  = { ' ', ' ', ' ', ' ', ' ', 0};
static uint16_t log_timer               = 0;
static bool     blink_timeout           = false;
static char     combo_str[6]            = { ' ', ' ', ' ', ' ', ' ', 0};
static const char code_to_name[60]      = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};

void render_empty_line(void) {
    oled_write_ln_P(PSTR(""), false);
}

void render_case_mode_status(uint16_t delimiter, bool caps) {
    bool brief = true;
#ifdef OLED_DISPLAY_128X64
    brief = false;
    oled_write_P(PSTR(" XCase: "), false);
#else
    oled_write_ln_P(PSTR("XCase"), false);
#endif
    if (delimiter == KC_UNDS) {
        if (caps) {
            oled_write_ln_P(brief ? PSTR("SNAKE") : PSTR("SNAKE_SCREM"), false);
        } else {
            oled_write_ln_P(brief ? PSTR("snake") : PSTR("snake_case"), false);
        }
    } else if (delimiter == OSM(MOD_LSFT)) {
        oled_write_ln_P(brief ? PSTR("caMel") : PSTR("camelCase"), false);
    } else if (caps) {
        oled_write_ln_P(brief ? PSTR("UPPER") : PSTR("UPPERCASE"), false);
    } else {
        oled_write_ln_P(brief ? PSTR("lower") : PSTR("lowercase"), false);
    }
}

void render_keylogger_status(void) {
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" Hist:  "), false);
#else
    oled_write_ln_P(PSTR("Hist."), false);
#endif
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    // TODO enable oneline support
    if (timer_elapsed(log_timer) > BLINK_TIMEOUT) {
        blink_timeout = true;
    }

    bool blink = (timer_read() % 1000) < BLINK_INTERVAL || blink_timeout;

    oled_write_P(PSTR("$"), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
            oled_write_P(blink ? PSTR("_\n") : PSTR("\n"), false);
            return;
        case _LOWER:
            oled_write_P(PSTR("LOW"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAI"), false);
            break;
        case _SYSTEM:
            oled_write_P(PSTR("SYS"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJ"), false);
            break;
        default:
            oled_write_P(PSTR("-?-"), false);
            break;
    }
    oled_write_P(blink ? PSTR("_") : PSTR(" "), false);
}

void render_mod_icon(uint8_t loc, bool enabled, const char *icon, bool invert) {
  uint8_t col = 1 + loc * (MOD_ICON_WIDTH + 1);
  for (uint8_t i=0; i < MOD_ICON_HEIGHT; ++i) {
    oled_set_cursor(col, i);
    for (uint8_t j=0; j < MOD_ICON_WIDTH; ++j) {
        oled_write_char(enabled ? icon[i*MOD_ICON_WIDTH+j] : ' ', invert);
    }
  }
}

void render_mod_shift(uint8_t order, uint8_t mods) {
    static const char shift_icon[] = {
        0x88, 0x89, 0x8A, 0x8B,
        0xA8, 0xA9, 0xAA, 0xAB,
        0xC8, 0xC9, 0xCA, 0xCB
    };
    render_mod_icon(order, mods & MOD_MASK_SHIFT, shift_icon, false);
}

void render_mod_gui(uint8_t order, uint8_t mods) {
    static const char gui_icon[] = {
        0x80, 0x81, 0x82, 0x83,
        0xA0, 0xA1, 0xA2, 0xA3,
        0xC0, 0xC1, 0xC2, 0xC3
    };
    render_mod_icon(order, mods & MOD_MASK_GUI, gui_icon, false);
}

void render_mod_alt(uint8_t order, uint8_t mods) {
    static const char alt_icon[] = {
        0x84, 0x85, 0x86, 0x87,
        0xA4, 0xA5, 0xA6, 0xA7,
        0xC4, 0xC5, 0xC6, 0xC7
    };
    render_mod_icon(order, mods & MOD_MASK_ALT, alt_icon, false);
}

void render_mod_ctrl(uint8_t order, uint8_t mods) {
    static const char ctrl_icon[] = {
        0x8C, 0x8D, ' ', ' ',
        0xAC, 0xAD, ' ', ' ',
        0xCC, 0xCD, ' ', ' '
    };
    render_mod_icon(order, mods & MOD_MASK_CTRL, ctrl_icon, false);
}

void render_mod_status_short(void) {
    uint8_t modifiers = get_mods();
    oled_write_P(PSTR(" Mods:  "), false);
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_ln_P(PSTR(""), false);
}

void render_modifier_status(void) {
    uint8_t modifiers = get_mods();
    uint8_t order = 0; // dynamic to making swap order less of a hassle
    render_mod_shift(order++, modifiers);
    render_mod_gui(order++, modifiers);
    render_mod_alt(order++, modifiers);
    render_mod_ctrl(order++, modifiers);
}

void render_combo_status(void) {
#ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(" Combo: "), false);
#else
    oled_write_ln_P(PSTR("Combo"), false);
#endif
    oled_write_ln(combo_str, false);
}

void append_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
    blink_timeout = false;
}

void update_combo_status(uint16_t combo_term, char id) {
    sprintf(combo_str, "%5u", combo_term);
    combo_str[0] = id;
}

