#include <stdio.h>
#include "include/lcd_driver.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void)
{
    lcd_init();

    while(1) {
        lcd_write_string("Hello World!");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}