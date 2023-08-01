
/*============================================================================
 Name        : triangula.c
 Author      : Shadi Alhaj
 Version     : 1.0
 Copyright   : Miniproject, Module BTE505 - STGTS
 Description : 1- The function calcDistanceBearing() calculates distance and bearing
 between tow latitude and longitude coordinates.

 2- The function resetPointer() steps the motor to start position so that
 the pointer (arrow) points North.

 3- The function setPointer() steps the motor so that the arrow points
 to target. (steps correspond to bearing angle)

 Reference	 : Calculate distance, bearing and more between Latitude/Longitude points and JavaScript code
 https://www.movable-type.co.uk/scripts/latlong.html
 ============================================================================*/

/* Includes ------------------------------------------------------------------*/

#include "triangula.h"
#include "Bluetooth.h"

#include "math.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_gpio.h"

#include "stm32l0xx.h"

#define D2R(x)              (float)((x) * 0.01745329251994f)    //Degree to radian
#define R2D(x)              (float)((x) * 57.29577951308232f)   //Radian to degree
#define EARTH_RADIUS        (6371.0f)   						//Earth radius in kilometers

volatile double currentPointerAngle = -1;		//Position of the motor at start

GPIO_InitTypeDef GPIO_InitStruct;

/**
 Calculates distance and bearing

 * \param[in]       lat_home: Home latitude coordinate in degrees
 * \param[in]       lon_home: Home longitude coordinate in degrees
 * \param[in]       lat_target: Target latitude coordinate in degrees
 * \param[in]       lon_target: Target longitude coordinate in degrees
 * \param[out]      d: Pointer to distance value in meters
 * \param[out]      b: Pointer to  bearing value in relation to north in degrees
 */
uint8_t calcDistanceBearing(float lat_home, float lon_home, float lat_target,
		float lon_target, float* d, float* b) {
	float d_lat, d_lon, a;

	if (d == NULL && b == NULL) {
		return 0;
	}

	/* Convert degrees to radians */
	d_lat = D2R(lat_target - lat_home);
	d_lon = D2R(lon_target - lon_home);
	lat_home = D2R(lat_home);
	lon_home = D2R(lon_home);
	lat_target = D2R(lat_target);
	lon_target = D2R(lon_target);

	/* Distance equals the absolute value in meters between 2 points.  */

	if (d != NULL) {
		a = (float) (sin(d_lat * 0.5f) * sin(d_lat * 0.5f)
				+ sin(d_lon * 0.5f) * sin(d_lon * 0.5f) * cos(lat_home)
						* cos(lat_target));
		*d = (float) (EARTH_RADIUS * 2.0f * atan2(sqrt(a), sqrt(1.0f - a))
				* 1000.0f);
	}

	/*
	 * Bearing from Home to target is calculated.
	 * Result show the direction referenced to north.
	 * Bearing  0 => to north
	 * Bearing 90 => to east
	 * Bearing 180 => to south
	 * Bearing 270 => to west
	 */
	if (b != NULL) {
		d_lat = (float) (sin(lon_target - lon_home) * cos(lat_target));
		d_lon = (float) (cos(lat_home) * sin(lat_target)
				- sin(lat_home) * cos(lat_target) * cos(lon_target - lon_home));

		*b = R2D(atan2(d_lat, d_lon)); /* Calculate bearing and convert to degrees */
		if (*b < 0) { /* Check for negative angle */
			*b += (float) 360.0; /* Bearing always positive */
		}
	}
	return 1;
}

/*
 * Steps the motor and change the direction of pointer (arrow)
 */
int setPointer(double angle) {
	int nz = round((int) (angle - currentPointerAngle + 512) % 512);
	int count = 0;
	if (nz < 256) {
		while (fabs(currentPointerAngle - angle) > 1) {
			Step_Right();
			count++;
			//printf("stepping right %d \n\r", count);
			currentPointerAngle += 1;
			if (currentPointerAngle > 512) {
				currentPointerAngle -= 512;

			}
		}
	} else {
		while (fabs(currentPointerAngle - angle) > 1) {
			Step_Left();
			count++;
			//printf("stepping left %d \n\r", count);
			currentPointerAngle -= 1;
			if (currentPointerAngle < 0) {
				currentPointerAngle += 512;
			}
		}
	}
	return count;

}

// /* One revolution CW using wave step mode ..... */
// void stepRight(void) {

// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
// 	HAL_Delay(5);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
// 	HAL_Delay(5);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
// 	HAL_Delay(5);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);
// 	HAL_Delay(5);

// }

// /* One revolution CCW using wave step mode .... */
// void stepLeft(void) {

// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 1);

// 	HAL_Delay(5);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);

// 	HAL_Delay(5);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
// 	HAL_Delay(5);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, 1);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
// 	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, 0);
// 	HAL_Delay(5);

// }

/* Init function for stepper motor .... */

void GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
