#include "lps22hb.h"

float lps22hb_pressure_read(uint8_t i2c_addr, I2C_HandleTypeDef *i2c)
{
	uint8_t press_out_h;
	uint8_t press_out_l;
	uint8_t press_out_xl;

	HAL_I2C_Mem_Read(i2c, i2c_addr, PRESS_OUT_H, sizeof(uint8_t), &press_out_h, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr, PRESS_OUT_L, sizeof(uint8_t), &press_out_l, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr, PRESS_OUT_XL, sizeof(uint8_t), &press_out_xl, sizeof(uint8_t), HAL_MAX_DELAY);

	uint32_t pressure_reg;
	pressure_reg = (uint32_t)press_out_h << 16 | (uint16_t)press_out_l << 8 | press_out_xl;

	uint16_t scalling_factor = 4096;

	float pressure = (float)pressure_reg/(float)scalling_factor;

	uint8_t rpds_l;
	uint8_t rpds_h;

	return pressure;
}
float lps22hb_temp_read(uint8_t i2c_addr, I2C_HandleTypeDef *i2c)
{
	uint8_t temp_h;
	uint8_t temp_l;

	HAL_I2C_Mem_Read(i2c, i2c_addr, TEMP_OUT_H, sizeof(uint8_t), &temp_h, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr, TEMP_OUT_L, sizeof(uint8_t), &temp_l, sizeof(uint8_t), HAL_MAX_DELAY);

	uint16_t temp_reg = (uint16_t)temp_h << 8 | temp_l;

	return temp_reg;
}
