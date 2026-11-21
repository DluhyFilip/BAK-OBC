#ifndef DISPLAY_H
#define DISPLAY_H

#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "temperature.h"
#include "battvolt.h"
#include "bitmaps.h"
#include "rpm.h"

#include <u8g2.h>
#include "u8g2_esp32_hal.h"


#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21

void display_init(void);
void speed(void);
void rpm(void);
void engtemp(void);
void battvolt(void);
void consump(void);
void fuelgaug(void);
void temp(void);

#endif