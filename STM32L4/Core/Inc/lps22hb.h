#include "stm32l4xx_hal.h"

#define INTERRUPT_CFG 0x0B
#define THS_P_L 0x0C
#define THS_P_H 0x0D
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x10
#define CTRL_REG2 0x11
#define CTRL_REG3 0x12
#define FIFO_CTRL 0x14
#define REF_P_XL 0x15
#define REF_P_L 0x16
#define REF_P_H 0x17
#define RPDS_L 0x18
#define RPDS_H 0x19
#define RES_CONF 0x1A
#define INT_SOURCE 0x25
#define FIFO_STATUS 0x26
#define STATUS 0x27
#define PRESS_OUT_XL 0x28
#define PRESS_OUT_L 0x29
#define PRESS_OUT_H 0x2A
#define TEMP_OUT_L 0x2B
#define TEMP_OUT_H 0x2C
#define LPFP_RES 0x33

uint8_t init(uint8_t i2c_addr, I2C_HandleTypeDef *i2c);
float lps22hb_pressure_read(uint8_t i2c_addr, I2C_HandleTypeDef *i2c);
float lps22hb_temp_read(uint8_t i2c_addr, I2C_HandleTypeDef *i2c);
