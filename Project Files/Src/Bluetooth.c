
/*============================================================================
 Name        : Bluetooth.c
 Author      : STGTS Team
 Version     : 1.0
 Copyright   : Miniproject, Module BTE505 - STGTS
 Description : Defindes the functionality necessary for buffering the UART data and
 extracting the 2 float values (latitude and longitude)

 Reference	 :
 ============================================================================*/

#include "Bluetooth.h"

/* Buffering and extracting function ---------------------------------------------------------*/
// rx_buff is an extern variable defined in main
char rx_buff[21];

void GetTargetData(gps_t *target) {

	float Wert1 = 0;
	float Wert2 = 0;

	if (rx_buff[0] != 0) { //Abfrage ob der Buffer leer ist
		rx_buff[10] = 0; //0 Terminierung f�r den atof(). erste Koordinate
		rx_buff[20] = 0; //0 Terminierung f�r den atof(). zweite Koordinate

		Wert1 = (float) atof(rx_buff); //string to float
		Wert2 = (float) atof(&rx_buff[11]); //string to float

		if (Wert1 != 0) //Wert �bergeben wenn die Umwandlung erfolgreich war
				{
			target->latitude = Wert1;

		}

		if (Wert2 != 0) //Wert �bergeben wenn die Umwandlung erfolgreich war
				{
			target->longitude = Wert2;
		}

		for (int i = 0; i < sizeof(rx_buff); i++) //Buffer leeren
				{
			rx_buff[i] = 0;
		}

	}

}

