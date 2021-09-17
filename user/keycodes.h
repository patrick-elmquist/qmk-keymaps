#pragma once

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SYSTEM MO(_SYSTEM)

#define QUIT RGUI(KC_Q)
#define ALFRED RGUI(KC_SPC)
#define ITERM RGUI(KC_ESC)

enum custom_keycodes {
    OS_LCTL = SAFE_RANGE,
    OS_LALT,
    OS_LGUI,
    OS_LSFT,

    OS_RAIS,
    SW_WIN,
    REPEAT,
    ADAPT,
    QUOTES,
    PARENS,
    CURLYS,

    CAPS,
    CAMEL,
    SNAKE,
    SNK_SCM,

    SE_AO,
    SE_AE,
    SE_OE
};
