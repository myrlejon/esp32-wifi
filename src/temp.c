#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Adafruit_Sensor.h>
#include "DHT.h"  // Include DHT sensor library

// DHT Sensor settings
#define DHTPIN 12        // Pin where DHT11 is connected
#define DHTTYPE DHT11    // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);  // Initialize the DHT sensor

// Variables to hold temperature and humidity data
float temperature = 0.0;
float humidity = 0.0;

// Task to read from the DHT11 sensor
void read_dht11(void *pvParameter) {
    dht.begin();  // Initialize the sensor

    while (1) {
        humidity = dht.readHumidity();
        temperature = dht.readTemperature();

        // Check if readings failed and try again
        if (isnan(humidity) || isnan(temperature)) {
            printf("Failed to read from DHT sensor!\n");
        } else {
            printf("Humidity: %.1f%% Temp: %.1f°C\n", humidity, temperature);
        }

        vTaskDelay(2000 / portTICK_PERIOD_MS);  // Read every 2 seconds
    }
}

// Web server to display temperature and humidity
#include <esp_http_server.h>

// Handler for serving the temperature and humidity webpage
esp_err_t root_get_handler(httpd_req_t *req) {
    char response[100];
    snprintf(response, sizeof(response),
             "<html><body><h1>Temperature: %.1f°C<br>Humidity: %.1f%%</h1></body></html>",
             temperature, humidity);

    httpd_resp_send(req, response, strlen(response));
    return ESP_OK;
}

// URI handler for the root page
httpd_uri_t root = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = root_get_handler,
    .user_ctx  = NULL
};

// Function to start the web server
void start_webserver(void) {
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &root);
    }
}

// Main application
void app_main(void) {
    // Start the DHT11 reading task
    xTaskCreate(&read_dht11, "read_dht11", 2048, NULL, 5, NULL);

    // Start the web server
    start_webserver();
}
