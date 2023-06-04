#include "hts221.h"

uint8_t hts221_init(uint8_t i2c_addr, I2C_HandleTypeDef *i2c)
{

	uint8_t temp = 0;

	HAL_I2C_Mem_Read(i2c, i2c_addr+1, WHO_AM_I, sizeof(uint8_t), &temp, sizeof(uint8_t), HAL_MAX_DELAY);

	if(temp != DEVICE_IDENTIFER)
		return 1;

	uint8_t data = HIGH_PRESSION;
	HAL_I2C_Mem_Write(i2c, i2c_addr, AV_CONF, sizeof(uint8_t), (uint8_t*)&data, sizeof(uint8_t), HAL_MAX_DELAY);
	data = 0b10000001;
	HAL_I2C_Mem_Write(i2c, i2c_addr, CTRL_REG1, sizeof(uint8_t), (uint8_t*)&data, sizeof(uint8_t), HAL_MAX_DELAY);
	data = 0b10000000;
	HAL_I2C_Mem_Write(i2c, i2c_addr, CTRL_REG2, sizeof(uint8_t), (uint8_t*)&data, sizeof(uint8_t), HAL_MAX_DELAY);

	HAL_I2C_Mem_Read(i2c, i2c_addr+1, CTRL_REG1, sizeof(uint8_t), &temp, sizeof(uint8_t), HAL_MAX_DELAY);

	return 0; //corrent init
}

float hts221_temp_read(uint8_t i2c_addr, I2C_HandleTypeDef *i2c)
{
	uint8_t temp_l = 0;
	uint8_t temp_h = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, TEMP_OUT_L, sizeof(uint8_t), &temp_l, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, TEMP_OUT_H, sizeof(uint8_t), &temp_h, sizeof(uint8_t), HAL_MAX_DELAY);

	int16_t T_OUT = ((int16_t)temp_h << 8) | temp_l;

	uint8_t T0_degC_x8 = 0;
	uint8_t T1_degC_x8 = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x32, sizeof(uint8_t), &T0_degC_x8, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x33, sizeof(uint8_t), &T1_degC_x8, sizeof(uint8_t), HAL_MAX_DELAY);

	uint8_t T0_degC = T0_degC_x8/8;
	uint8_t T1_degC = T1_degC_x8/8;

	uint8_t T1T0MSB = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x35, sizeof(uint8_t), &T1T0MSB, sizeof(uint8_t), HAL_MAX_DELAY);

	uint8_t T0_l = 0;
	uint8_t T0_h = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x3C, sizeof(uint8_t), &T0_l, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x3D, sizeof(uint8_t), &T0_h, sizeof(uint8_t), HAL_MAX_DELAY);

	int16_t T0_OUT = ((int16_t)T0_h << 8) | T0_l;

	uint8_t T1_l = 0;
	uint8_t T1_h = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x3E, sizeof(uint8_t), &T1_l, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x3F, sizeof(uint8_t), &T1_h, sizeof(uint8_t), HAL_MAX_DELAY);

	int16_t T1_OUT = ((int16_t)T1_h << 8) | T1_l;

	float temp = ((float)(T1_degC-T0_degC)*(float)(T_OUT - T0_OUT))/((float)(T1_OUT-T0_OUT)) + T0_degC;

	return temp;
}

float hts221_humidity_read(uint8_t i2c_addr, I2C_HandleTypeDef *i2c)
{
	uint8_t humidity_l = 0;
	uint8_t humidity_h = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, HUMIDITY_OUT_L, sizeof(uint8_t), &humidity_l, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, HUMIDITY_OUT_H, sizeof(uint8_t), &humidity_h, sizeof(uint8_t), HAL_MAX_DELAY);
	int H_T_OUT = ((int16_t)humidity_h << 8) | humidity_l;

	uint16_t H0_rH_x2 = 0;
	uint16_t H1_rH_x2 = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x30, sizeof(uint16_t), &H0_rH_x2, sizeof(uint16_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x31, sizeof(uint16_t), &H1_rH_x2, sizeof(uint16_t), HAL_MAX_DELAY);

	uint16_t H0_rH = H0_rH_x2/2;
	uint16_t H1_rH = H1_rH_x2/2;

	uint8_t H0_T0_l = 0;
	uint8_t H0_T0_H = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x36, sizeof(uint8_t), &H0_T0_l, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x37, sizeof(uint8_t), &H0_T0_H, sizeof(uint8_t), HAL_MAX_DELAY);
	int16_t H0_T0 = ((int16_t)H0_T0_H << 8) | H0_T0_l;

	uint8_t H1_T0_l = 0;
	uint8_t H1_T0_H = 0;
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x3A, sizeof(uint8_t), &H1_T0_l, sizeof(uint8_t), HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(i2c, i2c_addr+1, 0x3B, sizeof(uint8_t), &H1_T0_H, sizeof(uint8_t), HAL_MAX_DELAY);
	int16_t H1_T0 = ((int16_t)H1_T0_H << 8) | H1_T0_l;

	float humidity = ((float)(H1_rH-H0_rH) * (float)(H_T_OUT-H0_T0)) / (float)(H1_T0-H0_T0) + H0_rH ;

	return humidity;
}
