#include "def.h"
#include "nvs_flash.h"

void app_main(void) {
    // Initialize NVS
    ESP_ERROR_CHECK(nvs_flash_init());

    // Start the WiFi Access Point
    wifi_init_softap();
    start_webserver();
}
