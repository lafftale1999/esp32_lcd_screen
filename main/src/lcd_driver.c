#include "include/lcd_driver.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static void out_nibble(const char half_byte) {
    if(1 & half_byte) gpio_set_level(DB4_PIN, 1);
    else gpio_set_level(DB4_PIN, 0);

    if(2 & half_byte) gpio_set_level(DB5_PIN, 1);
    else gpio_set_level(DB5_PIN, 0);

    if(4 & half_byte) gpio_set_level(DB6_PIN, 1);
    else gpio_set_level(DB6_PIN, 0);

    if(8 & half_byte) gpio_set_level(DB7_PIN, 1);
    else gpio_set_level(DB7_PIN, 0);

    ENABLE_READ();
    vTaskDelay(pdMS_TO_TICKS(1));
    DISABLE_READ();
}

static void send_command(const char cmd) {
    WRITE_COMMAND_BIT();
    out_nibble(cmd >> 4);
    out_nibble(cmd);
}

static void send_data(const char data) {
    WRITE_DATA_BIT();
    out_nibble(data >> 4);
    out_nibble(data);
}

void lcd_clear_display() {
    send_command(CLEAR_DISPLAY);
    vTaskDelay(pdMS_TO_TICKS(5));
}

void lcd_write_string(const char *string) {
    int8_t line_addresses[] = DDRAM_ADDRESSES;
    int8_t char_index = 0;
    int8_t line_index = 0;

    while(*string != '\0' && line_index < NUMBER_OF_LINES) {
        if (char_index == DEVICE_CHAR_WIDTH || *string == '\n') {
            line_index++;
            char_index = 0;

            if(line_index >= NUMBER_OF_LINES) break;
            
            send_command(SET_DDRAM_ADDRESS | line_addresses[line_index]);

            if(*string == '\n') string++;
        }

        if(*string != '\0' && *string != '\n') {
            send_data(*string++);
            char_index++;
        }
    }
}

void lcd_init() {
    vTaskDelay(pdMS_TO_TICKS(50));

    gpio_config_t gpio = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1 << DB4_PIN) | (1ULL << DB5_PIN) | (1ULL << DB6_PIN) | (1ULL << DB7_PIN) | (1ULL << RS_PIN) | (1ULL << ENABLE_PIN),
        .intr_type = GPIO_INTR_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE
    };
    gpio_config(&gpio);
    
    gpio_set_level(DB4_PIN,0);
    gpio_set_level(DB5_PIN,0);
    gpio_set_level(DB6_PIN,0);
    gpio_set_level(DB7_PIN,0);
    gpio_set_level(RS_PIN,0);
    gpio_set_level(ENABLE_PIN,0);

    out_nibble(0x03);
    vTaskDelay(pdMS_TO_TICKS(1));
    out_nibble(0x03);
    vTaskDelay(pdMS_TO_TICKS(1));
    out_nibble(0x03);
    vTaskDelay(pdMS_TO_TICKS(1));

    out_nibble(0x02);
    send_command(FUNCTION_SET | TWO_LINES | FONT_5X8);
    send_command(DISPLAY_CONTROL | DISPLAY_ON | SHOW_CURSOR);
    clear_display();
    send_command(ENTRY_MODE_SET | CURSOR_DIR_RIGHT);
}