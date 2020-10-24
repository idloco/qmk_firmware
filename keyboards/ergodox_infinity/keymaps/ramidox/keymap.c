#include QMK_KEYBOARD_H
#include "debug.h"
#include "led.h"
#include "action_layer.h"
#include "action_util.h"
#include "eeconfig.h"
#include "version.h"

#ifdef SUBPROJECT_infinity
#include "infinity.h"
#endif

enum layers {
    _BASE,
    _MAC,
    _FN,
    _NUM
};

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ergodox(KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_MINS, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_BSLS, LALT(KC_LSFT), KC_A, KC_S, KC_D, KC_F, KC_G, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, TT(2), KC_LCTL, LCTL(KC_C), LCTL(KC_V), KC_LGUI, KC_LALT, KC_F5, KC_F6, KC_F10, KC_SPC, KC_ENT, KC_F11, KC_EQL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_LBRC, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_RBRC, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, TT(3), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_DEL, KC_HOME, KC_END, TG(1), LALT(KC_TAB), KC_ENT, KC_SPC),
  [_MAC]  = LAYOUT_ergodox(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_SPC), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_C), LGUI(KC_V), KC_LALT, KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_SPC), KC_TRNS, KC_TRNS),
  [_FN]   = LAYOUT_ergodox(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F11, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_NO, KC_MPLY, KC_MSTP, KC_NO, KC_F12, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MFFD, KC_MRWD, KC_TRNS, KC_TRNS),
  [_NUM]  = LAYOUT_ergodox(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, BL_TOGG, BL_STEP, BL_INC, KC_TRNS, KC_TRNS, BL_DEC, KC_NO, KC_NO, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_TRNS, KC_NO, KC_P4, KC_P5, KC_P6, KC_PCMM, KC_TRNS, KC_TRNS, KC_NO, KC_P1, KC_P2, KC_P3, KC_PEQL, KC_TRNS, KC_P0, KC_P0, KC_PDOT, KC_PENT, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};

