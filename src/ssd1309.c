#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "u8g2.h"
#include "u8g2_esp32_hal.h" // Include the ESP32 HAL for u8g2
#include "esp_log.h"

#define PIN_SCK   18  // Clock pin
#define PIN_MOSI  23  // Data pin
#define PIN_CS    5   // Chip select
#define PIN_RST   17  // Reset pin
#define PIN_DC    16  // Data/Command pin

static const char *TAG = "SSD1309";

esp_err_t ssd1309_init(u8g2_t *u8g2) {
    esp_err_t err = ESP_OK;
    u8g2_esp32_hal_t u8g2_esp32_hal = {
        .dc   = PIN_DC,
        .reset  = PIN_RST,
        .bus.spi.cs   = PIN_CS,
        .bus.spi.clk  = PIN_SCK,
        .bus.spi.mosi = PIN_MOSI,
        // .miso = -1   // Not used
    };

    ESP_LOGI(TAG, "Running u8g2 init.");

    u8g2_esp32_hal_init(u8g2_esp32_hal);

    // Initialize u8g2 for SPI
    u8g2_Setup_ssd1309_128x64_noname0_f(u8g2, U8G2_R0, u8g2_esp32_spi_byte_cb, u8g2_esp32_gpio_and_delay_cb);
    
    // Initialize the display
    u8g2_InitDisplay(u8g2);
    u8g2_SetPowerSave(u8g2, 0); // Wake up display

    return ESP_OK;
}

void ssd1309_reset(void) {
    gpio_set_direction(PIN_RST, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_RST, 0);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    gpio_set_level(PIN_RST, 1);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void ssd1309_run(float temp) {
    ESP_LOGI(TAG, "Initializing SSD1309...");

    // Initialize the display
    u8g2_t u8g2;
    ssd1309_reset();
    ssd1309_init(&u8g2);

    // Clear the display
    u8g2_ClearBuffer(&u8g2);

    // Draw text
    u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);

    // Konvertera temp till string och printa
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "Temp: %.2f", temp);
    u8g2_DrawStr(&u8g2, 10, 45, buffer);
    //


    // Send the buffer to the display
    u8g2_SendBuffer(&u8g2);
    
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
