/*
 * sensor_us.h
 *
 *  Created on: Nov 3, 2024
 *      Author: dmytro
 */

#ifndef SRC_SENSOR_US_H_
#define SRC_SENSOR_US_H_

#include "Legacy/stm32_hal_legacy.h"

static TIM_HandleTypeDef* objSP_delay_timer;

void delay_init(TIM_HandleTypeDef* objLP_timer)
{
	objSP_delay_timer = objLP_timer;
	HAL_TIM_Base_Start(objSP_delay_timer);
}

void delay_us(uint32_t u32L_time_us)
{
	uint32_t u32_crnt_time = __HAL_TIM_GetCounter(objSP_delay_timer);
	while ( __HAL_TIM_GetCounter(objSP_delay_timer) - u32_crnt_time < u32L_time_us);
}

void delay_ms(uint32_t u32L_time_ms)
{
	for (uint32_t u32L_i = 0; u32L_i < u32L_time_ms; ++u32L_i)
	{
		delay_us(1000);
	}
}

#define TRIG_TIME 10

struct AcousticSensorStruct
{
	GPIO_TypeDef * objP_trig_port;
	uint16_t u16_trig_pin;
	GPIO_TypeDef * objP_echo_port;
	uint16_t u16_echo_pin;
} typedef acoustic_sensor_t;

void acoustic_sensor_init(acoustic_sensor_t* objPL_this, GPIO_TypeDef* objPL_trig_port, uint16_t u16L_trig_pin, GPIO_TypeDef * objPL_echo_port, uint16_t u16L_echo_pin)
{
	objPL_this->objP_echo_port = objPL_echo_port;
	objPL_this->objP_trig_port = objPL_trig_port;
	objPL_this->u16_echo_pin = u16L_echo_pin;
	objPL_this->u16_trig_pin = u16L_trig_pin;
}

uint16_t acoustic_sensor_convert_duration(uint32_t u32L_duration)
{
	return (u32L_duration * 10) / 58;
}

uint32_t delay_get_us_tick() {
	return __HAL_TIM_GetCounter(objSP_delay_timer);
}

uint16_t acoustic_sensor_read(acoustic_sensor_t* objPL_this)
{
	uint32_t u32L_timer = delay_get_us_tick();
	HAL_GPIO_WritePin(objPL_this->objP_trig_port, objPL_this->u16_trig_pin,
	GPIO_PIN_SET);
	while (delay_get_us_tick() - u32L_timer < TRIG_TIME);
	HAL_GPIO_WritePin(objPL_this->objP_trig_port, objPL_this->u16_trig_pin,
	GPIO_PIN_RESET);
	while (HAL_GPIO_ReadPin(objPL_this->objP_echo_port, objPL_this->u16_echo_pin) ==
	GPIO_PIN_RESET);
	u32L_timer = delay_get_us_tick();
	while (HAL_GPIO_ReadPin(objPL_this->objP_echo_port, objPL_this->u16_echo_pin) ==
	GPIO_PIN_SET);
	uint32_t u32L_duration = delay_get_us_tick() - u32L_timer;
	return acoustic_sensor_convert_duration(u32L_duration);
}

#endif /* SRC_SENSOR_US_H_ */
