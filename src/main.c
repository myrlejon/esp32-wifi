#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "def.h"
#include "nvs_flash.h"
#include "esp_http_server.h"

void app_main(void) {
    // httpd_handle_t server = NULL;
    // start_http_server(&server);
    // nvs_flash_init(); 

    // wifi_init_softap();

    // start_webserver();

    float temp = 0.0;

    temp = read_temperature();
    // temp = get_temperature();

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ssd1309_run(temp);

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}