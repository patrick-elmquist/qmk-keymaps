#include "pket.h"
#include "print.h"
#include "features/swapper.h"

uint8_t mod_state;

bool sw_win_active = false;
bool sw_app_active = false;

// const uint16_t PROGMEM at_combo[] = {KC_A, KC_T, COMBO_END};

// combo_t key_combos[] = {
//   COMBO(at_combo, KC_ESC),
// };

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYSTEM, _NAV, _ADJUST);
}

// // Combo functions
// bool get_combo_must_tap(uint16_t index, combo_t *combo) {
//     switch(index) {
//         case HCOM_DQUOT:
//         case VCB_LN:
//         case VCB_NH:
//             return false;
//     }
//     return true;
// }

// bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
//     bool is_canary = layer_state_is(_CANARY);

//     switch (combo_index) {
//         case CRY_COPY:
//         case CRY_PASTE:
//         case CRY_CUT:
//         case CRY_UNDO:
//         case CRY_SWE_AO:
//         case CRY_SWE_AE:
//         case CRY_SWE_OE:
//             return is_canary;
//     }

//     return is_canary;
// }

// uint16_t get_combo_term(uint16_t index, combo_t *combo) {
//     uint16_t term;
//     switch (index) {
//         case WP_CBR_PAIR:
//         case WF_LCBR:
//         case FP_RCBR:
//             term = 45;
//             break;

//         case RAI_ENT:
//         case RS_LPRN:
//         case ST_RPRN:
//         case RT_PRN_PAIR:

//         case XC_COPY:
//         case CD_PASTE:
//         case CRY_COPY:
//         case CRY_PASTE:
//         case LU_QUES_DOT:

//         case LUY_SNAKE_SCREAM:
//             term = 30;
//             break;

//         case VCB_LN:
//         case VCB_NH:
//         case XD_CUT:
//         case ZX_UNDO:
//         case CRY_CUT:
//         case CRY_UNDO:
//         case UY_QUOT:
//         case EI_TAB:
//         case NI_EQL:
//             term = 40;
//             break;

//         case NE_ESC:
//             term = 50;
//             break;

//         case HCOM_DQUOT:
//         case SWE_AO:
//         case SWE_AE:
//         case SWE_OE:
//         case CRY_SWE_AO:
//         case CRY_SWE_AE:
//         case CRY_SWE_OE:
//             term = 45;
//             break;

//         case LTGT_ARROW:
//         case XCD_PASTE_SFT:
//         case WFP_CBR_PAIR_IN:
//         case RST_PRN_PAIR_IN:
//         case NEI_ENT:

//         default:
//             term = 45;
//             break;
//     }
//     return term;
// }

// Xcase functions
bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        // Keycodes to ignore (don't disable caps word)
        case KC_MINS:
        case KC_UNDS:
        case KC_BSPC:
        case CAPS:
        case SNK_SCM:
        case SNAKE:
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
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

// Tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_R:
        case HOME_I:
            return TAPPING_TERM + RING_EXTRA;
        case CNRY_C:
        case CNRY_A:
        case HOME_A:
        case HOME_O:
            return TAPPING_TERM + PINKY_EXTRA;
        case HOME_S:
        case HOME_E:
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
        case RAI_ENT:
        case RAI_BSP:
        case NAV_BSP:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_R:
        case HOME_S:
        case HOME_T:
        case HOME_N:
        case HOME_E:
        case HOME_I:
        case HOME_O:
        case CNRY_C:
        case CNRY_A:
        case RAI_ENT:
        case LOW_SPC:
            return 0;
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            switch (keycode) {
                case HOME_A:
                case HOME_R:
                case HOME_S:
                case HOME_T:
                case HOME_N:
                case HOME_E:
                case HOME_I:
                case HOME_O:
                case CNRY_C:
                case CNRY_A:
                    // Do not force the mod-tap key press to be handled as a modifier
                    // if any other key was pressed while the mod-tap key is held down.
                    return false;
                default:
                    // Force the mod-tap key press to be handled as a modifier if any
                    // other key was pressed while the mod-tap key is held down.
                    return true;
            }
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    uprintf("key:0x%04X, row:%u, col:%u, layer:%u, down:%s, mods:0x%02X, osm:0x%02X, count:%u\n",
        keycode,
        record->event.key.row,
        record->event.key.col,
        get_highest_layer(layer_state),
        record->event.pressed ? "true" : "false",
        get_mods(),
        get_oneshot_mods(),
        record->tap.count
    );
    #endif

    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
    update_swapper(&sw_app_active, KC_LGUI, KC_GRV, SW_APP, keycode, record);

    if (!process_case_modes(keycode, record)) {
        return false;
    }

    static uint16_t single_quote_timer;
    static uint16_t double_quote_timer;

    if (record->event.pressed) {
        append_keylog(keycode);
    }

    mod_state = get_mods();

    switch (keycode) {
        case HOME_T:
            if (record->event.pressed && record->tap.count > 0) {
                if (get_mods() & MOD_BIT(KC_LGUI)) {
                    unregister_mods(MOD_BIT(KC_LGUI));
                    tap_code(KC_S);
                    tap_code(KC_T);
                    add_mods(MOD_BIT(KC_LGUI));
                    return false;
                }
                if (layer_state_is(_CANARY)) {
                    // TODO evalutate if a version of this is needed for Canary
                    if (get_mods() & MOD_BIT(KC_LCTL)) {
                        unregister_mods(MOD_BIT(KC_LCTL));
                        tap_code(KC_A);
                        tap_code(KC_T);
                        add_mods(MOD_BIT(KC_LCTL));
                        return false;
                    }
                }
            }
        case HOME_R:
            if (record->event.pressed && record->tap.count > 0) {
                if (get_mods() & MOD_BIT(KC_LCTL)) {
                    unregister_mods(MOD_BIT(KC_LCTL));
                    tap_code(KC_A);
                    tap_code(KC_R);
                    add_mods(MOD_BIT(KC_LCTL));
                    return false;
                }
            }
            return true;

        case HOME_E:
            if (record->event.pressed && record->tap.count > 0) {
                if (get_mods() & MOD_BIT(KC_RSFT)) {
                    unregister_mods(MOD_BIT(KC_RSFT));
                    tap_code(KC_N);
                    tap_code(KC_E);
                    add_mods(MOD_BIT(KC_RSFT));
                    return false;
                }
            }
            return true;

        case HOME_N:
            if (record->event.pressed && record->tap.count > 0) {
                if (get_mods() & MOD_BIT(KC_RGUI)) {
                    unregister_mods(MOD_BIT(KC_RGUI));
                    tap_code(KC_E);
                    tap_code(KC_N);
                    add_mods(MOD_BIT(KC_RGUI));
                    return false;
                }
                if (layer_state_is(_CANARY)) {
                    // TODO evalutate if a version of this is needed for Canary
                    if (get_mods() & MOD_BIT(KC_RCTL)) {
                        unregister_mods(MOD_BIT(KC_RCTL));
                        tap_code(KC_O);
                        tap_code(KC_N);
                        add_mods(MOD_BIT(KC_RCTL));
                        return false;
                    }
                }
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
