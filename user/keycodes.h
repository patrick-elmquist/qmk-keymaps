#pragma once

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SYSTEM MO(_SYSTEM)
#define NUM MO(_NUM)

#define QUIT RGUI(KC_Q)
#define CLOSE RGUI(KC_W)
#define RELOAD RGUI(KC_R)

#define WIN_LFT C(A(KC_LEFT))
#define WIN_RGT C(A(KC_RGHT))
#define WIN_MAX C(A(KC_ENT))
#define WIN_RES C(A(KC_BSPC))
#define WIN_CEN C(A(KC_C))

#define ALFRED RGUI(KC_SPC)
#define ITERM RGUI(KC_ESC)
#define BSP_WRD LALT(KC_BSPC)

#define LOW_ENT LT(_LOWER, KC_ENT)
#define RAI_ENT LT(_RAISE, KC_ENT)
#define LOW_SPC LT(_LOWER, KC_SPC)
#define RAI_ESC LT(_RAISE, KC_ESC)
#define CTL_BSP LCTL_T(KC_BSPC)

// Left-hand home row mods
#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)

#define HOME_A LCTL_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LGUI_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define GUI_K RGUI_T(KC_K)
#define ALT_L LALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)

#define HOME_N RSFT_T(KC_N)
#define HOME_E RGUI_T(KC_E)
#define HOME_I LALT_T(KC_I)
#define HOME_O RCTL_T(KC_O)

#define SFT_G LSFT(KC_G)

enum custom_keycodes {
    OS_LCTL = SAFE_RANGE,
    OS_LALT,
    OS_LGUI,
    OS_LSFT,

    RAI_BSP,
    SW_WIN,
    SW_APP,
    S_QUOTE,
    D_QUOTE,
    PARENS,
    BRCKETS,
    CURLYS,

    CAPS,
    CAMEL,
    SNAKE,
    SNK_SCM,

    SE_AO,
    SE_AE,
    SE_OE
};
