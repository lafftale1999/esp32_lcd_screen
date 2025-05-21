#include <stdio.h>
#include "include/lcd_driver.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

static const char *MAIN_TAG = "MAIN";

void app_main(void)
{
    lcd_init();

    while(1) {
        ESP_LOGI(MAIN_TAG, "Logging - before writing string");
        lcd_write_string("Hello World!");
        ESP_LOGI(MAIN_TAG, "Logging - after writing string");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}