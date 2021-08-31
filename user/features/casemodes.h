#pragma once

#include QMK_KEYBOARD_H

// Check whether caps word is on
bool caps_word_enabled(void);
// Enable caps word
void enable_caps_word(void);
// Disable caps word
void disable_caps_word(void);
// Toggle caps word
void toggle_caps_word(void);

// enum for the xcase states
enum xcase_state {
    XCASE_OFF = 0,  // xcase is off
    XCASE_ON,       // xcase is actively on
    XCASE_WAIT,     // xcase is waiting for the delimiter input
};

// Get current delimiter, defaults to KC_NO when off
uint16_t get_xcase_delimiter(void);
// Get xcase state
enum xcase_state get_xcase_state(void);
// Enable xcase and pickup the next keystroke as the delimiter
void enable_xcase(void);
// Enable xcase with the specified delimiter
void enable_xcase_with(uint16_t delimiter);
// Disable xcase
void disable_xcase(void);

// Function to be put in process user
bool process_case_modes(uint16_t keycode, const keyrecord_t *record);
