// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "animation.c"



enum layers {
    _ALPHA_QWERTY = 0,
    _NAV,
    _SYM,
    _NUM,
    _FUN,
};

// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LCTL_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RCTL_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RGUI_T(KC_SCLN)

#define REDO LCTL_T(KC_Y)
#define PASTE LSFT_T(KC_INS)
#define COPY LCTL_T(KC_INS)
#define CUT LSFT_T(KC_DEL)
#define UNDO LCTL_T(KC_Z)

#define SWC_WIN LALT(KC_TAB)
#define SEARCH LGUI(KC_SPC)	

#define MS_LCLK KC_MS_BTN1
#define MS_RCLK KC_MS_BTN2
#define MS_W_UP KC_MS_WH_UP
#define MS_W_DN KC_MS_WH_DOWN

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

    [_ALPHA_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        HOME_A,       HOME_S,  HOME_D,  HOME_F,  KC_G,                                                KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN,
        KC_Z,         KC_X,    KC_C,    KC_V,    KC_B,                                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                        LT(_NUM, KC_ESC), LT(_FUN, KC_SPC), LT(_NAV, KC_TAB),     LT(_SYM, KC_BSPC), LSFT_T(KC_ENT), LALT_T(KC_DEL)
    ),
    [_NAV] = LAYOUT_split_3x5_3(
        MS_W_UP,      MS_LCLK, KC_MS_U, MS_RCLK, MS_W_UP,                                             KC_INS,  KC_PGDN, KC_UP,   KC_PGUP, KC_DEL,
        MS_W_DN, KC_MS_L, KC_MS_D, KC_MS_R,   MS_W_DN,                                              KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                              UNDO,   CUT,     COPY,    PASTE,   REDO,
                        LT(_NUM, KC_ESC), LT(_FUN, KC_SPC), LT(_NAV, KC_TAB),     LT(_SYM, KC_BSPC), LSFT_T(KC_ENT), LALT_T(KC_DEL)
    ),
    [_SYM] = LAYOUT_split_3x5_3(
        KC_EXLM, KC_AT,   KC_HASH, KC_DOLLAR, KC_PERCENT,                                             KC_AMPR, KC_SLSH, KC_LPRN, KC_RPRN, KC_EQL,
        KC_TILD, KC_QUOT, XXXXXXX , XXXXXXX,  XXXXXXX,                                                KC_ASTR, KC_PLUS, KC_LBRC, KC_RBRC, KC_QUES,
        KC_PIPE, KC_LT,   KC_GT,   KC_PERC,   XXXXXXX,                                                KC_PMNS, KC_UNDS, KC_LCBR, KC_RCBR, XXXXXXX,
                        LT(_NUM, KC_ESC), LT(_FUN, KC_SPC), LT(_NAV, KC_TAB),     LT(_SYM, KC_BSPC), LSFT_T(KC_ENT), LALT_T(KC_DEL)
    ),
    [_NUM] = LAYOUT_split_3x5_3(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_PAST, KC_PSLS, KC_PDOT, KC_PSLS, KC_PPLS,                                                  KC_NUM,  XXXXXXX, XXXXXXX, XXXXXXX, KC_CALC,
        KC_PEQL, XXXXXXX, XXXXXXX, XXXXXXX, KC_PENT,                                                  UNDO,    CUT,     COPY,    PASTE,   REDO,
                        LT(_NUM, KC_ESC), LT(_FUN, KC_SPC), LT(_NAV, KC_TAB),     LT(_SYM, KC_BSPC), LSFT_T(KC_ENT), LALT_T(KC_DEL)
    ),
    [_FUN] = LAYOUT_split_3x5_3(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                                    KC_VOLD, KC_MUTE, KC_VOLU, CK_TOGG, KC_SLEP,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                                                   KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_PWR,
        KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX,                                                  KC_BRID, KC_BRIU, SEARCH,  SWC_WIN, KC_PSCR,
                        LT(_NUM, KC_ESC), LT(_FUN, KC_SPC), LT(_NAV, KC_TAB),     LT(_SYM, KC_BSPC), LSFT_T(KC_ENT), LALT_T(KC_DEL)
    ),
    // clang-format on
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) { 
       if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return OLED_ROTATION_270; 
}


void render_animation(uint8_t frame) {
    if (last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return;
    }
    oled_write_raw_P(animation[frame], sizeof(animation[frame]));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
       extern void render_mod_status(void);
       render_mod_status();
    }
    else {
        render_animation((timer_read() / 60) % 10);
    }
    return false;
}