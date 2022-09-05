/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Let the keyboard decide primary/secondary
// TODO investigate if this is actually needed, doesn't seem like it...
// #define SPLIT_USB_DETECT

// Seems to be a lot of accidental mods with the undefs...
// #undef TAPPING_TERM_PER_KEY
// #undef TAPPING_FORCE_HOLD_PER_KEY
// #undef IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// Pick good defaults for enabling homerow modifiers
// #define TAPPING_TERM 200
#define PERMISSIVE_HOLD
// #define HOLD_ON_OTHER_KEY_PRESS
// #define IGNORE_MOD_TAP_INTERRUPT
// #define TAPPING_FORCE_HOLD

