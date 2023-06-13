#pragma once

#include QMK_KEYBOARD_H
#include "keycodes.h"

void render_empty_line(void);

void render_case_mode_status(uint16_t delimiter, bool caps);

void render_keylogger_status(void);

void render_default_layer_state(void);

void render_mod_icon(uint8_t loc, bool enabled, const char *icon, bool invert);

void render_mod_shift(uint8_t order, uint8_t mods);

void render_mod_gui(uint8_t order, uint8_t mods);

void render_mod_alt(uint8_t order, uint8_t mods);

void render_mod_ctrl(uint8_t order, uint8_t mods);

void render_mod_status_short(void);

void render_modifier_status(void);

void render_combo_status(void);

// Append a keycode to the key log
void append_keylog(uint16_t keycode);

// Update the combo status
void update_combo_status(uint16_t combo_term, char id);
