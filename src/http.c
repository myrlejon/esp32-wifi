#include <stdio.h>
#include "esp_http_server.h"
// #include "components/dht/dht.h"
#include "def.h"
#include <esp_http_server.h>

// Function to serve the HTML page
esp_err_t root_get_handler(httpd_req_t *req) {
    const char *response = "<html><body><h1>Hello from ESP32!</h1></body></html>";
    httpd_resp_send(req, response, strlen(response));
    return ESP_OK;
}

// Register URI handlers
httpd_uri_t root = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = root_get_handler,
    .user_ctx  = NULL
};

void start_webserver(void) {
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    
    // Start the HTTP server
    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &root);
    }
}
