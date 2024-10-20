/*
 * sensor.h
 *
 *  Created on: Oct 20, 2024
 *      Author: dmytro
 */

#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_

#include "stdbool.h"

static TIM_HandleTypeDef* objSP_delay_timer;
static GPIO_TypeDef* objSP_sensor_port;
static uint16_t u16L_sensor_pin;

void delay_init(TIM_HandleTypeDef* objLP_timer)
{
	objSP_delay_timer = objLP_timer;
	HAL_TIM_Base_Start(objSP_delay_timer);
}

void delay_us(uint32_t u32L_time_us)
{
	uint32_t u32_crnt_time = HAL_TIM_GetCounter(objSP_delay_timer);
	while ( HAL_TIM_GetCounter(objSP_delay_timer) - u32_crnt_time < u32L_time_us);
}

void delay_ms(uint32_t u32L_time_ms)
{
	for (uint32_t u32L_i = 0; u32L_i < u32L_time_ms; ++u32L_i)
	{
		delay_us(1000);
	}
}

void DHT11_config_to_in(void)
{
	GPIO_InitTypeDef objL_init_struct;
	objL_init_struct.Pin = u16L_sensor_pin;
	objL_init_struct.Mode = GPIO_MODE_INPUT;
	objL_init_struct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(objSP_sensor_port, &objL_init_struct);
}

void DHT11_config_to_out(void)
{
	GPIO_InitTypeDef objL_init_struct;
	HAL_GPIO_WritePin(objSP_sensor_port, u16L_sensor_pin, GPIO_PIN_SET);
	objL_init_struct.Pin = u16L_sensor_pin;
	objL_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	objL_init_struct.Pull = GPIO_PULLUP;
	objL_init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(objSP_sensor_port, &objL_init_struct);
}

void DHT11_init(GPIO_TypeDef* objL_port, uint16_t u16L_pin)
{
	objSP_sensor_port = objL_port;
	u16L_sensor_pin = u16L_pin;
}

void DHT11_Rst(void)
{
	HAL_GPIO_WritePin(objSP_sensor_port, u16L_sensor_pin, GPIO_PIN_RESET);
	delay_ms(20);
	HAL_GPIO_WritePin(objSP_sensor_port, u16L_sensor_pin, GPIO_PIN_SET);
	delay_us(30);
}

uint8_t DHT11_Check(void)
{
	uint16_t u16L_retry = 0;
	DHT11_config_to_in();
	while ((HAL_GPIO_ReadPin(objSP_sensor_port, u16L_sensor_pin) == GPIO_PIN_RESET) && u16L_retry < 100)
		{
		u16L_retry++;
		delay_us(1);
	};
	if(u16L_retry >= 100) return 1;

	u16L_retry = 0;
	while ((HAL_GPIO_ReadPin(objSP_sensor_port, u16L_sensor_pin) == GPIO_PIN_SET) && u16L_retry < 100)
	{
		u16L_retry++;
		delay_us(1);
	};
	if(u16L_retry >= 100) return 1;
	return 0;
}

uint8_t DHT11_Read_Bit(void)
{
	uint16_t u16L_retry = 0;
	while ((HAL_GPIO_ReadPin(objSP_sensor_port, u16L_sensor_pin) == GPIO_PIN_RESET) && u16L_retry < 60)
	{
		u16L_retry++;
		delay_us(1);
	}
	if (u16L_retry > 60) return 0xFF;

	u16L_retry = 0;
	while ((HAL_GPIO_ReadPin(objSP_sensor_port, u16L_sensor_pin) == GPIO_PIN_SET) && u16L_retry < 80)
	{
		u16L_retry++;
		delay_us(1);
	}
	return u16L_retry < 30 ? 0 : 1;
}

uint8_t DHT11_Read_Data(uint8_t* u8P_temp, uint8_t* u8P_humi)
{
	uint8_t u8PL_buf[5];
	uint16_t u16L_retry = 0;
	DHT11_config_to_out();
	DHT11_Rst();
	if (DHT11_Check() != 0)	return 1;

	for (uint8_t u8_i = 0; u8_i < 5; u8_i++)
	{
		u8PL_buf[u8_i] = DHT11_Read_Byte();
	}
	bool bL_has_error = true;
	if((u8PL_buf[0] + u8PL_buf[1] + u8PL_buf[2] + u8PL_buf[3]) == u8PL_buf[4])
	{
		*u8P_humi = u8PL_buf[0];
		*u8P_temp = u8PL_buf[2];
		bL_has_error = false;
	}
	if (!bL_has_error)
	{
		while ((HAL_GPIO_ReadPin(objSP_sensor_port, u16L_sensor_pin) == GPIO_PIN_RESET) && u16L_retry < 60)
		{
			u16L_retry++;
			delay_us(1);
		}
		if (u16L_retry > 60) bL_has_error = true;
	}
	return bL_has_error ? 1 : 0;
}

#endif /* SRC_SENSOR_H_ */
