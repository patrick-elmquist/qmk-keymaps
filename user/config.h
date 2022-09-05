#pragma once

#define TAPPING_TERM 200

#define COMBO_TERM 35
#define COMBO_TERM_PER_COMBO
#define COMBO_MUST_TAP_PER_COMBO

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 3000

#define TAPPING_TERM_PER_KEY
#define TAPPING_FORCE_HOLD_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

#define SPLIT_MODS_ENABLE

// Should reduce the total firmware footprint according to some blog post
#define DISABLE_LEADER

// Not supported without flto
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
