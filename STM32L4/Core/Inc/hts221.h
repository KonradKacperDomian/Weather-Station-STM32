#include "stm32l4xx_hal.h"

#define HIGH_PRESSION 0b111111

#define WHO_AM_I 0x0F
#define AV_CONF 0x10
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define STATUS_REG 0x27
#define HUMIDITY_OUT_L 0x28
#define HUMIDITY_OUT_H 0x29
#define TEMP_OUT_L 0x2A
#define TEMP_OUT_H 0x2B
#define CALIB 0x30

#define DEVICE_IDENTIFER 0xBC

uint8_t hts221_init(uint8_t i2c_addr, I2C_HandleTypeDef *i2c);
float hts221_humidity_read(uint8_t i2c_addr, I2C_HandleTypeDef *i2c);
float hts221_temp_read(uint8_t i2c_addr, I2C_HandleTypeDef *i2c);
