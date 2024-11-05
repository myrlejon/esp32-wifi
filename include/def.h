#include "esp_err.h"
#include "esp_http_server.h"

typedef struct {
    float temp;
    float humidity;
} SensorData;

void wifi_init_softap(void);
void start_webserver(void);
void ssd1309_run(SensorData data);
void deepsleep(void);

SensorData read_temperature(void);
float get_temperature(void);