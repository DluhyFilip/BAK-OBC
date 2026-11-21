#include "rpm.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "hal/gpio_types.h"


static volatile int64_t time = 0;
static volatile int64_t prev_time = 0;

gpio_config_t gpio_intr = {
  .pin_bit_mask = 1ULL<<14,
  .mode = GPIO_MODE_INPUT,
  .pull_up_en = GPIO_PULLUP_ENABLE,
  .pull_down_en = GPIO_PULLDOWN_DISABLE,
  .intr_type = GPIO_INTR_NEGEDGE,
};

void rpm_init(void){
    gpio_config(&gpio_intr);
    gpio_isr_handler_add(GPIO_NUM_14, gpio_isr_t isr_handler, void *args)
}

int rpm_meas(void){



    return 0;
}

