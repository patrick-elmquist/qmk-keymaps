#include "pket.h"
// #include "g/keymap_combo.h"
#include "features/swapper.h"

//uint8_t mod_state;

//bool sw_win_active = false;
//bool sw_app_active = false;

//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//    #ifdef CONSOLE_ENABLE
//    uprintf("key:0x%04X, row:%u, col:%u, layer:%u, down:%s, mods:0x%02X, osm:0x%02X, count:%u\n",
//        keycode,
//        record->event.key.row,
//        record->event.key.col,
//        get_highest_layer(layer_state),
//        record->event.pressed ? "true" : "false",
//        get_mods(),
//        get_oneshot_mods(),
//        record->tap.count
//    );
//    #endif

//    update_swapper(&sw_win_active, KC_LGUI, KC_TAB, SW_WIN, keycode, record);
//    update_swapper(&sw_app_active, KC_LGUI, KC_GRV, SW_APP, keycode, record);

//    if (!process_case_modes(keycode, record)) {
//        return false;
//    }

//    static uint16_t single_quote_timer;
//    static uint16_t double_quote_timer;

//    if (record->event.pressed) {
//        append_keylog(keycode);
//    }

//    mod_state = get_mods();

//    switch (keycode) {
//        case HOME_T:
//            if (record->event.pressed && record->tap.count > 0) {
//                if (get_mods() & MOD_BIT(KC_LGUI)) {
//                    unregister_mods(MOD_BIT(KC_LGUI));
//                    tap_code(KC_S);
//                    tap_code(KC_T);
//                    add_mods(MOD_BIT(KC_LGUI));
//                    return false;
//                }
//                if (layer_state_is(_CANARY)) {
//                    // TODO evalutate if a version of this is needed for Canary
//                    if (get_mods() & MOD_BIT(KC_LCTL)) {
//                        unregister_mods(MOD_BIT(KC_LCTL));
//                        tap_code(KC_A);
//                        tap_code(KC_T);
//                        add_mods(MOD_BIT(KC_LCTL));
//                        return false;
//                    }
//                }
//            }
//        case HOME_R:
//            if (record->event.pressed && record->tap.count > 0) {
//                if (get_mods() & MOD_BIT(KC_LCTL)) {
//                    unregister_mods(MOD_BIT(KC_LCTL));
//                    tap_code(KC_A);
//                    tap_code(KC_R);
//                    add_mods(MOD_BIT(KC_LCTL));
//                    return false;
//                }
//            }
//            return true;

//        case HOME_E:
//            if (record->event.pressed && record->tap.count > 0) {
//                if (get_mods() & MOD_BIT(KC_RSFT)) {
//                    unregister_mods(MOD_BIT(KC_RSFT));
//                    tap_code(KC_N);
//                    tap_code(KC_E);
//                    add_mods(MOD_BIT(KC_RSFT));
//                    return false;
//                }
//            }
//            return true;

//        case HOME_N:
//            if (record->event.pressed && record->tap.count > 0) {
//                if (get_mods() & MOD_BIT(KC_RGUI)) {
//                    unregister_mods(MOD_BIT(KC_RGUI));
//                    tap_code(KC_E);
//                    tap_code(KC_N);
//                    add_mods(MOD_BIT(KC_RGUI));
//                    return false;
//                }
//                if (layer_state_is(_CANARY)) {
//                    // TODO evalutate if a version of this is needed for Canary
//                    if (get_mods() & MOD_BIT(KC_RCTL)) {
//                        unregister_mods(MOD_BIT(KC_RCTL));
//                        tap_code(KC_O);
//                        tap_code(KC_N);
//                        add_mods(MOD_BIT(KC_RCTL));
//                        return false;
//                    }
//                }
//            }
//            return true;

//        case KC_BSPC: {
//            // Initialize a boolean variable that keeps track
//            // of the delete key status: registered or not?
//            //
//            static bool delkey_registered;
//            if (record->event.pressed) {
//                // Detect the activation of either shift keys
//                if (mod_state & MOD_MASK_SHIFT) {
//                    // First temporarily canceling both shifts so that
//                    // shift isn't applied to the KC_DEL keycode
//                    del_mods(MOD_MASK_SHIFT);
//                    register_code(KC_DEL);
//                    // Update the boolean variable to reflect the status of KC_DEL
//                    delkey_registered = true;
//                    // Reapplying modifier state so that the held shift key(s)
//                    // still work even after having tapped the Backspace/Delete key.
//                    set_mods(mod_state);
//                    return false;
//                }
//            } else { // on release of KC_BSPC
//                     // In case KC_DEL is still being sent even after the release of KC_BSPC
//                if (delkey_registered) {
//                    unregister_code(KC_DEL);
//                    delkey_registered = false;
//                    return false;
//                }
//            }
//            // Let QMK process the KC_BSPC keycode as usual outside of shift
//            return true;
//        }
//        // TODO could I merge these like the swe chars?
//        case S_QUOTE:
//            if (record->event.pressed) {
//                single_quote_timer = timer_read();
//                tap_code16(KC_QUOT);
//            } else if (timer_elapsed(single_quote_timer) > TAPPING_TERM) {
//                tap_code16(KC_QUOT);
//                tap_code16(KC_LEFT);
//            }
//            return false;
//        case D_QUOTE:
//            if (record->event.pressed) {
//                double_quote_timer = timer_read();
//                tap_code16(KC_DQUO);
//            } else if (timer_elapsed(double_quote_timer) > TAPPING_TERM) {
//                tap_code16(KC_DQUO);
//                tap_code16(KC_LEFT);
//            }
//            return false;
//        // TODO could I merge this three like swe chars?
//        case CURLYS:
//            if (record->event.pressed) {
//                SEND_STRING("{}"SS_TAP(X_LEFT));
//            }
//            return false;
//        case BRCKETS:
//            if (record->event.pressed) {
//                SEND_STRING("[]"SS_TAP(X_LEFT));
//            }
//            return false;
//        case PARENS:
//            if (record->event.pressed) {
//                SEND_STRING("()"SS_TAP(X_LEFT));
//            }
//            return false;
//        case SE_AO:
//            if (record->event.pressed) {
//                tap_code16(A(KC_A));
//            }
//            return false;
//        case SE_AE:
//        case SE_OE:
//            if (record->event.pressed) {
//                uint8_t mod_state = get_mods();
//                if (mod_state & MOD_MASK_SHIFT) {
//                    del_mods(MOD_MASK_SHIFT);
//                }
//                tap_code16(A(KC_U));
//                set_mods(mod_state);
//                tap_code16(keycode == SE_AE ? KC_A : KC_O);
//            }
//            return false;
//        case CAPS:
//            if (record->event.pressed) {
//                toggle_caps_word();
//            }
//            return false;
//        // TODO these two are never used afaik
//        case SNAKE:
//        case CAMEL:
//            if (record->event.pressed) {
//                if (get_xcase_delimiter() != KC_NO) {
//                    disable_xcase();
//                } else {
//                    enable_xcase_with(keycode == SNAKE ? KC_UNDS : OSM(MOD_LSFT));
//                }
//            }
//            return false;
//        case SNK_SCM:
//            if (record->event.pressed) {
//                if (get_xcase_delimiter() != KC_NO) {
//                    disable_xcase();
//                    disable_caps_word();
//                } else {
//                    enable_caps_word();
//                    enable_xcase_with(KC_UNDS);
//                }
//            }
//            return false;
//    }
//    return true;
//}

