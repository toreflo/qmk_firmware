/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "keymap_extras/keymap_italian.h"

enum planck_layers {
  _QWERTY,
  _NUMBERS,
  _SYMBOLS,
  _FUNCTIONS,
  _MEDIA_AND_NAV,
  _ALT_GR,
  _NUM_PAD,
  _ADJUST
};

enum my_keycodes {
  L1 = SAFE_RANGE,
  L2,
  R1,
  R2,
  BACKLIT
};

//Tap dance enums
enum {
  ALT_L3 = 0,
};

#define BTICK ALGR(IT_QUOT)  // On Windows you need to define a custom Italian layout
#define TILDE ALGR(IT_IGRV)  // On Windows you need to define a custom Italian layout

#define L1 MO(_NUMBERS)
#define L2 MO(_SYMBOLS)
#define R1 MO(_MEDIA_AND_NAV)
#define R2 MO(_ALT_GR)

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 5,
  TRIPLE_HOLD = 6
};

int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |      |ENTER |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |Alt/L3|  L2  |  L1  |    Space    |  R1  |  R2  | INS  |  DEL | Bksp |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  IT_Q,    IT_W,        IT_E,    IT_R,    IT_T,    IT_Y,    IT_U,    IT_I,    IT_O,      IT_P,     IT_PLUS,
    KC_ESC,  IT_A,    IT_S,        IT_D,    IT_F,    IT_G,    IT_H,    IT_J,    IT_K,    IT_L,      _______,  KC_ENT,
    KC_LSFT, IT_Z,    IT_X,        IT_C,    IT_V,    IT_B,    IT_N,    IT_M,    IT_COMM, IT_DOT,    IT_MINS,  _______,
    KC_LCTL, KC_LGUI, TD(ALT_L3),  L2,      L1,      KC_SPC,  KC_SPC,  R1,      R2,      KC_INSERT, KC_DEL,   KC_BSPC
),

