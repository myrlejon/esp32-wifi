#include "esp_err.h"
#include "esp_http_server.h"
#include "u8g2.h"

typedef struct {
    float temp;
    float humidity;
} SensorData;

void wifi_init_softap(void);
void start_webserver(void);

esp_err_t ssd1309_init(u8g2_t *u8g2);
esp_err_t ssd1309_update(SensorData data);

void deepsleep(void);

SensorData read_temperature(void);
float get_temperature(void);

void temperatureDisplayTask(void *pvParameters);