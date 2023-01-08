/********************************************************************************
* tmp36.c: Inneh�ller funktioner realterade till temperatursensorn.
********************************************************************************/
#include "header.h"

// Deklarerar array inneh�llade de senaste 5 temperaturm�tningarna.
static double temprature[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };

/********************************************************************************
* push_temperature: B�rjar med att flytta alla tal i arrayen ett steg fram.
*                   L�gger sedan in det nya temperaturv�rdet i arrayen.
*
*                   OBS: Innan dem f�rsta fem v�rdena har lagts in i arrayen f�r
*                        vi felaktiga v�rden eftersom den inte fyllts med riktiga
*                        v�rden.
********************************************************************************/
void push_temperature(double new_temprature)
{
	for(uint8_t i = 4; i > 1; i--)
	{
		temprature[i] = temprature[i -1];
	}
	
	// L�gger till nya tiden till arrayen.
	temprature[0] = new_temprature;
}

/********************************************************************************
* push_temperature: R�knar ut medelv�rdet i arrayen och skickar tillbaka detta i
*                   returv�rdet.
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
* tmp36_print_temperature: Skriver ut ett medelv�rde p� rumstemperaturen uppm�tt
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