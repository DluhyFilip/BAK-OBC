#ifndef DISPLAY_H
#define DISPLAY_H

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