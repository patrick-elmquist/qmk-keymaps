#include "pket.h"
#include "print.h"
#include "g/keymap_combo.h"

bool sw_win_active = false;
bool sw_app_active = false;
oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

static uint16_t non_combo_input_timer = 0;
uint8_t mod_state;

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// Oneshot functions
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LOWER:
        case LOW_SPC:
        case RAISE:
        case SYSTEM:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LOWER:
        case LOW_SPC:
        case RAISE:
        case SYSTEM:
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

// Xcase functions
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

// Combo functions
bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    switch(index) {
        case HCOM_DQUOT:
        case VCB_LN:
        case VCB_NH:
        // case THUMB_M:
        // case THUMB_N:
        // case THUMB_H:
            return false;
    }
    return true;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    char id;
    uint16_t term;
    switch (index) {
        case WP_CBR_PAIR:
        case WF_LCBR:
        case FP_RCBR:
            id = timer_elapsed(non_combo_input_timer) > 350 ? '1' : '2';
            term = timer_elapsed(non_combo_input_timer) > 350 ? 25 : 5;
            term = 35;
            break;

        case RAI_ENT:
        case RS_LPRN:
        case ST_RPRN:
        case RT_PRN_PAIR:

        case XC_COPY:
        case CD_PASTE:
        case LU_QUES_DOT:

        case LUY_SNAKE_SCREAM:
            id = '5';
            term = 25;
            break;

        case VCB_LN:
        case VCB_NH:
        case XD_CUT:
        case ZX_UNDO:
        case UY_QUOT:
        case EI_TAB:
        case NI_EQL:
            id = '3';
            term = 30;
            break;

        // case THUMB_N:
        case NE_ESC:
            // id = timer_elapsed(non_combo_input_timer) > 150 ? '4' : '7';
            // term = timer_elapsed(non_combo_input_timer) > 150 ? 35 : 5;
            id = '4';
            term = 45;
            // #ifdef CONSOLE_ENABLE
            //     uprintf("COMBO: index: %u, id: %c, term: %u timer: %u\n",
            //             index,
            //             id,
            //             term,
            //             timer_elapsed(non_combo_input_timer)
            //             );
            // #endif
            break;

        // case THUMB_M:
        // case THUMB_H:
        case HCOM_DQUOT:
        case SWE_AO:
        case SWE_AE:
        case SWE_OE:
            id = '8';
            term = 40;
            break;

        case LTGT_ARROW:
        case XCD_PASTE_SFT:
        case WFP_CBR_PAIR_IN:
        case RST_PRN_PAIR_IN:

        default:
            id = '6';
            term = 35;
            break;
    }
    update_combo_status(term, id);
    return term;
}

// Tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_R:
        case HOME_I:
        case MOD_X:
        case MOD_DOT:
            return TAPPING_TERM + RING_EXTRA;
        case HOME_A:
        case HOME_O:
        case MOD_A:
        case MOD_O:
        case MOD_Z:
        case MOD_SLH:
            return TAPPING_TERM + PINKY_EXTRA;
        case HOME_S:
        case HOME_E:
        case MOD_C:
        case MOD_COM:
            return TAPPING_TERM + LONG_EXTRA;
        case HOME_T:
        case HOME_N:
            return TAPPING_TERM + INDEX_EXTRA;
        case LOW_SPC:
            return TAPPING_TERM + THUMB_EXTRA;
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOW_SPC:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
        case MOD_A:
        case MOD_Z:
        case MOD_X:
        case MOD_C:
        case MOD_COM:
        case MOD_DOT:
        case MOD_SLH:
        case MOD_O:
        case RAI_ENT:
        case LOW_SPC:
            return true;
        default:
            return false;
    }
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
        case MOD_A:
        case MOD_Z:
        case MOD_X:
        case MOD_C:
        case MOD_COM:
        case MOD_DOT:
        case MOD_SLH:
        case MOD_O:
            // Do not force the mod-tap key press to be handled as a modifier
            // if any other key was pressed while the mod-tap key is held down.
            return true;
        default:
            // Force the mod-tap key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return false;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case MOD_A:
            // Immediately select the hold action when another key is pressed.
            // return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    uprintf("key:0x%04X, row:%u, col:%u, layer:%u, down:%b, mods:0x%02X, osm:0x%02X, count:%u\n",
        keycode,
        record->event.key.row,
        record->event.key.col,
        get_highest_layer(layer_state),
        record->event.pressed,
        get_mods(),
        get_oneshot_mods(),
        record->tap.count
        );
    #endif

    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    update_swapper(&sw_app_active, KC_LGUI, KC_GRV, SW_APP, keycode, record);

    update_oneshot(&os_shft_state, KC_LSFT, OS_LSFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_LCTL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_LALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LGUI, OS_LGUI, keycode, record);

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    non_combo_input_timer = timer_read();

    static uint16_t single_quote_timer;
    static uint16_t double_quote_timer;

    if (record->event.pressed) {
        append_keylog(keycode);
    }

    mod_state = get_mods();

    switch (keycode) {
        case NE_ESC:
            if (!record->event.pressed) {
                non_combo_input_timer += 151;
            }
            return true;
        case KC_BSPC: {
            // Initialize a boolean variable that keeps track
            // of the delete key status: registered or not?
            //
            static bool delkey_registered;
            if (record->event.pressed) {
                // Detect the activation of either shift keys
                if (mod_state & MOD_MASK_SHIFT) {
                    // First temporarily canceling both shifts so that
                    // shift isn't applied to the KC_DEL keycode
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    // Update the boolean variable to reflect the status of KC_DEL
                    delkey_registered = true;
                    // Reapplying modifier state so that the held shift key(s)
                    // still work even after having tapped the Backspace/Delete key.
                    set_mods(mod_state);
                    return false;
                }
            } else { // on release of KC_BSPC
                     // In case KC_DEL is still being sent even after the release of KC_BSPC
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    return false;
                }
            }
            // Let QMK process the KC_BSPC keycode as usual outside of shift
            return true;
        }
        // TODO could I merge these like the swe chars?
        case S_QUOTE:
            if (record->event.pressed) {
                single_quote_timer = timer_read();
                tap_code16(KC_QUOT);
            } else if (timer_elapsed(single_quote_timer) > TAPPING_TERM) {
                tap_code16(KC_QUOT);
                tap_code16(KC_LEFT);
            }
            return false;
        case D_QUOTE:
            if (record->event.pressed) {
                double_quote_timer = timer_read();
                tap_code16(KC_DQUO);
            } else if (timer_elapsed(double_quote_timer) > TAPPING_TERM) {
                tap_code16(KC_DQUO);
                tap_code16(KC_LEFT);
            }
            return false;
        // TODO could I merge this three like swe chars?
        case CURLYS:
            if (record->event.pressed) {
                SEND_STRING("{}"SS_TAP(X_LEFT));
            }
            return false;
        case BRCKETS:
            if (record->event.pressed) {
                SEND_STRING("[]"SS_TAP(X_LEFT));
            }
            return false;
        case PARENS:
            if (record->event.pressed) {
                SEND_STRING("()"SS_TAP(X_LEFT));
            }
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
        // TODO these two are never used afaik
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

#ifdef OLED_ENABLE

void suspend_power_down_user(void) {
    oled_off();
}

#endif
