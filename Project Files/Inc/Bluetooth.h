
/*============================================================================
 Name        : Bluetooth.h
 Author      : STGTS Team
 Version     : 1.0
 Copyright   : Miniproject, Module BTE505 - STGTS
 Description : Defines Variables and functions for UART / UART Interrupt

 Reference	 :

 ============================================================================*/

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_uart.h"
#include "main.h"
#include "triangula.h"

UART_HandleTypeDef huart1;
#define USARTx_IRQn                      USART1_IRQn
#define USARTx_IRQHandler                USART1_IRQHandler

void GetTargetData(gps_t *target);

#endif /* BLUETOOTH_H_ */
