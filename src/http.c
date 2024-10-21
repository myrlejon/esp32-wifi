#include <stdio.h>
#include "esp_http_server.h"
#include "components/dht/dht.h"
#include "def.h"

// Function to handle the HTTP request for temperature
esp_err_t get_temperature_handler(httpd_req_t *req) {
    // Read the temperature before responding
    read_temperature();
    
    float temperature = get_temperature();
    
    // Prepare the response
    char response[50];
    snprintf(response, sizeof(response), "{\"temperature\": %.1f}", temperature);
    
    // Set response type
    httpd_resp_set_type(req, "application/json");
    // Send the response
    httpd_resp_send(req, response, strlen(response));
    
    return ESP_OK;
}

// Set up the HTTP server and routes
void start_http_server(httpd_handle_t *server) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    // Start the HTTP server
    if (httpd_start(server, &config) == ESP_OK) {
        httpd_uri_t uri_temperature = {
            .uri       = "/temperature",
            .method    = HTTP_GET,
            .handler   = get_temperature_handler,
            .user_ctx  = NULL
        };
        // Register the temperature URI
        httpd_register_uri_handler(*server, &uri_temperature);
    }
}
