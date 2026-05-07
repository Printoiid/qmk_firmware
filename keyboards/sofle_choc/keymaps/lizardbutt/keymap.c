// Include statements
#include QMK_KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>

// This is used later in the OLED Screensaver
bool oled_screensaver_active = false;

// Animation timer/frames
#define FRAME_DURATION 75
uint32_t timer = 0;
uint8_t current_frame = 0;

// Import the stuff you need *after* defining globals... Duh
#include "triforce.h"
//#include "ivy.h"

// Current KB Layers and their names
enum sofle_layers {
    _BASE,
    _FUNC,
    _CHARACTERS,
    _GAMES,
    _LAYERSWITCH,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * | ESC    | 1   | 2    | 3    | 4    | 5   |                     | 6    | 7    | 8    | 9    | 0    | - _  |
 * |--------+-----+------+------+------+-----|                     |------+------+------+------+------+------|
 * | Tab    | Q   | W    | E    | R    | T   |                     | Y    | U    | I    | O    | P    | \ |  |
 * |--------+-----+------+------+------+-----|                     |------+------+------+------+------+------|
 * | LShift | A   | S    | D    | F    | G   |--------.    ,-------| H    | J    | K    | L    | ; :  | ' "  |
 * |--------+-----+------+------+------+-----| Mute   |    | P/P   |------+------+------+------+------+------|
 * | LCTRL  | Z   | X    | C    | V    | B   |--------|    |-------| N    | M    | = +  | , <  | . >  | / ?  |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *         | LGUI | LAlt | MO 1 | Backspc | / Enter /        \ MO 1 \  | Space | MO 2 |      | MO 3 |
 *         |      |      |      |         |/       /          \      \ |       |      |      |      |
 *         '------------------------------''------'            '------''----------------------------'       */
[_BASE] = LAYOUT(
  KC_ESC,  KC_1, KC_2,    KC_3,    KC_4,      KC_5,                         KC_6,     KC_7,            KC_8,     KC_9,             KC_0,    KC_MINS,
  KC_TAB,  KC_Q, KC_W,    KC_E,    KC_R,      KC_T,                         KC_Y,     KC_U,            KC_I,     KC_O,             KC_P,    KC_BSLS,
  KC_LSFT, KC_A, KC_S,    KC_D,    KC_F,      KC_G,                         KC_H,     KC_J,            KC_K,     KC_L,             KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z, KC_X,    KC_C,    KC_V,      KC_B,    KC_MUTE,    KC_MPLY, KC_N,     KC_M,            KC_EQUAL, KC_COMMA,         KC_DOT,  KC_SLSH,
                 KC_LGUI, KC_LALT, MO(_FUNC), KC_BSPC, KC_ENT,     KC_RGUI, KC_SPACE, MO(_CHARACTERS), XXXXXXX,  MO(_LAYERSWITCH)
),
/* Function
 * ,--------------------------------------------.                     ,------------------------------------------.
 * | F1     | F2   | F3   | F4   | F5   | F6    |                     |      |      |      |      |      | NMLCK |
 * |--------+------+------+------+------+-------|                     |------+------+------+------+------+-------|
 * | F7     | F8   | F9   | F10  | F11  | F12   |                     |      | 7    | 8    | 9    |      |       |
 * |--------+------+------+------+------+-------|                     |------+------+------+------+------+-------|
 * | LShift | CAPS | +    | -    |      |       |--------.    ,-------| DEL  | 4    | 5    | 6    | 0    |       |
 * |--------+------+------+------+------+-------| TOGRGB |    |       |------+------+------+------+------+-------|
 * | CTRL   | ALT  | *    | /    | =    |       |--------|    |-------|      | 1    | 2    | 3    | .    | PRSCR |
 * `--------------------------------------------/       /      \      \------------------------------------------'
 *            | PT    | PT   |     | Backspc | / Enter /        \      \  |      | CTRL | ALT  | DEL  |
 *            |       |      |     |         |/       /          \      \ |      |      |      |      |
 *            '------------------------------''------'            '------''---------------------------'            */
[_FUNC] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,          KC_F4,       KC_F5,    KC_F6,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_NUM_LOCK,
  KC_F7,   KC_F8,   KC_F9,          KC_F10,      KC_F11,   KC_F12,                        XXXXXXX, KC_P7,   KC_P8,   KC_P9,   XXXXXXX, XXXXXXX,
  KC_LSFT, KC_CAPS, KC_KP_PLUS,     KC_KP_MINUS, XXXXXXX,  XXXXXXX,                       KC_DEL,  KC_P4,   KC_P5,   KC_P6,   KC_P0,   XXXXXXX,
  KC_LCTL, KC_LALT, KC_KP_ASTERISK, KC_KP_SLASH, KC_EQUAL, XXXXXXX, UG_TOGG,     XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_PSCR,
            		KC_TRNS,        KC_TRNS,     XXXXXXX,  KC_BSPC, KC_ENT,      XXXXXXX, XXXXXXX, KC_LCTL, KC_RALT, KC_DEL
),
/* Characters
 * ,------------------------------------------.                    ,-------------------------------------------.
 * |      |      |      | [    | ]    | *     |                    |       |      |      |       |      |      |
 * |------+------+------+------+------+-------|                    |-------+------+------+-------+------+------|
 * | `    | '    | "    | (    | )    | +     |                    |       |      | Up   |       | PGUP |      |
 * |------+------+------+------+------+-------|                    |-------+------+------+-------+------+------|
 * | PT   | ~    | $    | {    | }    | -     |--------.   ,-------| DEL   | Left | Down | Right | PGDN |      |
 * |------+------+------+------+------+-------|        |   |       |-------+------+------+-------+------+------|
 * | PT   | :    | @    | <    | >    | =     |--------|   |-------|       |      |      |       |      |      |
 * `------------------------------------------/       /     \      \-------------------------------------------'
 *            | PT   | PT   |    | Backspc | / Enter /       \      \  |      |      |       |       |
 *            |      |      |    |         |/       /         \      \ |      |      |       |       |
 *            '----------------------------''------'           '------''-----------------------------'         */
