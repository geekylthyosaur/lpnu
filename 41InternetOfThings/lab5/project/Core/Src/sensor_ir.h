/*
 * sensor_ir.h
 *
 *  Created on: Nov 3, 2024
 *      Author: dmytro
 */

#ifndef SRC_SENSOR_IR_H_
#define SRC_SENSOR_IR_H_

#include "math.h"

#define MIN_ADC 460
#define MAX_ADC 3870
#define START_DELAY 0
#define TOO_FAR_DIST 0
#define FILTER_COUNT 0

struct IrSensorStruct
{
	ADC_HandleTypeDef* objP_adc;
	math_function_2d_obj_t obj_func;
} typedef ir_sensor_t;

static const math_2d_point_t objPS_data[] =
{
{ MIN_ADC, 800 },
{ 776, 500 },
{ 931, 400 },
{ 1117, 300 },
{ 1365, 250 },
{ 1614, 200 },
{ 2017, 150 },
{ 2681, 100 },
{ 3413, 80 },
{ 3724, 70 },
{ MAX_ADC, 60 }
};

void ir_sensor_init(ir_sensor_t* objPL_this, ADC_HandleTypeDef* objPL_adc)
{
	objPL_this->objP_adc = objPL_adc;
	HAL_Delay(START_DELAY);
	math_function_2d_construct(&objPL_this->obj_func, objPS_data, 11);
}

uint16_t ir_sensor_get_distance(ir_sensor_t* objPL_this, uint16_t u16L_adc_val)
{
	if (u16L_adc_val >= MAX_ADC || u16L_adc_val <= MIN_ADC)
	{
	return TOO_FAR_DIST;
	}
	return math_function_2d_get_y(&objPL_this->obj_func, (int16_t)u16L_adc_val);
}

uint16_t ir_sensor_read(ir_sensor_t* objPL_this)
{
	filter_t objL_filter;
	filter_init(&objL_filter, FILTER_COUNT);
	uint16_t u16L_dist = 0;
	for (uint8_t u8L_i = 0; u8L_i < FILTER_COUNT; u8L_i++)
	{
	HAL_ADC_Start(objPL_this->objP_adc);
	HAL_ADC_PollForConversion(objPL_this->objP_adc, 0xFFFF);
	u16L_dist = filter_calc(&objL_filter, HAL_ADC_GetValue(objPL_this->objP_adc));
	}
	return ir_sensor_get_distance(objPL_this, u16L_dist);
}

#endif /* SRC_SENSOR_IR_H_ */
