#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_PIN 18

extern QueueHandle_t button_queue;

void button_init(void);

#endif