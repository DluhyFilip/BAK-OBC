#include "temperature.h"

#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <math.h>

static int16_t temp_raw(void){
    uint8_t config[3] = {ADS1115_REG_CONFIG, 0xC3, 0x83};

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ADS1115_I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, config, sizeof(config), true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    vTaskDelay(pdMS_TO_TICKS(15));

    uint8_t reg = ADS1115_REG_CONV;
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ADS1115_I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    uint8_t data[2] = {0};
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ADS1115_I2C_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 2, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    return (int16_t)((data[0] << 8) | data[1]);
}

float temp_real(){
    int16_t raw = temp_raw();

    float voltage = raw * 0.000125f;

    if (voltage <= 0.05f || voltage >= (VCC_VOLTAGE - 0.05f)) {
        return -999.0f;
    }

    float r_term = R_PULLUP * (voltage / (VCC_VOLTAGE - voltage));

    float real;

    real = r_term/TERM_NOM_R;
    real = logf(real);
    real /= TERM_BETA;
    real += 1.0f / (TERM_NOM_TEMP + 273.15f);
    real = 1.0f / real;
    real -= 273.15f;

    return real;
}