#pragma once

#ifdef VIA_ENABLE
/* VIA configuration. */
#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#endif // VIA_ENABLE

/**
 * \brief Prevent normal rollover on alphas from accidentally triggering mods.
 *
 * Ignores key presses that interrupt a mod-tap.  Must-have for Home Row mod.
 *
 * Without `IGNORE_MOD_TAP_INTERRUPT`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 Mod(a)🠕 e🠕 ➞ Mod+e
 * With `IGNORE_MOD_TAP_INTERRUPT`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 Mod(a)🠕 e🠕 ➞ ae
 */

/* Charybdis-specific features. */

#ifdef POINTING_DEVICE_ENABLE
// Automatically enable the pointer layer when moving the trackball.  See also:
// - `DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS`
// - `DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD`
// #define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE
#define CIRQUE_PINNACLE_TAP_ENABLE
// #define USB_VBUS_PIN GP19
#define TAPPING_TERM 150
#define DILEMMA_DRAGSCROLL_REVERSE_Y
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define COMBO_COUNT 5
#define COMBO_TERM 30
#define CAPS_WORD_TOGGLE_KEY
