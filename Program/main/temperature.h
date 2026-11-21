#pragma once

#include <stdint.h>
#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <math.h>

#define ADS1115_REG_CONV    0x00
#define ADS1115_REG_CONFIG  0x01
#define ADS1115_I2C_ADDR 0x48



#define R_ref 9950.0
#define VCC 3.296

int16_t temp_raw(void);
float temp_real(void);