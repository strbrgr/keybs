/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "layer_names.h"
#include "keycodes.h"

#ifdef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define NAV MO(_NAV)
#define SYM MO(_SYM)

// Automatically enable sniping-mode on the pointer layer.
#define DILEMMA_AUTO_SNIPING_ON_LAYER _POINTER

#ifdef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x5_2(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,       KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      LGUI_KA,  LALT_KR, LCTL_KS, LSFT_KT,  ALL_KG,     ALL_KM, RSFT_KN, RCTL_KE, RALT_KI, RGUI_KO,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_Z,    KC_X,    KC_C,   LNU_D,    KC_V,       KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                                   LSY_ESC, LNA_SPC,    KC_ENT,  KC_BSPC
  //                            ╰──────────────────╯ ╰──────────────────╯
  ),

  [_SYM] = LAYOUT_split_3x5_2(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_CIRC, KC_CIRC, KC_ASTR, KC_AMPR, KC_BSLS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,    KC_GRV, KC_QUOT, KC_DQUO, KC_EXLM, KC_PLUS,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,    KC_TILD, KC_HASH, KC_AT, KC_DLR, KC_PIPE,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                                  _______, XXXXXXX,    XXXXXXX, _______
  //                            ╰──────────────────╯ ╰──────────────────╯
  ),

  [_NUM] = LAYOUT_split_3x5_2(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
      XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,   XXXXXXX,   KC_7,   KC_8,   KC_9, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, KC_4,   KC_5,   KC_6,  XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,      KC_0,   KC_1,   KC_2,   KC_3,  XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                                  _______, KC_LSFT,     KC_SPC, _______
  //                            ╰──────────────────╯ ╰──────────────────╯
  ),

  [_NAV] = LAYOUT_split_3x5_2(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,   XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_LBRC, KC_RBRC, KC_GT,    KC_LT,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                                  _______, XXXXXXX,     XXXXXXX, _______
  //                            ╰──────────────────╯ ╰──────────────────╯
  ),

  [_POINTER] = LAYOUT_split_3x5_2(
    // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
        QK_BOOT, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,     S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX,QK_BOOT,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
        KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,   KC_F11,     KC_F12, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT,
    // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         _______, DRGSCRL, SNIPING, KC_BTN3, XXXXXXX,    XXXXXXX, KC_BTN3, SNIPING, DRGSCRL,  _______,
    // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                                    KC_BTN2, KC_BTN1,     KC_BTN1, KC_BTN2
    //                            ╰──────────────────╯ ╰──────────────────╯
    ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NAV, _SYM, _NUM);
}

enum combo_events {
  SCREENSHOT,
  CAPSWORD,
  LBRACKET,
  RBRACKET,
  LPRN,
  RPRN,
  TAB,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM screenshot_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM capsword_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM lbracket_combo[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM rbracket_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM lprn_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM rprn_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_R, KC_T, COMBO_END};


combo_t key_combos[] = {
  [SCREENSHOT] = COMBO_ACTION(screenshot_combo),
  [CAPSWORD] = COMBO_ACTION(capsword_combo),
  [LBRACKET] = COMBO_ACTION(lbracket_combo),
  [RBRACKET] = COMBO_ACTION(rbracket_combo),
  [LPRN] = COMBO_ACTION(lprn_combo),
  [RPRN] = COMBO_ACTION(rprn_combo),
  [TAB] = COMBO_ACTION(tab_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case SCREENSHOT:
      if (pressed) {
        tap_code16(LSG(KC_4));
      }
      break;
    case CAPSWORD:
      if (pressed) {
        caps_word_on();
      }
      break;
    case LBRACKET:
      if (pressed) {
        tap_code16(KC_LBRC);
      }
      break;
    case RBRACKET:
      if (pressed) {
        tap_code16(KC_RBRC);
      }
      break;
    case LPRN:
      if (pressed) {
        tap_code16(KC_LPRN);
      }
      break;
    case RPRN:
      if (pressed) {
        tap_code16(KC_RPRN);
      }
      break;
    case TAB:
      if (pressed) {
        tap_code16(KC_TAB);
      }
      break;
  }
}