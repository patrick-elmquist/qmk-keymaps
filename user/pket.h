#pragma once

#include QMK_KEYBOARD_H

#include "layers.h"
#include "keycodes.h"
#include "oled.h"
#include "features/oneshot.h"
#include "features/swapper.h"
#include "features/repeat.h"
#include "features/casemodes.h"

#define _____________________QWERTY_L1______________________ KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T
#define _____________________QWERTY_L2______________________ CTL_BSP, CTL_A,   ALT_S,   GUI_D,  SFT_F,   KC_G
#define _____________________QWERTY_L3______________________ KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B

#define _____________________QWERTY_R1______________________ KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSLS
#define _____________________QWERTY_R2______________________ KC_H,    SFT_J,   GUI_K,   ALT_L,  CTL_SCLN,KC_QUOT
#define _____________________QWERTY_R3______________________ KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS

#define _____________________COLEMAK_L1_____________________ KC_TAB,  KC_Q,    KC_W,    KC_F,   KC_P,    KC_B
#define _____________________COLEMAK_L2_____________________ CTL_BSP, HOME_A,  HOME_R,  HOME_S, HOME_T,  KC_G
#define _____________________COLEMAK_L3_____________________ KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_D,    KC_V

#define _____________________COLEMAK_R1_____________________ KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS
#define _____________________COLEMAK_R2_____________________ KC_M,    HOME_N,  HOME_E,  HOME_I, HOME_O,  KC_QUOT
#define _____________________COLEMAK_R3_____________________ KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH, KC_MINS

#define _____________________LOWER__L1______________________ _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _____________________LOWER__L2______________________ _______, KC_HASH, BRCKETS, PARENS,  CURLYS,  KC_GRV
#define _____________________LOWER__L3______________________ _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD

#define _____________________LOWER__R1______________________ KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS
#define _____________________LOWER__R2______________________ KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_SCLN, KC_QUOT
#define _____________________LOWER__R3______________________ KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS


#define _____________________RAISE__L1______________________ _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _____________________RAISE__L2______________________ _______, XXXXXXX, KC_LBRC, KC_LPRN, KC_LCBR, SFT_G
#define _____________________RAISE__L3______________________ _______, XXXXXXX, KC_RBRC, KC_RPRN, KC_RCBR, XXXXXXX

#define _____________________RAISE__R1______________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS
#define _____________________RAISE__R2______________________ KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, QUOTES
#define _____________________RAISE__R3______________________ XXXXXXX, XXXXXXX, KC_COMM, KC_DOT, KC_SLSH, KC_MINS


#define _____________________SYSTEM_L1______________________ _______, QUIT,    CLOSE,   SW_WIN,  RELOAD,  ITERM
#define _____________________SYSTEM_L2______________________ _______, KC_9,    KC_5,    KC_3,    KC_1,    ALFRED
#define _____________________SYSTEM_L3______________________ _______, _______, _______, _______, KC_7,    _______

#define _____________________SYSTEM_R1______________________ _______, _______, _______, _______, _______, _______
#define _____________________SYSTEM_R2______________________ _______, KC_0,    KC_2,    KC_4,    KC_8,    _______
#define _____________________SYSTEM_R3______________________ _______, KC_6,    _______, _______, _______, _______


#define _____________________ADJUST_L1______________________ _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _____________________ADJUST_L2______________________ _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU
#define _____________________ADJUST_L3______________________ _______, _______, _______, _______, KC_MUTE, KC_VOLD

#define _____________________ADJUST_R1______________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  TG_QWER
#define _____________________ADJUST_R2______________________ _______, _______, _______, KC_F11,  KC_F12,  TG_COLM
#define _____________________ADJUST_R3______________________ _______, _______, _______, _______, _______, _______

#define _________MOD_LEFT________ RAISE,   SYSTEM,  LOW_SPC
#define _________MOD_RIGHT_______ RAI_BSP, LOWER,   KC_LGUI


#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
