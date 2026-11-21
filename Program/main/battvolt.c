#include "battvolt.h"


int16_t battvolt_raw(void){

    uint8_t config[3] = {ADS1115_REG_CONFIG,
                        0xD3,
                        0x43};

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ADS1115_I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, config, sizeof(config), true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_1, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    vTaskDelay(pdMS_TO_TICKS(15));

    uint8_t reg = ADS1115_REG_CONV;
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,(ADS1115_I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_1, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    uint8_t data[2] = {0};
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,(ADS1115_I2C_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, sizeof(data),I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_1, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    return(int16_t)((data[0]<<8)|(data[1]));
}

float battvolt_real(){
    int16_t raw = battvolt_raw();

    float real = 0.000699265573086186 * raw + 0.00539593910809622;

    return real;
}