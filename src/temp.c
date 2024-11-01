#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dht.h"  // Include the DHT library
#define DHT_GPIO 12       // GPIO pin where the DHT sensor is connected
#define DHT_TYPE DHT_TYPE_DHT11  // Specify the DHT sensor type

static float temperature = 0.0;

// Function to read temperature from the DHT sensor
esp_err_t read_temperature(void) {
    int16_t humidity_int = 0;
    int16_t temperature_int = 0;

    // Read the DHT sensor data
    esp_err_t result = dht_read_data(DHT_TYPE, DHT_GPIO, &humidity_int, &temperature_int);
    if (result == ESP_OK) {
        temperature = temperature_int / 10.0;  // Convert to float
    }
    return result;
}

// Function to get the current temperature
float get_temperature(void) {
    return temperature;
}