#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <driver/gpio.h>

// DEVICE CONFIGURATION
#define NUMBER_OF_LINES     2               // Number of lines use to write on the LCD screen
#define DEVICE_CHAR_WIDTH   20              // The maxmimum character width of the screen
#define MAXIMUM_LINE_HEIGHT 4               // The maximum character length of the screen

// DEVICE AUTOMATIC SETTINGS
#if NUMBER_OF_LINES <= 2
#define DDRAM_ADDRESSES {0x00, 0x40}
#elif NUMBER_OF_LINES > 2
#define DDRAM_ADDRESSES {0x00, 0x40, 0x14, 0x54}
#endif

// PIN CONFIGURATION
#define RS_PIN              GPIO_NUM_26     // Register Select 1 = Data | 0 = Command
#define ENABLE_PIN          GPIO_NUM_25     // Setting to 1 signals the lcd to read the databuses
#define DB4_PIN             GPIO_NUM_17     // Databus 4
#define DB5_PIN             GPIO_NUM_16     // Databus 5
#define DB6_PIN             GPIO_NUM_27     // Databus 6
#define DB7_PIN             GPIO_NUM_14     // Databus 7

// OWN COMMAND
#define ENABLE_READ() (gpio_set_level(ENABLE_PIN, 1))   // Signals the LCD to read the databusses
#define DISABLE_READ() (gpio_set_level(ENABLE_PIN, 0))  // Signals the LCD to stop reading the databusses
#define WRITE_DATA_BIT() (gpio_set_level(RS_PIN, 1))    // Signals the LCD that this is data to be shown on the LCD
#define WRITE_COMMAND_BIT() (gpio_set_level(RS_PIN, 0)) // Signlas the LCD that this is a command to be performed

// DEVICE COMMANDS
#define CLEAR_DISPLAY           0x01            // Clears display and returns cursor to initial position
#define RETURN_HOME             0x02            // Returns cursor to initial position

#define ENTRY_MODE_SET          0x04            // Set direction of cursor and display shift
#define CURSOR_DIR_RIGHT        0x02            // Must be used together with ENTRY_MODE_SET
#define CURSOR_DIR_LEFT         0               // Must be used together with ENTRY_MODE_SET
#define ENALBE_DISPLAY_SHIFT    0x01            // Must be used together with ENTRY_MODE_SET
#define DISABLE_DISPLAY_SHIFT   0               // Must be used together with ENTRY_MODE_SET

#define DISPLAY_CONTROL         0x08            // Set current state of the display
#define DISPLAY_ON              0x04            // Must be used together with DISPLAY_CONTROL
#define DISPLAY_OFF             0               // Must be used together with DISPLAY_CONTROL
#define SHOW_CURSOR             0x02            // Must be used together with DISPLAY_CONTROL
#define HIDE_CURSOR             0               // Must be used together with DISPLAY_CONTROL
#define BLINK_CURSOR_POS        0x01            // Must be used together with DISPLAY_CONTROL
#define STOP_BLINK_CURSOR_POS   0               // Must be used together with DISPLAY_CONTROL

#define CURSOR_DISPLAY_SHIFT    0x10            // Moves cursor or shift display without changing DDRAM content
#define DISPLAY_SHIFT           0x08            // Must be used together with CURSOR_DISPLAY_SHIFT
#define CURSOR_SHIFT            0               // Must be used together with CURSOR_DISPLAY_SHIFT
#define SHIFT_RIGHT             0x04            // Must be used together with CURSOR_DISPLAY_SHIFT
#define SHIFT_LEFT              0               // Must be used together with CURSOR_DISPLAY_SHIFT

#define FUNCTION_SET            0x20            // Sets interface data length, number of display lines and character font.
#define DATA_LENGTH_8_BIT       0x10            // Must be used together with FUNCTION_SET
#define DATA_LENGTH_4_BIT       0               // Must be used together with FUNCTION_SET
#define TWO_LINES               0x08            // Must be used together with FUNCTION_SET
#define ONE_LINE                0               // Must be used together with FUNCTION_SET
#define FONT_5X10               0x04            // Must be used together with FUNCTION_SET
#define FONT_5X8                0               // Must be used together with FUNCTION_SET

#define SET_DDRAM_ADDRESS       0x80            // Set ddram address

void lcd_clear_display();
void lcd_write_string(const char *string);
void lcd_init();

#endif