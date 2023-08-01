
/*============================================================================
 Name        : triangula.h
 Author      : STGTS Team ( ..... )
 Version     : 1.0
 Copyright   : Miniproject, Module BTE505 - STGTS
 Description : Defines Structure for GPS values (The scope of this Test-Program
 is limited to Latitude and longitude)

 Reference	 : Calculate distance, bearing and more between Latitude/Longitude points and JavaScript code
 https://www.movable-type.co.uk/scripts/latlong.html
 ============================================================================*/

#ifndef TRIANGULA_H_
#define TRIANGULA_H_

#include "stdint.h"
#include "stddef.h"



typedef struct {
	float latitude;                       // Latitude in degrees
	float longitude;                      // Longitude in degrees

} gps_t;


uint8_t calcDistanceBearing(float lat_home, float lon_home, float lat_target,
		float lon_target, float* d, float* b);
//void resetPointer(double *steps);
int setPointer(double angle);
void GPIO_Init(void);
extern void Step_Right (void);
extern void Step_Left (void);

#endif /* TRIANGULA_H_ */
