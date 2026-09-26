#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_attr.h>

#include "button.h"

QueueHandle_t button_queue = NULL;

gpio_config_t io_config = {
  .pin_bit_mask = 1ULL<<18,
  .mode = GPIO_MODE_INPUT,
  .pull_up_en = GPIO_PULLUP_ENABLE,
  .pull_down_en = GPIO_PULLDOWN_DISABLE,
  .intr_type = GPIO_INTR_NEGEDGE,
};

static void IRAM_ATTR gpio_isr_handler(void* arg){
  uint32_t gpio_num = (uint32_t) arg; 
  xQueueSendFromISR(button_queue, &gpio_num, NULL);
}

void button_init(void){
  button_queue = xQueueCreate(10, sizeof(uint32_t));

  gpio_config(&io_config);

  gpio_install_isr_service(0);
  gpio_isr_handler_add(BUTTON_PIN, gpio_isr_handler, (void*) BUTTON_PIN);
}