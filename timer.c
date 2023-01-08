/********************************************************************************
* timer.c: Inneh�ller funktioner realterade till timern.
********************************************************************************/
#include "header.h"

// Vad timern ska r�kna upp till.
static uint32_t timer0_max = 0;

// Deklarerar funktion.
static uint32_t average(const uint32_t* data, 
                        const uint8_t size);

/********************************************************************************
* set_timer0_max: Initierar timern med en angiven tid den ska r�kna till.
********************************************************************************/
void set_timer0_max(const double time_ms)
{
   timer0_max = (uint32_t)(time_ms / 0.128 + 0.5);
   return;
}

/********************************************************************************
* set_timer0_max: Skickar tillbaka timerns tid den ska r�kna till.
********************************************************************************/
uint32_t get_timer0_max(void)
{
   return timer0_max;
}

/********************************************************************************
* push_counter_time: fem stycken tidsv�rden skickas in i funktionen beroende p�
*                    tidsintervallen mellan knapptrycken. N�r detta har gjorts
*                    r�knas medelv�rdet ut genom en funktion och array b�rjar om
*                    p� nytt.
********************************************************************************/
void push_counter_time(volatile uint32_t* counter_time)
{ 
   static uint32_t timerarray_s[5];
   static uint8_t index = 0;
   
   timerarray_s[index++] = *counter_time;
   *counter_time = 0;

   // Genomsnittstiden r�knas ut med en funktion n�r 5 v�rden har lagts in i arrayen.
   if (index >= 5)
   {
      timer0_max = average(timerarray_s, 5);
      index = 0;
   }
}

/********************************************************************************
* average: R�knar ut medelv�rdet i arrayen och skickar tillbaka det som
*          returv�rde.
********************************************************************************/
static uint32_t average(const uint32_t* data, 
                        const uint8_t size)
{
   uint32_t sum = 0;

   for (uint8_t i = 0; i < size; ++i)
   {
      sum += data[i];
   }

   return (uint32_t)(sum / (double)size + 0.5);
}