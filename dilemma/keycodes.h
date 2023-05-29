enum custom_keycodes {
    K_COLEMAK = SAFE_RANGE,
};

// COLEMAK
#define LGUI_KA LGUI_T(KC_A)
#define LALT_KR LALT_T(KC_R)
#define LCTL_KS LCTL_T(KC_S)
#define LSFT_KT LSFT_T(KC_T)
#define ALL_KG  ALL_T(KC_G)
#define ALL_KM  ALL_T(KC_M)
#define RSFT_KN RSFT_T(KC_N)
#define RCTL_KE RCTL_T(KC_E)
#define RALT_KI RALT_T(KC_I)
#define RGUI_KO RGUI_T(KC_O)

// NUM
#define LALT_K1 LALT_T(KC_1)
#define LCTL_K2 LCTL_T(KC_2)
#define LGUI_K3 LGUI_T(KC_3)
#define LSFT_K4 LSFT_T(KC_4)
#define RSFT_K7 RSFT_T(KC_7)
#define RGUI_K8 RGUI_T(KC_8)
#define RCTL_K9 RCTL_T(KC_9)
#define RALT_K0 RALT_T(KC_0)

// SYM
#define LGU_GRV LGUI_T(KC_GRV)
#define LSF_QT LSFT_T(KC_QUOT)
#define RSF_MIN RSFT_T(KC_MINS)
#define RGU_EQL RGUI_T(KC_EQL)

// MISC
#define KC_CAPW LGUI(LSFT(KC_3)) // capture the whole screen on MacOS
#define KC_CAPP LGUI(LSFT(KC_5)) // capture portion of the screen on MacOS

// LAYERS
#define LSY_ESC LT(_SYM, KC_ESC)
#define LNU_D LT(_NUM, KC_D)
#define LNA_SPC LT(_NAV, KC_SPC)
