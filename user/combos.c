#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "print.h"

// Combo functions
bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    switch(index) {
        case HCOM_DQUOT:
        case VCB_LN:
        case VCB_NH:
            return false;
    }
    return true;
}

bool combo_should_trigger(
        uint16_t combo_index,
        combo_t *combo,
        uint16_t keycode,
        keyrecord_t *record
    ) {
    return true;
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    uint16_t term;
    switch (index) {
        case WP_CBR_PAIR:
        case WF_LCBR:
        case FP_RCBR:
            term = 45;
            break;

        case RAI_ENT:
        case RS_LPRN:
        case ST_RPRN:
        case RT_PRN_PAIR:

        case XC_COPY:
        case CD_PASTE:
        case LU_QUES_DOT:

        case LUY_SNAKE_SCREAM:
            term = 30;
            break;

        case VCB_LN:
        case VCB_NH:
        case XD_CUT:
        case ZX_UNDO:
        case UY_QUOT:
        case EI_TAB:
        case NI_EQL:
            term = 40;
            break;

        case NE_ESC:
            term = 50;
            break;

        case HCOM_DQUOT:
        case SWE_AO:
        case SWE_AE:
        case SWE_OE:
            term = 45;
            break;

        case LTGT_ARROW:
        case XCD_PASTE_SFT:
        case WFP_CBR_PAIR_IN:
        case RST_PRN_PAIR_IN:
        case NEI_ENT:

        default:
            term = 45;
            break;
    }
    return term;
}