[_CHARACTERS] = LAYOUT(
   XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_ASTR,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
   KC_GRV,  KC_QUOT, KC_DQT,  KC_LPRN, KC_RPRN, KC_PLUS,                     XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  KC_PGUP, XXXXXXX,
   KC_TRNS, KC_TILD, KC_DLR,  KC_LCBR, KC_RCBR, KC_MINS,                     KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, XXXXXXX,
   KC_TRNS, KC_COLN, KC_AT,   KC_LABK, KC_RABK, KC_EQUAL, KC_TRNS,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
                     KC_TRNS, KC_TRNS, XXXXXXX, KC_BSPC,  KC_ENT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
/* Games
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * | ESC    | 1   | 2    | 3    | 4    | 5   |                     | 6    | 7    | 8    | 9    | 0    | - _  |
 * |--------+-----+------+------+------+-----|                     |------+------+------+------+------+------|
 * | Tab    | Q   | W    | E    | R    | T   |                     | Y    | U    | I    | O    | P    | \ |  |
 * |--------+-----+------+------+------+-----|                     |------+------+------+------+------+------|
 * | LShift | A   | S    | D    | F    | G   |--------.    ,-------| H    | J    | K    | L    | ; :  | ' "  |
 * |--------+-----+------+------+------+-----| Mute   |    | P/P   |------+------+------+------+------+------|
 * | LCTRL  | Z   | X    | C    | V    | B   |--------|    |-------| N    | M    | = +  | , <  | . >  | / ?  |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *         | PT   | PT   |      | Space   | / BKSPC /        \ ENT  \  | Space |      |      | SWCH |
 *         |      |      |      |         |/       /          \      \ |       |      |      |      |
 *         '------------------------------''------'            '------''----------------------------'       */
[_GAMES] = LAYOUT(
  KC_ESC,  KC_1, KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,      KC_7,    KC_8,     KC_9,            KC_0,    KC_MINS,
  KC_TAB,  KC_Q, KC_W,    KC_E,    KC_R,    KC_T,                             KC_Y,      KC_U,    KC_I,     KC_O,            KC_P,    KC_BSLS,
  KC_LSFT, KC_A, KC_S,    KC_D,    KC_F,    KC_G,                             KC_H,      KC_J,    KC_K,     KC_L,            KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z, KC_X,    KC_C,    KC_V,    KC_B,     KC_MUTE,      KC_MPLY,  KC_N,      KC_M,    KC_EQUAL, KC_COMMA,        KC_DOT,  KC_SLSH,
                 KC_TRNS, KC_TRNS, XXXXXXX, KC_SPACE, KC_BACKSPACE, KC_ENTER, KC_SPACE,  XXXXXXX, XXXXXXX,  MO(_LAYERSWITCH)
),
/* LayerSwitch
 * ,------------------------------------------.                     ,-----------------------------------------.
 * |       |      |      |      |      |      |                     |      |      |      |      |      | BASE |
 * |-------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |       |      |      |      |      |      |                     |      |      |      |      |      |      |
 * |-------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |       |      |      |      |      |      |--------.    ,-------|      |      |      |      |      |      |
 * |-------+------+------+------+------+------|        |    |       |------+------+------+------+------+------|
 * |       |      |      |      |      |      |--------|    |-------|      |      |      |      |      | GAME |
 * `------------------------------------------/       /      \      \-----------------------------------------'
 *             |      |      |      |      | /       /        \      \  |      |      |      |      |
 *             |      |      |      |      |/       /          \      \ |      |      |      |      |
 *             '---------------------------''------'            '------''---------------------------'        */
[_LAYERSWITCH] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_BASE),
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_GAMES),
                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
};
/* Template layout
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                     |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                     |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|        |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |--------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            |      |      |      |      | /       /        \      \  |      |      |      |      |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            '---------------------------''------'            '------''---------------------------'        */
/*
[_TEMPLATE] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),
*/

