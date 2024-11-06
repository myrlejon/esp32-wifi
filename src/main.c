#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "def.h"
#include "nvs_flash.h"
#include "esp_http_server.h"
#include "u8g2.h"

void app_main(void) {
    u8g2_t *u8gt;
    SensorData data;

    ssd1309_init(u8gt);

    xTaskCreate(
        temperatureDisplayTask,  // Task function
        "Temperature Display Task", // Task name
        4096,                   // Stack size in words (2048 is generally safe for most tasks)
        NULL,                   // Parameter to pass to task (if needed)
        5,                      // Task priority
        NULL                    // Task handle (can be NULL if you don't need it)
    );

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Idle loop or placeholder delay
    }
}


// Task function to read temperature and update the display
void temperatureDisplayTask(void *pvParameters) {
    while (1) {
        SensorData data = read_temperature();   // Get the temperature data
        ssd1309_update(data);                      // Update the display
        vTaskDelay(10000 / portTICK_PERIOD_MS);  // Delay to set the update interval
    }
}