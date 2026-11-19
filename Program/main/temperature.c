#include "temperature.h"

#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <math.h>

 int16_t temp_raw(void){
    uint8_t config[3] = {ADS1115_REG_CONFIG, // Pointer Byte
                        0xC3, //MSB byte
                        0x83 //LSB byte
                        }; 

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
    i2c_master_write_byte(cmd, (ADS1115_I2C_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_1, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    uint8_t data[2] = {0};
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (ADS1115_I2C_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 2, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_1, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    return (int16_t)((data[0] << 8) | data[1]);
}


//Steinhart-Hart
float temp_real(){
    int16_t raw = temp_raw();

    float A = 1.129e-3;
    float B = 2.341e-4;
    float C = 8.767e-8;
    
    float U = (4.096f / 32768.0f) * raw;
    float R = (U * R_ref) / (VCC-U) ;

    float real = (1.0 / (A + (B * log(R)) + (C * log(R) * log(R) * log(R))))-273.15; 

    return real;
}