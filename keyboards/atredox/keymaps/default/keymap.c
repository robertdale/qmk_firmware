#include "atredox.h"
#include "action_layer.h"
#include "eeconfig.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _RAISE 1

enum atredox_keycodes {
  QWERTY = SAFE_RANGE,
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,---------------------------------------------------------------------------------------------------------------.
 * |   =  |   1  |   2  |   3  |   4  |   5  |      |      |      |      |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |      |      |      |      |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------+------|
 * | Ctl  |   A  |   S  |   D  |   F  |   G  |      |      |      |      |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  | Ctl  | Alt  | Alt  | Ctl  |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Raise|   `  |   \  | Left | Right| Bksp | Del  |      |      | Enter| Space| Down |  Up  |   [  |   ]  |Raise |
 * `---------------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_EQL,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS},
  {KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS},
  {KC_LCTL, KC_A,   KC_S,    KC_D,    KC_F,     KC_G,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    KC_LCTL, KC_LALT, KC_RALT, KC_RCTL, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
  {RAISE,   KC_GRV, KC_BSLS, KC_LEFT, KC_RIGHT, KC_BSPC, KC_DEL,  KC_NO,   KC_NO,   KC_ENT,  KC_SPC, KC_DOWN, KC_UP,   KC_LBRC, KC_RBRC, RAISE}
},

/* Raise
 * ,---------------------------------------------------------------------------------------------------------------.
 * |  ESC |   F1 |  F2  |  F3  |  F4  |  F5  |      |      |      |      |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |  F11 |  F12 |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | Home | End  |      |      |      |      |      |      |PgDown| PgUp |      |      |      |
 * `---------------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_ESC,  KC_F1,  KC_F2,   KC_F3,   KC_F4,    KC_F5,_______,_______,_______,_______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______},
  {_______,_______,_______,KC_HOME, KC_END,_______,_______,_______,_______,_______,_______,KC_PGDN,KC_PGUP,_______,_______,_______}
}

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            persistant_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
          } else {
            layer_off(_RAISE);
          }
          return false;
          break;
      }
    return true;
};

void matrix_init_user(void) {
}

