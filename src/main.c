#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "def.h"
#include "nvs_flash.h"
#include "esp_http_server.h"

void app_main(void) {
    // Initialize your WiFi and other components here
    httpd_handle_t server = NULL;
    start_http_server(&server);  // Make sure the signature matches

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}