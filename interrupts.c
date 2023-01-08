/********************************************************************************
* interrupts.c: Inneh�ller avbrottsrutiner.
********************************************************************************/
#include "header.h"

// Definerar variabler.
static volatile uint32_t counter_timer0 = 0;
static volatile uint32_t time_between_buttons = 0;

/********************************************************************************
* ISR(PCINT0_vect): Trycks v�ran knapp ned s� skrivs temperaturen i
*                   omgivningen ut och r�knaren nollst�lls inf�r n�sta 
*                   uppr�kning.
********************************************************************************/
ISR(PCINT0_vect)
{
	if (BUTTON1_IS_PRESSED)
	{
		serial_print_string("Button: ");
		tmp36_print_temperature();
		push_counter_time(&time_between_buttons);
		push_temperature(tmp36_get_temperature(&t1));
	}
}

/********************************************************************************
* ISR (TIMER0_OVF_vect): Avbrottsrutin f�r Timer 0 i Normal Mode, d�r avbrott
*                        sker var 0.128:e ms vid overflow av r�knaren TCNT0.
*                        Varje exekverat avbrott r�knas via variabeln counter0.
*                        Efter en minut skrivs temperaturen i omgivningen ut och
*                        r�knaren nollst�lls inf�r n�sta uppr�kning.
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	time_between_buttons++;
	
	if (++counter_timer0 >= get_timer0_max())
	{
		tmp36_print_temperature();
		push_temperature(tmp36_get_temperature(&t1));
		counter_timer0 = 0;
	}
	return;
}