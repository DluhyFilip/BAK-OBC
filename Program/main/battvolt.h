#pragma once

#include <stdint.h>

#define ADS1115_REG_CONV    0x00
#define ADS1115_REG_CONFIG  0x01

#define ADS1115_I2C_ADDR 0x48

int16_t battvolt_raw(void);
float battvolt_real(void);