// Set the light mode when first powered on
void matrix_init_user() {
	rgblight_mode(5);
	rgblight_enable();
}

// Orients the non-master hand to display right-side-up
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;  // flips the display 270 degrees if mainhand
    } else {
        oled_clear();
        return OLED_ROTATION_270;  // flips the display 270 degrees if offhand
    }
    return rotation;
}

// This works now, just need a better animation.
bool oled_task_user(void) {
    // If the keyboard is active and screensaver is on, turn the OLED on and clear it once
    // This seems redundant, but it's added to reset the OLED after coming back from AFK
	if(last_input_activity_elapsed() < OLED_SCREENSAVER_TIMEOUT && oled_screensaver_active == true) {
        oled_screensaver_active = false;
        rgblight_enable();
        oled_on();
        oled_clear();
    }
	// Draw the layer information and change layer colors after and when the screensaver is disabled.
	if(last_input_activity_elapsed() < OLED_SCREENSAVER_TIMEOUT && oled_screensaver_active == false) {
        rgblight_enable();
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                oled_write_P("-==-\nMain\nLayer\n-==-\n", false);
                rgblight_mode(11);
                rgblight_sethsv(127, 255, 255);
                break;
            case _FUNC:
                oled_write_P("-==-\nFunc\nLayer\n-==-\n", false);
                rgblight_mode(11);
                rgblight_sethsv(148, 255, 255);
                break;
            case _CHARACTERS:
                oled_write_P("-==-\nChar\nLayer\n-==-\n", false);
                rgblight_mode(1);
                rgblight_sethsv(190, 255, 255);
                break;
            case _GAMES:
                oled_write_P("-==-\nGame\nLayer\n-==-\n", false);
                rgblight_mode(26);
                rgblight_sethsv(200, 255, 255);
                break;
            case _LAYERSWITCH:
                oled_write_P("-==-\nSwch\nLayer\n-==-\n", false);
                rgblight_mode(20);
                rgblight_sethsv(1, 255, 255);
                break;
        }
		// Draw that silly little triforce animation
        triforce_animation();
    }
    // If the oled is on, but has been idle for longer than the screensaver time, turn the OLED off
    if(is_oled_on() && last_input_activity_elapsed() > OLED_TIMEOUT) {
        rgblight_disable();
        oled_clear();
        oled_off();
        oled_screensaver_active = false;
    // If the OLED is on, but has been idle for a while, turn the screensaver on
    } else if(is_oled_on() && last_input_activity_elapsed() > OLED_SCREENSAVER_TIMEOUT) {
        oled_screensaver_active = true;
		// ivy_animation();
        rgblight_mode(5);
        rgblight_sethsv(150, 255, 255);
        return false;
    }
    return false;
}

bool encoder_update_kb(uint8_t index, bool clockwise) {

	if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    // clockwise is technically counter clockwise, I'm t oo lazy to inverse it.
    switch (get_highest_layer(layer_state)) {
        case _BASE :
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
            }
            break;
        case _FUNC :
            if (index == 0) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
            }
            break;
        case _CHARACTERS :
            if (index == 0) {
                if (clockwise) {
                    tap_code(MS_WHLD);
                } else {
                    tap_code(MS_WHLU);
                }
            } else if (index == 1) {
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
            }
            break;
    }
    return true;
}
