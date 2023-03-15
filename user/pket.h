#pragma once

#include QMK_KEYBOARD_H

#include "layers.h"
#include "keycodes.h"
#include "oled.h"
#include "features/oneshot.h"
#include "features/swapper.h"
#include "features/casemodes.h"

// 5 column
#define ________________COLEMAK_L1_5_______________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ________________COLEMAK_L2_5_______________ HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G
#define ________________COLEMAK_L3_5_______________ KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ________________COLEMAK_R1_5_______________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ________________COLEMAK_R2_5_______________ KC_M,    HOME_N,  HOME_E,  HOME_I,  HOME_O
#define ________________COLEMAK_R3_5_______________ KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH


#define ________________HANDS_DOWN_L1_5____________ KC_Q,    KC_C,    KC_H,    KC_P,    KC_V
#define ________________HANDS_DOWN_L2_5____________ KC_R,    KC_S,    KC_N,    KC_T,    KC_G
#define ________________HANDS_DOWN_L3_5____________ KC_X,    KC_M,    KC_L,    KC_D,    KC_B

#define ________________HANDS_DOWN_R1_5____________ KC_K,    KC_Y,    KC_O,    KC_J,    KC_SCLN
#define ________________HANDS_DOWN_R2_5____________ KC_W,    KC_U,    KC_E,    KC_I,    KC_A
#define ________________HANDS_DOWN_R3_5____________ KC_Z,    KC_F,    KC_COMM, KC_DOT,  KC_SLSH






#define ________________LOWER__L1_5________________ KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define ________________LOWER__L2_5________________ _______, _______, _______, _______, KC_GRV
#define ________________LOWER__L3_5________________ KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD

#define ________________LOWER__R1_5________________ KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define ________________LOWER__R2_5________________ KC_PLUS, KC_MINS, KC_SLSH, KC_COMM, KC_SCLN
#define ________________LOWER__R3_5________________ KC_EQL,  KC_UNDS, KC_COMM, KC_DOT,  KC_SLSH

#define ________________LOWER2_L1_5________________ KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define ________________LOWER2_L2_5________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________LOWER2_L3_5________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define ________________LOWER2_R1_5________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________LOWER2_R2_5________________ KC_CIRC, KC_AMPR, KC_ASTR, XXXXXXX, XXXXXXX
#define ________________LOWER2_R3_5________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define ________________RAISE__L1_5________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________RAISE__L2_5________________ KC_LT,   KC_PERC, KC_LPRN, KC_LCBR, KC_LBRC
#define ________________RAISE__L3_5________________ KC_GT,   KC_DLR,  KC_RPRN, KC_RCBR, KC_RBRC

#define ________________RAISE__R1_5________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define ________________RAISE__R2_5________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________RAISE__R3_5________________ XXXXXXX, KC_UNDS, _______, _______, _______

#define ________________NAV_L1_5___________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NAV_L2_5___________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ________________NAV_L3_5___________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define ________________NAV_R1_5___________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define ________________NAV_R2_5___________________ KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX
#define ________________NAV_R3_5___________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX



#define ________________SYSTEM_L1_5________________ QUIT,    CLOSE,   SW_WIN,  SW_APP,  ITERM
#define ________________SYSTEM_L2_5________________ OS_LCTL, OS_LALT, OS_LGUI, OS_LSFT, ALFRED
#define ________________SYSTEM_L3_5________________ _______, _______, _______, _______, _______

#define ________________SYSTEM_R1_5________________ KC_LSFT, _______, WIN_MAX, BACK,    FORWARD
#define ________________SYSTEM_R2_5________________ _______, WIN_LFT, WIN_CEN, WIN_RGT, _______
#define ________________SYSTEM_R3_5________________ _______, WIN_RES, _______, _______, _______

#define ________________ADJUST_L1_5________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ________________ADJUST_L2_5________________ _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU
#define ________________ADJUST_L3_5________________ QK_BOOT, _______, _______, KC_MUTE, KC_VOLD

#define ________________ADJUST_R1_5________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
#define ________________ADJUST_R2_5________________ DFL_COL, _______, _______, KC_F11,  KC_F12
#define ________________ADJUST_R3_5________________ DFL_HDR, _______, _______, _______, _______

#define ___THUMB_LEFT___ SYSTEM,  LOW_SPC
#define ___THUMB_RIGHT__ RAI_ENT, NAV_BSP










// 6 column
#define _____________________COLEMAK_L1_____________________ KC_TAB,  ________________COLEMAK_L1_5_______________
#define _____________________COLEMAK_L2_____________________ CTL_BSP, ________________COLEMAK_L2_5_______________
#define _____________________COLEMAK_L3_____________________ KC_LSFT, ________________COLEMAK_L3_5_______________

#define _____________________COLEMAK_R1_____________________ ________________COLEMAK_R1_5_______________, KC_BSLS
#define _____________________COLEMAK_R2_____________________ ________________COLEMAK_R2_5_______________, KC_QUOT
#define _____________________COLEMAK_R3_____________________ ________________COLEMAK_R3_5_______________, KC_MINS

#define _____________________LOWER__L1______________________ _______, ________________LOWER__L1_5________________
#define _____________________LOWER__L2______________________ BSP_WRD, ________________LOWER__L2_5________________
#define _____________________LOWER__L3______________________ _______, ________________LOWER__L3_5________________

#define _____________________LOWER__R1______________________ ________________LOWER__R1_5________________, _______
#define _____________________LOWER__R2______________________ ________________LOWER__R2_5________________, _______
#define _____________________LOWER__R3______________________ ________________LOWER__R3_5________________, _______

#define _____________________RAISE__L1______________________ _______, ________________RAISE__L1_5________________
#define _____________________RAISE__L2______________________ _______, ________________RAISE__L2_5________________
#define _____________________RAISE__L3______________________ _______, ________________RAISE__L3_5________________

#define _____________________RAISE__R1______________________ ________________RAISE__R1_5________________, _______
#define _____________________RAISE__R2______________________ ________________RAISE__R2_5________________, D_QUOTE
#define _____________________RAISE__R3______________________ ________________RAISE__R3_5________________, _______

#define _____________________SYSTEM_L1______________________ _______, ________________SYSTEM_L1_5____________________
#define _____________________SYSTEM_L2______________________ _______, ________________SYSTEM_L2_5____________________
#define _____________________SYSTEM_L3______________________ _______, ________________SYSTEM_L3_5____________________

#define _____________________SYSTEM_R1______________________ ________________SYSTEM_R1_5____________________, _______
#define _____________________SYSTEM_R2______________________ ________________SYSTEM_R2_5____________________, _______
#define _____________________SYSTEM_R3______________________ ________________SYSTEM_R3_5____________________, _______

#define _____________________ADJUST_L1______________________ _______, ________________ADJUST_L1_5____________________
#define _____________________ADJUST_L2______________________ _______, ________________ADJUST_L2_5____________________
#define _____________________ADJUST_L3______________________ _______, ________________ADJUST_L3_5____________________

#define _____________________ADJUST_R1______________________ ________________ADJUST_R1_5____________________, _______
#define _____________________ADJUST_R2______________________ ________________ADJUST_R2_5____________________, _______
#define _____________________ADJUST_R3______________________ ________________ADJUST_R3_5____________________, _______

#define _________MOD_LEFT________ RAISE,   SYSTEM,  KC_SPC
#define _________MOD_RIGHT_______ RAISE,   LOWER,   KC_LGUI


#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
