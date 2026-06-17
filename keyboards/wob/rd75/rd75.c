/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
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

#include "../../lib/rdr_lib/rdr_common.h"

void matrix_io_delay(void)                                          {}
void matrix_output_select_delay(void)                               {}
void matrix_output_unselect_delay(uint8_t line, bool key_pressed)  {}

// LED layout configuration
led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, NO_LED, NO_LED, NO_LED },
    { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,     28, NO_LED,     14 },
    { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,     43,     13,     29 },
    { 45, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,     59,     44,     60 },
    { 61, NO_LED, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, NO_LED,     72,     73, NO_LED },
    { 74, 75, 76, NO_LED, NO_LED, 77, NO_LED, NO_LED, NO_LED, 78, 79, NO_LED, NO_LED, 80, 81, 82 },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
}, {
    // physical LED positions (x, y)
    {   0, 10 }, {  15, 10 }, {  30, 10 }, {  45, 10 }, {  60, 10 }, {  75, 10 }, {  90, 10 }, { 105, 10 }, { 120, 10 }, { 135, 10 }, { 150, 10 }, { 165, 10 }, { 180, 10 }, { 195, 10 }, { 208, 10 },
    {   0, 20 }, {  15, 20 }, {  30, 20 }, {  45, 20 }, {  60, 20 }, {  75, 20 }, {  90, 20 }, { 105, 20 }, { 120, 20 }, { 135, 20 }, { 150, 20 }, { 165, 20 }, { 180, 20 }, { 195, 20 }, { 208, 20 },
    {   0, 30 }, {  15, 30 }, {  30, 30 }, {  45, 30 }, {  60, 30 }, {  75, 30 }, {  90, 30 }, { 105, 30 }, { 120, 30 }, { 135, 30 }, { 150, 30 }, { 165, 30 }, { 180, 30 }, { 195, 30 }, { 208, 30 },
    {   0, 40 }, {   0, 40 }, {  15, 40 }, {  30, 40 }, {  45, 40 }, {  60, 40 }, {  75, 40 }, {  90, 40 }, { 105, 40 }, { 120, 40 }, { 135, 40 }, { 150, 40 }, { 165, 40 }, { 180, 40 }, { 195, 40 }, { 208, 40 },
    {   0, 50 },              {  15, 50 }, {  30, 50 }, {  45, 50 }, {  60, 50 }, {  75, 50 }, {  90, 50 }, { 105, 50 }, { 120, 50 }, { 135, 50 }, { 150, 50 }, { 165, 50 }, { 180, 50 },
    {   0, 60 }, {  15, 60 }, {  30, 60 },                           {  75, 60 },                            { 135, 60 }, { 150, 60 },              { 180, 60 }, { 195, 60 }, { 208, 60 },
    { 225, 65 }, { 225, 65 }, { 225, 65 }, { 225, 65 },
}, {
    // LED flags (1 = key backlight, 0 = underglow/indicator)
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
    1, 1, 1,       1,          1, 1,    1, 1, 1,
    0, 0, 0, 0,
} };

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    User_Led_Show();

    // capslock indicator
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(45, 96, 24, 0);
    }

    return false;
}

void notify_usb_device_state_change_user(enum usb_device_state usb_device_state) {
    // only track USB-OK status when in USB mode
    Usb_If_Ok_Led = (Keyboard_Info.Key_Mode == QMK_USB_MODE) && (usb_device_state == USB_DEVICE_STATE_CONFIGURED);
}

void housekeeping_task_user(void) {
    if (Keyboard_Reset) {
        Keyboard_Reset = false;
        User_Keyboard_Reset();
        return;
    }
    es_chibios_user_idle_loop_hook();
}

void board_init(void) {
    User_Keyboard_Init();
}

void keyboard_post_init_user(void) {
    User_Keyboard_Post_Init();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);

    // logo off by default
#if LOGO_LED_ENABLE
    Keyboard_Info.Logo_On_Off = LOGO_LED_OFF;
    Keyboard_Info.Logo_Mode = LOGO_OFF_MODE;
    Logo_Init();
#endif
}

