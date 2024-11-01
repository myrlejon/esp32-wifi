#ifndef WIFI_H
#define WIFI_H

#include "esp_err.h"
#include "esp_http_server.h"

void wifi_init_softap(void);
void start_webserver(void);
void ssd1309_run(float temp);

esp_err_t read_temperature(void);
float get_temperature(void);

#endif // WIFI_H