/* L1: Numbers
 * ,-----------------------------------------------------------------------------------.
 * |   \  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   €  |  ^   |   °  |      |      |  [   |  ]   |      |  ì   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  <   |      |      |      |      |      |      |  {   |  }   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBERS] = LAYOUT_planck_grid(
    IT_BSLS, IT_1,    IT_2,    IT_3,    IT_4,    IT_5,    IT_6,    IT_7,       IT_8,       IT_9,    IT_0,    IT_QUOT,
    _______, _______, _______, IT_EURO, IT_CIRC, IT_DEG,  _______, _______,    IT_LBRC,    IT_RBRC, _______, IT_IGRV,
    _______, IT_LABK, _______, _______, _______, _______, _______, _______,    IT_LCBR,    IT_RCBR, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    _______,    _______, _______, _______
),

/* L2: Symbols  (It is a shifted L1. Remove it if SHIFT+L2 is fine for you)
 * ,-----------------------------------------------------------------------------------.
 * |   |  |   !  |   "  |   £  |   $  |   %  |   &  |   /  |  (   |  )   |   =  |  ?   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   €  |  ^   |   °  |      |      |  [   |  ]   |      |  ^   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  >   |      |      |      |      |      |      |  {   |  }   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = LAYOUT_planck_grid(
    IT_PIPE, IT_EXLM, IT_DQUO, IT_PND,  IT_DLR,  IT_PERC, IT_AMPR, IT_SLSH,  IT_LPRN,  IT_RPRN, IT_EQL,  IT_QUES,
    _______, _______, _______, IT_EURO, IT_CIRC, IT_DEG,  _______, _______,  IT_LBRC,  IT_RBRC, _______, IT_CIRC,
    _______, IT_RABK, _______, _______, _______, _______, _______, _______,  IT_LCBR,  IT_RCBR, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______
),

/* L3: Functions
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTIONS] = LAYOUT_planck_grid(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______,  _______,  _______, _______, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______,  _______,  _______, _______, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______
),

/* R1: Media & Navigations
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      | Vol+ |      |      |      |      |  Up  |      |      | Home |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | Prev | Vol+ | Next |      |      | Left | Down |Right |      | Page+|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | Mute |      |      |      |      |      |      |      | Page-|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | PLAY/PAUSE  |      |      |      |      | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA_AND_NAV] = LAYOUT_planck_grid(
    _______, _______, _______,             KC_AUDIO_VOL_UP,    _______,             _______,             _______,             _______, KC_UP,   _______,  _______, KC_HOME,
    _______, _______, KC_MEDIA_PREV_TRACK, KC_AUDIO_VOL_DOWN,  KC_MEDIA_NEXT_TRACK, _______,             _______,             KC_LEFT, KC_DOWN, KC_RIGHT, _______, KC_PGUP,
    _______, _______, _______,             KC_AUDIO_MUTE,      _______,             _______,             _______,             _______, _______, _______,  _______, KC_PGDOWN,
    _______, _______, _______,             _______,            _______,             KC_MEDIA_PLAY_PAUSE, KC_MEDIA_PLAY_PAUSE, _______, _______, _______,  _______, KC_END
),

/* R2: Alt-gr
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |  è   |      |      |      |  ù   |  ì   |  ò   |  `   |  ~   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  à   |      |      |      |      |      |      |      |      |  @   |  #   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ALT_GR] = LAYOUT_planck_grid(
    _______, _______, _______, IT_EGRV, _______, _______, _______, IT_UGRV, IT_EGRV,  IT_OGRV,  BTICK,   TILDE,
    _______, IT_AGRV, _______, _______, _______, _______, _______, _______,  _______,  _______, IT_AT,   IT_HASH,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______
),

/* L1+L2: NumPad
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |  *   |  7   |  8   |  9   |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  /   |  4   |  5   |  6   |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  %   |  1   |  2   |  3   |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM_PAD] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, _______, _______, KC_KP_ASTERISK,  KC_KP_7,  KC_KP_8, KC_KP_9, KC_KP_PLUS,
    _______, _______, _______, _______, _______, _______, _______, KC_KP_SLASH,     KC_KP_4,  KC_KP_5, KC_KP_6, KC_KP_MINUS,
    _______, _______, _______, _______, _______, _______, _______, IT_PERC,         KC_KP_1,  KC_KP_2, KC_KP_3, KC_KP_EQUAL,
    _______, _______, _______, _______, _______, _______, _______, _______,         _______,  _______, _______, _______
),

/* L1+R1: Adjust
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite|      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  _______, _______, _______, _______,  _______, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
    BACKLIT, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NUMBERS, _SYMBOLS, _NUM_PAD);        // L1 + L2
  state = update_tri_layer_state(state, _NUMBERS, _MEDIA_AND_NAV, _ADJUST);   // L1 + R1
  return state;
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->pressed) return SINGLE_HOLD;
    else return SINGLE_TAP;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap alttap_state = {
  .is_press_action = true,
  .state = 0
};

void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alttap_state.state = cur_dance(state);
  switch (alttap_state.state) {
    case SINGLE_TAP: set_oneshot_layer(_FUNCTIONS, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    //case DOUBLE_TAP: set_oneshot_layer(1, ONESHOT_START); set_oneshot_layer(1, ONESHOT_PRESSED); break;
    case DOUBLE_HOLD: register_code(KC_LALT); layer_on(_FUNCTIONS); break;
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alttap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    //case DOUBLE_TAP: break;
    case DOUBLE_HOLD: layer_off(_FUNCTIONS); unregister_code(KC_LALT); break;
  }
  alttap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [ALT_L3]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TRNS:
    case KC_NO:
      /* Always cancel one-shot layer when another key gets pressed */
      if (record->event.pressed && is_oneshot_layer_active())
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      return true;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_MEDIA_AND_NAV)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case L1:
    case L2:
    //case ALT_L3:
    case R1:
    case R2:
      return false;
    default:
      return true;
  }
}
