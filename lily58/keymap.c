#include QMK_KEYBOARD_H

#include "keymap.h"
#include "g/keymap_combo.h"

bool sw_win_active = false;
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

static uint16_t non_combo_input_timer = 0;

// TODO move enter and change thumb shift to one shot and perhaps toggle Word cap on double tap
// TODO update the combo term since io and er seems to misfire
// TODO can I solve the issues with CMD (SFT) + N by having OSM CMD and SFT on SPC and ENT
// TODO would it be nice to move enter to a layer or combo and use ENT as OS SFT instead of having to press it
//      perhaps a follow up to the above could be to toggle CAPS Word if pressing the ENT OSM twice
// TODO when adding a number layer, make dubble tapping it toggle NUMWORD
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT( \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_GRV,  \
        CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,  KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, \
                                   XXXXXXX, REPEAT,  LOWER,   KC_SPC,   ENT_SFT, RAISE,   REPEAT,  XXXXXXX \
        ),

    // Mnemonic for Alfred and iTerm is T for Terminal and G for Goto. N is for Newline
    [_LOWER] = LAYOUT( \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, KC_ESC,  XXXXXXX, SW_WIN,  XXXXXXX, ITERM,                      XXXXXXX, CAPS,    SNAKE,   CAMEL,   KC_DEL,  XXXXXXX, \
        XXXXXXX, OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, ALFRED,                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSPC, XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,  _______, KC_ENT,  XXXXXXX, XXXXXXX, XXXXXXX, KC_ENT,  XXXXXXX, \
                                   _______, _______, __LOW__, _______,  _______, __RAS__, _______, _______ \
        ),

    [_RAISE] = LAYOUT( \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, XXXXXXX, \
        XXXXXXX, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    QUOTES,  \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                                   _______, _______, __LOW__, _______,  _______, __RAS__, _______, _______ \
        ),

    [_ADJUST] = LAYOUT( \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, G(KC_1), G(KC_2), G(KC_3), G(KC_4), G(KC_5),                    G(KC_6), G(KC_7), G(KC_8), G(KC_9), G(KC_0), XXXXXXX, \
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    KC_MINS, KC_EQL,  KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX, \
        XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, \
                                   _______, _______, __LOW__, _______,  _______, __RAS__, _______, _______ \
        )
};

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    char id;
    uint16_t term;
    switch (index) {
        case WE_LCBR:
        case ER_RCBR:
        case WR_CBR_PAIR:

        case SD_LPRN:
        case DF_RPRN:
        case SF_PRN_PAIR:

        case XC_COPY:
        case CV_PASTE:
        case XV_CUT:
        case ZX_UNDO:

        case LSCLN_BSPC:

        case XCV_PASTE_SFT:
        case WER_CBR_PAIR_IN:
        case SDF_PRN_PAIR_IN:
            id = timer_elapsed(non_combo_input_timer) > 300 ? '1' : '2';
            term = timer_elapsed(non_combo_input_timer) > 300 ? 30 : 5;
            break;

        case UIO_SNAKE_SCREAM:
        case UI_CAPS_WORD:
        case IO_SNAKE_WORD:
            id = '3';
            term = 25;
            break;

        case KL_TAB:
        case JK_ESC:
        default:
            id = '4';
            term = 35;
            break;
    }
    update_combo_status(term, id);
    return term;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LOWER:
        case RAISE:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LOWER:
        case RAISE:
        case KC_LSFT:
        case OS_LSFT:
        case OS_LCTL:
        case OS_LALT:
        case OS_LGUI:
            return true;
        default:
            return false;
    }
}

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case CAPS:
        case SNK_SCM:
        case SNAKE:
            // If mod chording disable the mods
            if (record->event.pressed && (get_mods() != 0)) {
                return true;
            }
            break;
        default:
            if (record->event.pressed) {
                return true;
            }
            break;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    
    update_oneshot(&os_shft_state, KC_LSFT, OS_LSFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_LCTL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_LALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LGUI, OS_LGUI, keycode, record);

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    non_combo_input_timer = timer_read();

    if (record->event.pressed) {
        append_keylog(keycode);
    }

    if (record->event.pressed && keycode != REPEAT) {
        register_key_to_repeat(keycode);
    }

    switch (keycode) {
        case QUOTES:
            if (record->event.pressed) {
                SEND_STRING("\"\""SS_TAP(X_LEFT));
            }
            return false;
        case REPEAT:
            update_repeat_key(record);
            return false;
        case SE_AO:
            if (record->event.pressed) {
                tap_code16(A(KC_A));
            }
            return false;
        case SE_AE:
        case SE_OE:
            if (record->event.pressed) {
                uint8_t mod_state = get_mods();
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                } 
                tap_code16(A(KC_U));
                set_mods(mod_state);
                tap_code16(keycode == SE_AE ? KC_A : KC_O);
            }
            return false;
        case CAPS:
            if (record->event.pressed) {
                toggle_caps_word();
            }
            return false;
        case SNAKE:
        case CAMEL:
            if (record->event.pressed) {
                if (get_xcase_delimiter() != KC_NO) {
                    disable_xcase();
                } else {
                    enable_xcase_with(keycode == SNAKE ? KC_UNDS : OSM(MOD_LSFT));
                }
            }
            return false;
        case SNK_SCM:
            if (record->event.pressed) {
                if (get_xcase_delimiter() != KC_NO) {
                    disable_xcase();
                    disable_caps_word();
                } else {
                    enable_caps_word();
                    enable_xcase_with(KC_UNDS);
                }
            }
            return false;
    }

    return true;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_empty_line();
        render_default_layer_state();
        render_empty_line();
        render_case_mode_status(get_xcase_delimiter(), caps_word_enabled());
        render_empty_line();
        render_keylogger_status();
        render_empty_line();
        render_combo_status();
    } else {
        render_empty_line();
        render_modifier_status();
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
}

void suspend_power_down_user(void) {
    oled_off();
}

