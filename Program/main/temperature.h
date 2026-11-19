#pragma once

#include <stdint.h>

#define ADS1115_REG_CONV    0x00
#define ADS1115_REG_CONFIG  0x01
#define ADS1115_I2C_ADDR 0x48



#define R_ref 9950.0
#define VCC 3.296

int16_t temp_raw(void);
float temp_real(void);