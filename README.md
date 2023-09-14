# ST-GPS-Tracking
As part of the BTE5053 "Embedded Software Development" module 2018, this project includes the development of a GPS receiver controlled by a custom-designed Android app, with a stepper motor indicating the direction to the destination. <br> 
The STM32 Nucleo-Board is utilized for programming and control purposes, using both assembler language and C. <br>

## Features
- GPS coordinate tracking
- Communication between GPS receiver and custom app via Bluetooth
- Direction indication using a stepper motor
- STM32 Nucleo-Board integration
  <br><br>
## Main Code
The main code snippet, which includes the system initialization, infinite loop for distance and bearing calculation, and functions related to USART, GPIO, and UART. <br>

## triangula.c
This file includes functions to calculate distance and bearing between two latitude and longitude coordinates. It also contains functions to control a stepper motor for the pointer (arrow) direction.<br>

## How to Build and Run
Set Up Environment: Make sure you have the STM32 development environment installed. You may also need specific drivers or tools based on the STM32 Nucleo-Board you are using.<br>