// switch to BLE channel if not already on it
static inline void handle_ble_channel(bool pressed, bool *key_status, uint8_t channel, uint8_t spi_cmd) {
    if (pressed) {
        *key_status = true;
        Usb_Disconnect();
        if ((Keyboard_Info.Key_Mode != QMK_BLE_MODE) ||
            (Keyboard_Info.Ble_Channel != channel)) {
            Keyboard_Info.Key_Mode = QMK_BLE_MODE;
            Keyboard_Info.Ble_Channel = channel;
            Spi_Send_Commad(spi_cmd); // send SPI command to wireless module
            Save_Flash_Set();
            Led_Rf_Pair_Flg = true;
        }
    } else {
        *key_status = false;
    }
    Time_3s_Count = 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // any key activity resets the idle-sleep timer
    Usb_Change_Mode_Delay = 0;
    Usb_Change_Mode_Wakeup = false;

    // exit LED test mode on any key except the test navigation keys
    if (Test_Led) {
        if ((keycode != KC_SPC) &&
            (keycode != MO(2)) &&
            (keycode != MO(3)) &&
            (keycode != KC_LCTL)) {
            Test_Led = false;
        }
    }

    switch (keycode) {
        // 2.4 ghz mode
        case QMK_KB_MODE_2P4G:
            if (record->event.pressed) {
                Key_2p4g_Status = true;
                Usb_Disconnect();
                if (Keyboard_Info.Key_Mode != QMK_2P4G_MODE) {
                    Keyboard_Info.Key_Mode = QMK_2P4G_MODE;
                    Spi_Send_Commad(USER_SWITCH_2P4G_MODE);
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = true;
                }
            } else {
                Key_2p4g_Status = false;
            }
            Time_3s_Count = 0;
            return true;

        // ble channel 1
        case QMK_KB_MODE_BLE1:
            handle_ble_channel(record->event.pressed, &Key_Ble_1_Status, QMK_BLE_CHANNEL_1, USER_SWITCH_BLE_1_MODE);
            return true;

        // ble channel 2
        case QMK_KB_MODE_BLE2:
            handle_ble_channel(record->event.pressed, &Key_Ble_2_Status, QMK_BLE_CHANNEL_2, USER_SWITCH_BLE_2_MODE);
            return true;

        // ble channel 3
        case QMK_KB_MODE_BLE3:
            handle_ble_channel(record->event.pressed, &Key_Ble_3_Status, QMK_BLE_CHANNEL_3, USER_SWITCH_BLE_3_MODE);
            return true;

        // usb mode
        case QMK_KB_MODE_USB:
            if (record->event.pressed) {
                if (Keyboard_Info.Key_Mode != QMK_USB_MODE) {
                    Keyboard_Info.Key_Mode = QMK_USB_MODE;
                    Spi_Send_Commad(USER_SWITCH_USB_MODE);
                    es_restart_usb_driver();
                    Save_Flash_Set();
                    Led_Rf_Pair_Flg = false;
                }
            }
            return true;

        // utility keys

        // show batt percentage
        case QMK_BATT_NUM:
            if (record->event.pressed) {
                User_Key_Batt_Num_Show = true;
                User_Key_Batt_Count = 0;
            } else {
                User_Key_Batt_Num_Show = false;
                User_Key_Batt_Count = 0;
            }
            return true;

        // toggle win key lock
        case QMK_WIN_LOCK:
            if (!record->event.pressed) {
                if (Keyboard_Info.Mac_Win_Mode == INIT_MAC_MODE) {
                    // in mac mode: only allow locking (not unlocking)
                    if (Keyboard_Info.Win_Lock == INIT_WIN_LOCK) {
                        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                        Save_Flash_Set();
                    }
                } else {
                    // in Win mode: toggle lock and release any held GUI keys
                    if (Keyboard_Info.Win_Lock == INIT_WIN_NLOCK) {
                        Keyboard_Info.Win_Lock = INIT_WIN_LOCK;
                        unregister_code(KC_LGUI);
                        unregister_code(KC_RGUI);
                        unregister_code(KC_APP);
                    } else {
                        Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                    }
                    Save_Flash_Set();
                }
            }
            return true;

        // toggle between 6KRO and NKRO
        case QMK_KB_SIX_N_CH:
            if (record->event.pressed) {
                if (keymap_config.nkro) {
                    es_change_qmk_nkro_mode_disable();
                    Mac_Win_Point_Count = 3;
                } else {
                    es_change_qmk_nkro_mode_enable();
                    Led_Point_Count = 3;
                }
            }
            return true;

        // LED colour test cycle
        case QMK_TEST_COLOUR:
            if (!record->event.pressed) {
                if (!Test_Led) {
                    Test_Led = true;
                    Test_Colour = 0;
                }
            }
            return true;


        // colour during test
        case KC_SPC:
            if (!record->event.pressed && Test_Led) {
                if (++Test_Colour >= 4) {
                    Test_Colour = 0;
                }
            }
            return true;

        /* win/GUI key suppression when locked */

        // left GUI – suppress when Win-lock is active
        case KC_LGUI:
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
            return true;

        // right GUI – suppress when Win-lock is active
        case KC_RGUI:
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
            return true;

        // app key – suppress when Win-lock is active
        case KC_APP:
            if (Keyboard_Info.Win_Lock) {
                record->event.pressed = false;
            }
            return true;

        /* rgb matrix */

        // brightness increase – flash indicator at max
        case RGB_VAI:
            if (!record->event.pressed) {
                if (rgb_matrix_get_val() >= RGB_MATRIX_MAXIMUM_BRIGHTNESS) {
                    Led_Point_Count = 3;
                }
            }
            return true;

        // brightness decrease – flash indicator at min
        case RGB_VAD:
            if (!record->event.pressed) {
                if (rgb_matrix_get_val() <= 0) {
                    Led_Point_Count = 3;
                }
            }
            return true;


        // speed increase – flash indicator at max
        case RGB_SPI:
            if (!record->event.pressed) {
                if (rgb_matrix_get_speed() >= 255) {
                    Led_Point_Count = 3;
                }
            }
            return true;

        // speed decrease – flash indicator at min
        case RGB_SPD:
            if (!record->event.pressed) {
                if (rgb_matrix_get_speed() <= 0) {
                    Led_Point_Count = 3;
                }
            }
            return true;

        /* fn layer keys */

        case MO(2):
        case MO(3):
            Key_Fn_Status = record->event.pressed;
            return true;

        /* mac/win layout switching */

        // win and mac layout switch keys are flipped in default layout
        // default is mac layout

        // win layout
        case TO(1):
            if (!record->event.pressed) {
                if ((record->event.key.col == WIN_COL) && (record->event.key.row == WIN_ROL) &&
                    (Keyboard_Info.Mac_Win_Mode != INIT_WIN_MODE)) {
                    Keyboard_Info.Mac_Win_Mode = INIT_WIN_MODE;
                    Mac_Win_Point_Count = 1;
                    unregister_code(KC_LALT); unregister_code(KC_LGUI);
                    unregister_code(KC_RALT); unregister_code(KC_RGUI);
                    unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
            return true;

        // mac layout
        case TO(0):
            if (!record->event.pressed) {
                if ((record->event.key.col == MAC_COL) && (record->event.key.row == MAC_ROL) &&
                    (Keyboard_Info.Mac_Win_Mode != INIT_MAC_MODE)) {
                    Keyboard_Info.Mac_Win_Mode = INIT_MAC_MODE;
                    Keyboard_Info.Win_Lock = INIT_WIN_NLOCK;
                    Mac_Win_Point_Count = 3;
                    unregister_code(KC_LALT); unregister_code(KC_LGUI);
                    unregister_code(KC_RALT); unregister_code(KC_RGUI);
                    unregister_code(KC_APP);
                    Save_Flash_Set();
                }
            }
            return true;

        // reset
        case EE_CLR:
            if (record->event.pressed) {
                Key_Reset_Status = true;
                record->event.pressed = false; // prevent default EE_CLR action
            } else {
                Key_Reset_Status = false;
            }
            Func_Time_3s_Count = 0;
            return true;

#if LOGO_LED_ENABLE
        // logo LED controls

        // logo LED on/off toggle
        case LOGO_TOG:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off) {
                    Keyboard_Info.Logo_On_Off = LOGO_LED_ON;
                    if (Keyboard_Info.Logo_Brightness <= LOGO_MIN_BRIGHTNESS) {
                        Keyboard_Info.Logo_Brightness = LOGO_MAX_BRIGHTNESS;
                    }
                } else {
                    Keyboard_Info.Logo_On_Off = LOGO_LED_OFF;
                }
                Logo_Init();
                Save_Flash_Set();
            }
            return true;

        // logo LED mode - cycle forward
        case LOGO_MOD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off) {
                    return true;
                }

                if (Keyboard_Info.Logo_Mode < LOGO_OFF_MODE) {
                    Keyboard_Info.Logo_Mode++;
                } else {
                    Keyboard_Info.Logo_Mode = INIT_LOGO_MODE;
                }

                Logo_Init();
                Save_Flash_Set();
            }
            return true;

        // logo LED mode - cycle backward
        case LOGO_RMOD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off) {
                    return true;
                }

                if (Keyboard_Info.Logo_Mode > INIT_LOGO_MODE) {
                    Keyboard_Info.Logo_Mode--;
                } else {
                    Keyboard_Info.Logo_Mode = LOGO_OFF_MODE;
                }

                Logo_Init();
                Save_Flash_Set();
            }
            return true;

        // logo LED hue increase
        case LOGO_HUI:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off ||
                    (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE) ||
                    (Keyboard_Info.Logo_Mode == LOGO_WAVE_RGB_MODE) ||
                    (Keyboard_Info.Logo_Mode == LOGO_SPECTRUM_MODE)) {
                    return true;
                }

                if (Keyboard_Info.Logo_Colour < (LOGO_MAX_COLOUR - COLOUR_LEVEL)) {
                    Keyboard_Info.Logo_Colour += COLOUR_LEVEL;
                } else {
                    Keyboard_Info.Logo_Colour =
                        (Keyboard_Info.Logo_Colour + COLOUR_LEVEL) - LOGO_MAX_COLOUR;
                }

                Save_Flash_Set();
            }
            return true;

        // logo LED hue decrease
        case LOGO_HUD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off ||
                    (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE) ||
                    (Keyboard_Info.Logo_Mode == LOGO_WAVE_RGB_MODE) ||
                    (Keyboard_Info.Logo_Mode == LOGO_SPECTRUM_MODE)) {
                    return true;
                }

                if ((Keyboard_Info.Logo_Colour - COLOUR_LEVEL) > LOGO_MIN_COLOUR) {
                    Keyboard_Info.Logo_Colour -= COLOUR_LEVEL;
                } else {
                    Keyboard_Info.Logo_Colour =
                        (LOGO_MAX_COLOUR - COLOUR_LEVEL) + Keyboard_Info.Logo_Colour;
                }

                Save_Flash_Set();
            }
            return true;

        // logo LED saturation increase
        case LOGO_SAI:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off ||
                    (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                }

                if ((Keyboard_Info.Logo_Saturation - SATURATION_LEVEL) >
                    LOGO_MAX_SATURATION) {
                    Keyboard_Info.Logo_Saturation -= SATURATION_LEVEL;
                } else {
                    Keyboard_Info.Logo_Saturation = LOGO_MAX_SATURATION;
                }

                Save_Flash_Set();
            }
            return true;

        // logo LED saturation decrease
        case LOGO_SAD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off ||
                    (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                }

                if (Keyboard_Info.Logo_Saturation <
                    (LOGO_MIN_SATURATION - SATURATION_LEVEL)) {
                    Keyboard_Info.Logo_Saturation += SATURATION_LEVEL;
                } else {
                    Keyboard_Info.Logo_Saturation = LOGO_MIN_SATURATION;
                }

                Save_Flash_Set();
            }
            return true;

        // logo LED brightness increase
        case LOGO_VAI:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off ||
                    (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                }

                if (Keyboard_Info.Logo_Brightness <
                    (LOGO_MAX_BRIGHTNESS - BRIGHTNESS_LEVEL)) {
                    Keyboard_Info.Logo_Brightness += BRIGHTNESS_LEVEL;
                } else {
                    Keyboard_Info.Logo_Brightness = LOGO_MAX_BRIGHTNESS;
                    Led_Point_Count = 3;
                }

                Save_Flash_Set();
            }
            return true;

        // logo LED brightness decrease
        case LOGO_VAD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off ||
                    (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                }

                if ((Keyboard_Info.Logo_Brightness - BRIGHTNESS_LEVEL) >
                    LOGO_MIN_BRIGHTNESS) {
                    Keyboard_Info.Logo_Brightness -= BRIGHTNESS_LEVEL;
                } else {
                    Keyboard_Info.Logo_Brightness = LOGO_MIN_BRIGHTNESS;
                    Led_Point_Count = 3;
                }

                Save_Flash_Set();
            }
            return true;

        // logo LED animation speed increase
        case LOGO_SPI:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off ||
                    (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                }

                if (Keyboard_Info.Logo_Speed <
                    (LOGO_MAX_SPEED - SPEED_LEVEL)) {
                    Keyboard_Info.Logo_Speed += SPEED_LEVEL;
                } else {
                    Keyboard_Info.Logo_Speed = LOGO_MAX_SPEED;
                    Led_Point_Count = 3;
                }

                Save_Flash_Set();
            }
            return true;

        // logo LED animation speed decrease
        case LOGO_SPD:
            if (!record->event.pressed) {
                if (Keyboard_Info.Logo_On_Off ||
                    (Keyboard_Info.Logo_Mode == LOGO_OFF_MODE)) {
                    return true;
                }

                if ((Keyboard_Info.Logo_Speed - SPEED_LEVEL) >
                    LOGO_MIN_SPEED) {
                    Keyboard_Info.Logo_Speed -= SPEED_LEVEL;
                } else {
                    Keyboard_Info.Logo_Speed = LOGO_MIN_SPEED;
                    Led_Point_Count = 3;
                }

                Save_Flash_Set();
            }
            return true;
#endif // LOGO_LED_ENABLE

        default:
            return true; // pass all other keycodes through normally
    }
}
