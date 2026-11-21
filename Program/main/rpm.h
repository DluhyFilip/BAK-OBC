#ifndef RPMH
#define RPMH

#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "esp_timer.h"

int rpm_meas(void);
void rpm_init(void);

#endif