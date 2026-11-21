#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_PIN 18

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_attr.h>

extern QueueHandle_t button_queue;

void button_init(void);

#endif