#include QMK_KEYBOARD_H

enum charybdis_keymap_heyjochen_layers {
    LAYER_BASE = 0,
    LAYER_MBO,
    LAYER_MEDIA,
    LAYER_NAV,
    LAYER_MOUSE,
    LAYER_SYM,
    LAYER_NUM,
    LAYER_FUN,
};

int word_length_count = 0;
int last_word_length = 0;
bool combos_on = true; // use combo feature by default

// Automatically enable sniping when the mouse layer is on.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_MOUSE

#define BSP_FUN LT(LAYER_FUN, KC_BSPC)
#define ENT_MBO LT(LAYER_MBO, KC_ENT)
//#define TAB_NUM LT(LAYER_NUM, KC_TAB)
#define ESC_SYM LT(LAYER_SYM, KC_ESC)
#define SPC_NAV LT(LAYER_NAV, KC_SPC)
#define MOUSE(KC) LT(LAYER_MOUSE, KC)
#define D_NUM LT(LAYER_NUM, KC_D)

#define USR_RDO KC_AGAIN
#define USR_PST S(KC_INS)
#define USR_CPY C(KC_INS)
#define USR_CUT S(KC_DEL)
#define USR_UND KC_UNDO

#define MS_L KC_MS_LEFT
#define MS_R KC_MS_RIGHT
#define MS_D KC_MS_DOWN
#define MS_U KC_MS_UP

#define WH_L KC_MS_WH_LEFT
#define WH_R KC_MS_WH_RIGHT
#define WH_D KC_MS_WH_DOWN
#define WH_U KC_MS_WH_UP

/** Base layer with BÉPO layout. */
#define LAYOUT_LAYER_BASE             \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, \
       KC_Z,    KC_X,    KC_C,    D_NUM,    KC_V,    KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, \
       ESC_SYM, SPC_NAV, KC_TAB,  ENT_MBO, BSP_FUN
/** Convenience key shorthands. */
#define U_NA KC_NO // Present but not available for use.
#define U_NU KC_NO // Available but not used.

/** Convenience row shorthands. */
#define __________________RESET_L__________________ QK_BOOT,    EE_CLR,    U_NA,    U_NA,    U_NA
#define __________________RESET_R__________________    U_NA,    U_NA,    U_NA,    EE_CLR, QK_BOOT
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,    U_NA
#define ______________HOME_ROW_ALGR_L______________    U_NA, KC_ALGR,    U_NA,    U_NA,    U_NA
#define ______________HOME_ROW_GASC_R______________    U_NA, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI
#define ______________HOME_ROW_ALGR_R______________    U_NA,    U_NA,    U_NA, KC_ALGR,    U_NA

/** Layers. */

// Buttons.
#define LAYOUT_LAYER_MBO                                                                      \
    __________________RESET_L__________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________, KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1,    U_NA,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                         U_NA,    U_NA,    U_NA,  KC_ENT,  KC_DEL

// Media.
#define LAYOUT_LAYER_MEDIA                                                                    \
    __________________RESET_L__________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________,    U_NU,    MS_L,    MS_D,    MS_U,    MS_R, \
    ______________HOME_ROW_ALGR_L______________,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                         U_NA,    U_NA,    U_NA, KC_BTN1, KC_BTN3

// Navigation.
#define LAYOUT_LAYER_NAV                                                                      \
    __________________RESET_L__________________, XXXXXXX, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, \
    ______________HOME_ROW_GASC_L______________, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, \
    ______________HOME_ROW_ALGR_L______________,   U_NU,  KC_LBRC, KC_RBRC, KC_GT,     KC_LT, \
                         U_NA,    U_NA,    U_NA, KC_MSTP, KC_MPLY

// Mouse.
#define LAYOUT_LAYER_MOUSE                                                                    \
    S_D_MOD, USR_PST, USR_CPY, USR_CUT, USR_UND, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________,    U_NU,    MS_L,    MS_D,    MS_U,    MS_R, \
    DPI_MOD, DRGSCRL, USR_CPY, USR_CUT, USR_UND,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN1, KC_BTN3

// Symbols.
#define LAYOUT_LAYER_SYM                                                                      \
    __________________RESET_L__________________, KC_CIRC, KC_PERC, KC_ASTR, KC_AMPR, KC_BSLS, \
    ______________HOME_ROW_GASC_L______________, KC_GRV, KC_QUOT, KC_DQUO, KC_EXLM, KC_PLUS, \
    ______________HOME_ROW_ALGR_L______________, KC_TILD, KC_HASH, KC_AT, KC_DLR, KC_PIPE, \
                        U_NA,    U_NA,    U_NA , KC_MINS, KC_EQL

// Numerals.
#define LAYOUT_LAYER_NUM                                                                      \
    __________________RESET_L__________________,  KC_LBRC,    KC_7,   KC_8,    KC_9, KC_RBRC, \
    ______________HOME_ROW_GASC_L______________,  KC_MINS,    KC_4,   KC_5,    KC_6,  KC_EQL, \
    U_NA,    U_NA,      KC_BSPC,  U_NA,    U_NA,     KC_0,    KC_1,   KC_2,    KC_3, KC_DOT, \
                        U_NA,    U_NA,    U_NA ,  KC_COMM,   KC_BSPC

// Function keys.
#define LAYOUT_LAYER_FUN                                                                      \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR, __________________RESET_R__________________, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL, ______________HOME_ROW_GASC_R______________, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, ______________HOME_ROW_ALGR_R______________,\
                        KC_APP,  KC_SPC,  KC_TAB, U_NA,    U_NA

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GASC (Gui, Alt, Shift, Ctl)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE_BEPO` defined above, eg.:
 *
 *     HOME_ROW_MOD_GASC(LAYOUT_LAYER_BASE_BEPO)
 */
#define _HOME_ROW_MOD_GASC(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13), MEH_T(L14),  \
      MEH_T(R15), RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GASC(...) _HOME_ROW_MOD_GASC(__VA_ARGS__)

#define _MOUSE_MOD(                                               \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,             \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,             \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,             \
    ...)                                                          \
            L00,        L01,        L02,        L03,        L04,  \
            R05,        R06,        R07,        R08,        R09,  \
            L10,        L11,        L12,        L13,        L14,  \
            R15,        R16,        R17,        R18,        R19,  \
      MOUSE(L20),       L21,        L22,        L23,        L24,  \
            R25,        R26,        R27,        R28,  MOUSE(R29), \
      __VA_ARGS__
#define MOUSE_MOD(...) _MOUSE_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    MOUSE_MOD(HOME_ROW_MOD_GASC(LAYOUT_LAYER_BASE))
  ),
  [LAYER_MBO] = LAYOUT_wrapper(LAYOUT_LAYER_MBO),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NAV] = LAYOUT_wrapper(LAYOUT_LAYER_NAV),
  [LAYER_MOUSE] = LAYOUT_wrapper(LAYOUT_LAYER_MOUSE),
  [LAYER_SYM] = LAYOUT_wrapper(LAYOUT_LAYER_SYM),
  [LAYER_NUM] = LAYOUT_wrapper(LAYOUT_LAYER_NUM),
  [LAYER_FUN] = LAYOUT_wrapper(LAYOUT_LAYER_FUN),
};
// clang-format on

#if defined(POINTING_DEVICE_ENABLE) && defined(CHARYBDIS_AUTO_SNIPING_ON_LAYER)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#endif // POINTING_DEVICE_ENABLE && CHARYBDIS_AUTO_SNIPING_ON_LAYER

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb(RGB_RED);
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
}

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