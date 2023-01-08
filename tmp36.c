/********************************************************************************
* tmp36.c: Innehåller funktioner realterade till temperatursensorn.
********************************************************************************/
#include "header.h"

// Deklarerar array innehållade de senaste 5 temperaturmätningarna.
static double temprature[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };

/********************************************************************************
* push_temperature: Börjar med att flytta alla tal i arrayen ett steg fram.
*                   Lägger sedan in det nya temperaturvärdet i arrayen.
*
*                   OBS: Innan dem första fem värdena har lagts in i arrayen får
*                        vi felaktiga värden eftersom den inte fyllts med riktiga
*                        värden.
********************************************************************************/
void push_temperature(double new_temprature)
{
	for(uint8_t i = 4; i > 1; i--)
	{
		temprature[i] = temprature[i -1];
	}
	
	// Lägger till nya tiden till arrayen.
	temprature[0] = new_temprature;
}

/********************************************************************************
* push_temperature: Räknar ut medelvärdet i arrayen och skickar tillbaka detta i
*                   returvärdet.
********************************************************************************/
double average_temperature()
{
	double average = 0.0;
	
	for(uint8_t i = 0; i < 5; i++)
	{
		average += temprature[i]; 
	}
	
	return average;
}

/********************************************************************************
* tmp36_print_temperature: Skriver ut ett medelvärde på rumstemperaturen uppmätt
*                          med temperatursensor TMP36 via ansluten seriell
*                          terminal.
********************************************************************************/
void tmp36_print_temperature()
{
	serial_print_string("Temperature: ");
	serial_print_double(average_temperature());
	serial_print_string(" degrees Celcius\n");
	return;
}