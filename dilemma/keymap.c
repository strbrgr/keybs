#include QMK_KEYBOARD_H

#ifdef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#include "timer.h"
#endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum dilemma_keymap_layers {
  LAYER_BASE = 0,
  LAYER_FUNCTION,
  LAYER_NAVIGATION,
  LAYER_POINTER,
  LAYER_NUMERAL,
  LAYER_SYMBOLS,
};

int word_length_count = 0;
int last_word_length = 0;
bool combos_on = true; // use combo feature by default

// Automatically enable sniping-mode on the pointer layer.
#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#ifndef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#ifndef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ESC_SYM LT(LAYER_SYMBOLS, KC_ESC)
#define D_NUM LT(LAYER_NUMERAL, KC_D)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

#ifndef POINTING_DEVICE_ENABLE
#define DRGSCRL KC_NO
#define DPI_MOD KC_NO
#define S_D_MOD KC_NO
#define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                     \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, \
       KC_A,    KC_R,    KC_S,    KC_T, ALL_T(KC_G), ALL_T(KC_M),    KC_N,    KC_E,    KC_I, KC_O, \
       KC_Z,    KC_X,    KC_C,    D_NUM,    KC_V,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, \
                               ESC_SYM, SPC_NAV, KC_ENT, KC_BSPC

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI

#define LAYOUT_LAYER_FUNCTION                                                                 \
    _______________DEAD_HALF_ROW_______________, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12, \
    ______________HOME_ROW_GACS_L______________, KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11, \
    _______________DEAD_HALF_ROW_______________, KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10, \
                               _______, XXXXXXX, XXXXXXX, XXXXXXX

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                  \
    QK_BOOT, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, QK_BOOT, \
    ______________HOME_ROW_GACS_L______________, ______________HOME_ROW_GACS_R______________, \
    _______, DRGSCRL, SNIPING, KC_BTN3, XXXXXXX, XXXXXXX, KC_BTN3, SNIPING, DRGSCRL, _______, \
                               KC_BTN2, KC_BTN1, KC_BTN1, KC_BTN2

#define LAYOUT_LAYER_NAVIGATION                                                               \
    _______________DEAD_HALF_ROW_______________, XXXXXXX, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, \
    ______________HOME_ROW_GACS_L______________, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, \
    _______________DEAD_HALF_ROW_______________,  XXXXXXX,KC_LBRC, KC_RBRC, KC_GT, KC_LT, \
                               XXXXXXX, _______,  XXXXXXX, XXXXXXX

#define LAYOUT_LAYER_NUMERAL                                                                  \
    _______________DEAD_HALF_ROW_______________,  KC_LBRC,    KC_7,   KC_8,    KC_9, KC_RBRC, \
    _______________DEAD_HALF_ROW_______________,  KC_MINS,    KC_4,   KC_5,    KC_6,  KC_EQL, \
    XXXXXXX, XXXXXXX, KC_BSPC, XXXXXXX, XXXXXXX,     KC_0,    KC_1,   KC_2,    KC_3, KC_DOT, \
                               XXXXXXX, XXXXXXX,  KC_COMM,   KC_BSPC

#define LAYOUT_LAYER_SYMBOLS                                                                  \
    _______________DEAD_HALF_ROW_______________, KC_CIRC, KC_PERC, KC_ASTR, KC_AMPR, KC_BSLS, \
    _______________DEAD_HALF_ROW_______________, KC_GRV, KC_QUOT, KC_DQUO, KC_EXLM, KC_PLUS, \
    _______________DEAD_HALF_ROW_______________, KC_TILD, KC_HASH, KC_AT, KC_DLR, KC_PIPE, \
                              XXXXXXX,  XXXXXXX, KC_MINS, KC_EQL

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        MEH_T(L14),  \
             MEH_T(R15),  RSFT_T(R16), RCTL_T(R17), RALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_2(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE))
  ),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_NAVIGATION] = LAYOUT_wrapper(LAYOUT_LAYER_NAVIGATION),
  [LAYER_NUMERAL] = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
  [LAYER_SYMBOLS] = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#ifdef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  if (abs(mouse_report.x) > DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD ||
      abs(mouse_report.y) > DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
    if (auto_pointer_layer_timer == 0) {
      layer_on(LAYER_POINTER);
    }
    auto_pointer_layer_timer = timer_read();
  }
  return mouse_report;
}

void matrix_scan_user(void) {
  if (auto_pointer_layer_timer != 0 &&
      TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >=
          DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
    auto_pointer_layer_timer = 0;
    layer_off(LAYER_POINTER);
  }
}
#endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
  dilemma_set_pointer_sniping_enabled(
      layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
  return state;
}
#endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif // POINTING_DEVICE_ENABLE

// combos don't forget to edit COMBO_COUNT in config.h
enum combo_events { SCREENSHOT, CAPSWORD, TAB, UNDERSCORE, DELETEWORD };
const uint16_t PROGMEM screenshot_combo[] = {KC_B, KC_J, COMBO_END};
const uint16_t PROGMEM caps_word_combo[] = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {LCTL_T(KC_S), RCTL_T(KC_E), COMBO_END};
const uint16_t PROGMEM underscore_combo[] = {KC_P, KC_L, COMBO_END}; 
const uint16_t PROGMEM delete_word_combo[] = {KC_H, KC_COMM, COMBO_END};
/* const uint16_t PROGMEM RBRACKET[] = {RCTL_T(KC_E), RALT_T(KC_I), COMBO_END}; */
/* const uint16_t PROGMEM LPRN[] = {LCTL_T(KC_S), LSFT_T(KC_T), COMBO_END}; */
/* const uint16_t PROGMEM RPRN[] = {RSFT_T(KC_N), RCTL_T(KC_E), COMBO_END}; */

combo_t key_combos[COMBO_COUNT] = {
    [SCREENSHOT] = COMBO_ACTION(screenshot_combo),
    [CAPSWORD] = COMBO_ACTION(caps_word_combo),
    [TAB] = COMBO_ACTION(tab_combo),
    [UNDERSCORE] = COMBO_ACTION(underscore_combo),
    [DELETEWORD] = COMBO_ACTION(delete_word_combo)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch (combo_index) {
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
  case TAB:
    if (pressed) {
      tap_code16(KC_TAB);
    }
    break;
  case UNDERSCORE:
    if (pressed) {
      tap_code16(KC_UNDS);
    }
    break;
  case DELETEWORD:
    if (pressed) {
      tap_code16(LOPT(KC_BSPC));
    }
    break;
  }
}