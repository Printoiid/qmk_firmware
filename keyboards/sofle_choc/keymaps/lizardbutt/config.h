#pragma once

// USB-C connects on this side
#define MASTER_LEFT

// Split Settings
#define SPLIT_USB_DETECT
#define SPLIT_TRANSPORT_MIRROR

// RGB Configuration
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#define RGB_DI_PIN D3
#define RGB_MATRIX_SPLIT { 29, 29 } // changed from RGBLED_SPLIT
#define DRIVER_LED_TOTAL 58

// Layer states for OLEDs
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_WPM_ENABLE

// OLED Screens
#define MINUTE_TO_MS              10000  // 10 seconds
#define OLED_SCREENSAVER_TIMEOUT  1 * MINUTE_TO_MS  // 10 Seconds of no activity, turn on the screensaver
#define OLED_TIMEOUT              1 * MINUTE_TO_MS  // 20 Seconds of no activity, turn off the OLED
#define OLED_BRIGHTNESS           120

// Left Side Encoder
#define ENCODERS_A_PINS      { F5 }
#define ENCODERS_B_PINS      { F4 }
#define ENCODER_RESOLUTIONS  { 4 }

// Right Side Encoder
#define ENCODERS_PING_A_RIGHT      { F4 }
#define ENCODERS_PINS_B_RIGHT      { F5 }
#define ENCODER_RESOLUTIONS_RIGHT  { 4 }
