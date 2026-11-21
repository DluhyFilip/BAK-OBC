#include "display.h"

u8g2_t u8g2;

void display_init(void) {

  u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
  u8g2_esp32_hal.bus.i2c.sda = I2C_MASTER_SDA_IO;
  u8g2_esp32_hal.bus.i2c.scl = I2C_MASTER_SCL_IO;
  u8g2_esp32_hal_init(u8g2_esp32_hal);

  u8g2_Setup_sh1106_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8g2_esp32_i2c_byte_cb, u8g2_esp32_gpio_and_delay_cb);

  u8x8_SetI2CAddress(&u8g2.u8x8, 0x78);
  u8g2_InitDisplay(&u8g2);

  u8g2_SetPowerSave(&u8g2, 0);
  u8g2_ClearBuffer(&u8g2);

  u8g2_SetFont(&u8g2, u8g2_font_6x12_te);

  u8g2_DrawXBM(&u8g2, 0, 0, 128, 64, uvod);
  
  u8g2_SendBuffer(&u8g2);
  vTaskDelay(pdMS_TO_TICKS(2000));

  u8g2_ClearBuffer(&u8g2);
}

void speed(void){
  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_6x12_te);

  //u8g2_DrawXBM(&u8g2, 0, 0, 128, 64, test);
  u8g2_DrawUTF8(&u8g2, 0, 32, "Rychlost:");
  u8g2_SendBuffer(&u8g2);

  //vTaskDelay(pdMS_TO_TICKS(50));
}

void rpm(void){
  int meas = rpm_meas();
  char text_buffer1[32];
  snprintf(text_buffer1, sizeof(text_buffer1), "Otáčky motoru: %d", meas);


  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_6x12_te);
  u8g2_DrawUTF8(&u8g2, 0, 32, text_buffer1);
  u8g2_SendBuffer(&u8g2);

  //vTaskDelay(pdMS_TO_TICKS(50));
}

void engtemp(void){
  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_6x12_te);
  u8g2_DrawUTF8(&u8g2, 0, 32, "Teplota motoru:");
  u8g2_SendBuffer(&u8g2);

  //vTaskDelay(pdMS_TO_TICKS(50));
}

void battvolt(void){ 
  float meas = battvolt_real();
  char text_buffer1[32];
  snprintf(text_buffer1, sizeof(text_buffer1), "Napětí v síti: %.2f V", meas);


  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_6x12_te);
  u8g2_DrawUTF8(&u8g2, 0, 32, text_buffer1);
  u8g2_SendBuffer(&u8g2);

  //vTaskDelay(pdMS_TO_TICKS(50));
}

void consump(void){
  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_6x12_te);
  u8g2_DrawUTF8(&u8g2, 0, 32, "Spotřeba paliva:");
  u8g2_SendBuffer(&u8g2);

  //vTaskDelay(pdMS_TO_TICKS(50));
}

void fuelgaug(void){
  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_6x12_te);
  u8g2_DrawUTF8(&u8g2, 0, 32, "V nádrži zbývá:");
  u8g2_SendBuffer(&u8g2);

  //vTaskDelay(pdMS_TO_TICKS(50));
}

void temp(void){
  float temp = temp_real();
  char text_buffer1[32];
  char text_buffer2[48];
  

  if(temp < 5){
    snprintf(text_buffer1, sizeof(text_buffer1), "Teplota: %.1f °C", temp);
    snprintf(text_buffer2, sizeof(text_buffer2), "Je méně, než 5 °C");
  }

  if(temp > 5 && temp < 20){
    snprintf(text_buffer1, sizeof(text_buffer1), "Teplota: %.1f °C", temp);
    snprintf(text_buffer2, sizeof(text_buffer2), "Je 5-20 °C");
  }

  if(temp > 20){
    snprintf(text_buffer1, sizeof(text_buffer1), "Teplota: %.1f °C", temp);
    snprintf(text_buffer2, sizeof(text_buffer2), "Je více, než 20 °C");
  } 

  u8g2_ClearBuffer(&u8g2);
  u8g2_SetFont(&u8g2, u8g2_font_6x12_te);
  u8g2_DrawUTF8(&u8g2, 0, 32, text_buffer1);
  u8g2_DrawUTF8(&u8g2, 0, 47, text_buffer2);
  
  u8g2_SendBuffer(&u8g2);

  //vTaskDelay(pdMS_TO_TICKS(50));

}

