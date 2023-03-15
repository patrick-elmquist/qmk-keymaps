#pragma once

#define TAPPING_TERM 200

#define COMBO_TERM 35
#define COMBO_TERM_PER_COMBO
#define COMBO_MUST_TAP_PER_COMBO

#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
#define QUICK_TAP_TERM_PER_KEY
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define SPLIT_MODS_ENABLE

#define THUMB_EXTRA 45
#define INDEX_EXTRA 0
#define LONG_EXTRA 0
#define RING_EXTRA 0
#define PINKY_EXTRA 0

// Should reduce the total firmware footprint according to some blog post
#define DISABLE_LEADER

// Not supported without flto
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
