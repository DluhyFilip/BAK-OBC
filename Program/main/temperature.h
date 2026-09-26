#pragma once

#include <esp_err.h>

#define I2C_NUM             I2C_NUM_1

#define I2C_SDA_PIN         21
#define I2C_SCL_PIN         22
#define I2C_FREQ_HZ         100000

#define ADS1115_REG_CONV    0x00
#define ADS1115_REG_CONFIG  0x01

#define ADS1115_I2C_ADDR 0x48

#define VCC_VOLTAGE     3.3f
#define R_PULLUP        10000.0f
#define TERM_NOM_R      10000.0f
#define TERM_NOM_TEMP   25.0f
#define TERM_BETA       3950.0f

static int16_t temp_raw(void);
float temp_real(void);